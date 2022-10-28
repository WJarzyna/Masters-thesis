#include "bridge.h"

void hall_irq( uint gpio, uint32_t events )
{
    uint32_t state = ( gpio_get_all() & (H_ALL) ) >> 16;
    putchar_raw(REG_STATE);
    putchar_raw( state);
}

int irq_work()
{
    uint32_t run = 1;

    gpio_set_irq_enabled_with_callback( H1, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    gpio_set_irq_enabled_with_callback( H2, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    gpio_set_irq_enabled_with_callback( H3, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);

    while(run)
    {
        switch( getchar_timeout_us(0) )
        {
            case CMD_EXIT: run = 0; break;
            default: break;
        }
    }
    irq_set_enabled(IO_IRQ_BANK0, 0);

    return MODE_IDLE;
}

int sync_rotation()
{
    int trtab[8] = TRTAB;
    rt_data rundata = {0, 0, 0, FWD};
    uint prev_state = 0, state = 0, run = 1;
    uint32_t t = time_us_32();
    int rx[MAX_RX_LEN];
    int retval = MODE_ERR, advance = 0, step;

    while(run)
    {
        while( state == prev_state )
        {
            state = ( gpio_get_all() & (H_ALL) ) >> 16;
            rx[0] = getchar_timeout_us(0);
            if( rx[0] != PICO_ERROR_TIMEOUT )
            {
                advance = 1;
                break;
            }
        }

        if( prev_state != state )
        {
            prev_state = state;

            if( state == 0 ) // co obrot
            {
                send_reg_16( REG_DT, time_us_32() - t );
                t = time_us_32();
            }

            step = trtab[state] + ( rundata.dir == FWD ? 1 : -1 );
            switch( step )
            {
                case 6: step = 0; break;
                case -1: step = 5; break;
                case 253:;
                case 254:;
                case 255: continue;
                default: break;
            }

            set_out_state( step, rundata.pwm_l, rundata.pwm_h );
        }

        rx_data( rx, advance);
        advance = 0;

        switch (rx[0])
        {
            case CMD_STOP:
            {
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                send_reg_16( REG_PWM_H, rundata.pwm_h);
                send_reg_16( REG_PWM_L, rundata.pwm_l);
                break;
            }

            case CMD_START:
            {
                set_pwm_all( rundata.pwm_l, 0);
                sleep_ms(50);
                prev_state = 255;
                set_pwm_all( 0, 0);
                break;
            }

            case CMD_BRAKE:
            {
                set_pwm_all( rundata.pwm_l, 0);
                rundata.pwm_l = 0;
                rundata.pwm_h = 0;
                busy_wait_ms(2000);
                set_pwm_all( 0, 0);
                break;
            }

            case CMD_WREG: retval = parse_wreg( &run, &rundata, rx ); break;
            case CMD_EXIT: run = 0; retval = MODE_IDLE; break;
            case PICO_ERROR_TIMEOUT: break;
            default: run = 0; retval = MODE_ERR;
        }
    }
    set_pwm_all( 0, 0);

    return retval;
}

int manual_step()
{
    uint prev_state = 0, state = 0, run = 1;
    rt_data rundata = {0, 0, 0, FWD};
    int rx[MAX_RX_LEN];
    int retval = MODE_ERR;

    while(run)
    {
        state = ( gpio_get_all() & (H_ALL) ) >> 16;

        if( prev_state != state )
        {
            putchar_raw(REG_STATE);
            putchar_raw( state);
            prev_state = state;
        }

        rx_data( rx, 0 );

        switch (rx[0])
        {
            case CMD_STOP:
            {
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                send_reg_16( REG_PWM_H, rundata.pwm_h);
                send_reg_16( REG_PWM_L, rundata.pwm_l);
                break;
            }

            case CMD_START: rotate_stupid( &rundata, state); break;
            case CMD_BRAKE:
            {
                set_pwm_all( rundata.pwm_l, 0);
                rundata.pwm_l = 0;
                rundata.pwm_h = 0;
                busy_wait_ms(2000);
                set_pwm_all( 0, 0);
                break;
            }

            case CMD_WREG: retval = parse_wreg( &run, &rundata, rx ); break;
            case CMD_STEP: step( &rundata); break;

            case CMD_EXIT: run = 0; retval = MODE_IDLE; break;
            case PICO_ERROR_TIMEOUT: break;
            default: run = 0; retval = MODE_ERR;
        }
    }
    set_pwm_all( 0, 0);

    return retval;
}

void set_pwm_all( uint16_t pwm_l, uint16_t pwm_h)
{
    pwm_set_both_levels(PH_A, pwm_l, pwm_h);
    pwm_set_both_levels(PH_B, pwm_l, pwm_h);
    pwm_set_both_levels(PH_C, pwm_l, pwm_h);
}

void send_reg_16( int name, uint16_t reg)
{
    putchar_raw(name);
    putchar_raw(reg >> 8);
    putchar_raw(reg & 0xFF);
}

void rx_data( int rx[], int advance )
{
    int i = -1;
    i += advance;
    do
    {
        rx[++i] = getchar_timeout_us(0);
    }
    while( i < MAX_RX_LEN && rx[i] != PICO_ERROR_TIMEOUT );
}

int parse_wreg( uint* run, rt_data* data, int rx[] )
{
    switch (rx[1])
    {
        case REG_DIR:
        {
            data->dir = rx[2];
            putchar_raw(REG_DIR);
            putchar_raw(data->dir);
            break;
        }
        case REG_PWM_H:
        {
            data->pwm_h = (rx[2] << 8) + rx[3];
            send_reg_16(REG_PWM_H, data->pwm_h);
            break;
        }
        case REG_PWM_L:
        {
            data->pwm_l = (rx[2] << 8) + rx[3];
            send_reg_16(REG_PWM_L, data->pwm_l);
            break;
        }
//                    case REG_PWM_R:
//                    {
//                        data->pwm_h = (rx[2] << 8) + rx[3];
//                        send_reg_16( REG_PWM_R, data->pwm_r);
//                        break;
//                    }
        default: *run = 0; return MODE_ERR;
    }

    return MODE_IDLE;
}

void set_out_state( int step, uint16_t pwm_l, uint16_t pwm_h )
{
    static const uint ctab_al[6] = CTAB_AL;
    static const uint ctab_ah[6] = CTAB_AH;
    static const uint ctab_bl[6] = CTAB_BL;
    static const uint ctab_bh[6] = CTAB_BH;
    static const uint ctab_cl[6] = CTAB_CL;
    static const uint ctab_ch[6] = CTAB_CH;

    set_pwm_all( 0, 0);
    busy_wait_us_32( DEAD_TIME);
    pwm_set_both_levels(PH_A, ctab_al[step]*pwm_h, ctab_ah[step]*pwm_l);
    pwm_set_both_levels(PH_B, ctab_bl[step]*pwm_h, ctab_bh[step]*pwm_l);
    pwm_set_both_levels(PH_C, ctab_cl[step]*pwm_h, ctab_ch[step]*pwm_l);
}

void rotate_stupid( rt_data* rundata, int state)
{
    int prev_state = 255, step = 0;

    for( unsigned i = 0; i < 60; ++i)
    {
        while( state == prev_state )
        {
            state = ( gpio_get_all() & (H_ALL) ) >> 16;
            if( getchar_timeout_us(0) != PICO_ERROR_TIMEOUT ) return;
        }
        prev_state = state;

        if( ++step > 5 ) step = 0;

        set_out_state( step, rundata->pwm_l, rundata->pwm_h );
    }
    set_pwm_all( 0, 0);
}

void step( rt_data* rundata )
{
    static int step = 0;

    step += ( rundata->dir == FWD ? 1 : -1 );
    if( step > 5 ) step = 0;
    if( step < 0 ) step = 5;

    putchar_raw(REG_C_STATE);
    putchar_raw( step);

    set_out_state( step, rundata->pwm_l, rundata->pwm_h );
    sleep_ms(100);
    set_pwm_all( 0, 0);
}

void bridge_init()
{
    gpio_set_function( A_L, GPIO_FUNC_PWM);
    gpio_set_function( A_H, GPIO_FUNC_PWM);
    gpio_set_function( B_L, GPIO_FUNC_PWM);
    gpio_set_function( B_H, GPIO_FUNC_PWM);
    gpio_set_function( C_L, GPIO_FUNC_PWM);
    gpio_set_function( C_H, GPIO_FUNC_PWM);

    pwm_set_wrap(PH_A, PWM_MAX);
    pwm_set_wrap(PH_B, PWM_MAX);
    pwm_set_wrap(PH_C, PWM_MAX);

    set_pwm_all( 0, 0);

    pwm_set_enabled(PH_A, true);
    pwm_set_enabled(PH_B, true);
    pwm_set_enabled(PH_C, true);
}