#include "bridge.h"

volatile rt_data rundata;

void hall_irq( uint gpio, uint32_t events )
{
    static uint32_t t6;
    static const int trtab[8] = TRTAB;
    static const int alpha_tab[8] = ALPHA_TAB;
    uint32_t state = ( gpio_get_all() & (H_ALL) ) >> 16;
    int step = trtab[state] + ( rundata.dir == FWD ? -1 : 1 );

    rundata.dt = time_us_32() - rundata.t;
    rundata.t = time_us_32();
    rundata.alpha = alpha_tab[state];

    switch( step )
    {
        case 6: step = 0; break;
        case -1: step = 5; break;
        case 253:;
        case 254:;
        case 255: return;
        default: break;
    }

    if( step == 0 )
    {
        rundata.speed = (uint32_t)1e7/(time_us_32() - t6);
        t6 = time_us_32();
    }

    set_out_state( step, rundata.pwm_l, rundata.pwm_h );
}



int manual_step()
{
    int prev_state = 0, state = 0, run = 1;
    int rx[MAX_RX_LEN];
    int retval = MODE_ERR;

    zero_rundata( &rundata );

    while(run)
    {
        state = ( gpio_get_all() & (H_ALL) ) >> 16;

        if( prev_state != state )
        {
            send_reg_8(REG_STATE, state);
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

            case CMD_WREG: retval = parse_wreg( &run, &rundata, NULL, rx ); break;
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

void rotate_stupid( volatile rt_data* data, int state)
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

        set_out_state( step, data->pwm_l, data->pwm_h );
    }
    set_pwm_all( 0, 0);
}

void step( volatile rt_data* data )
{
    static int step = 0;

    step += ( data->dir == FWD ? -1 : 1 );
    if( step > 5 ) step = 0;
    if( step < 0 ) step = 5;

    send_reg_8(REG_C_STATE, step);

    set_out_state( step, data->pwm_l, data->pwm_h );
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

    gpio_init_mask(  H_ALL );
    gpio_set_dir_in_masked( H_ALL );

    gpio_set_irq_enabled_with_callback( H1, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    gpio_set_irq_enabled_with_callback( H2, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    gpio_set_irq_enabled_with_callback( H3, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    irq_set_enabled(IO_IRQ_BANK0, 0);
}

int sin_16( int angle )
{
    int values[180] = SIN_180;

    angle %= 360;
    if( angle < 0 )
    {
        if( angle > -180 ) return -values[-angle];
        else return values[angle+360];
    }
    if( angle > 180 ) return -values[angle-180];
    return values[angle];
}
