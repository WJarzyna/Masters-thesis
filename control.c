#include "control.h"

extern volatile rt_data rundata;

int vect_ctrl()
{
    int run = 1;
    int rx[MAX_RX_LEN];
    int retval = MODE_ERR;
    uint16_t alpha;
    int32_t i_alpha, i_beta, i_d, i_q;

    zero_rundata( &rundata );
    adc_init_dma();

    while(run)
    {
        rx_data( rx, 0);

        alpha = rundata.alpha + (60*(time_us_32()-rundata.t))/rundata.dt;
        send_reg_16( REG_SPEED, alpha );
        /*     i_alpha = adc_raw[0];
             i_beta = (adc_raw[0]*577)/1000 + (adc_raw[1]*1154)/1000;

             i_d = (i_alpha*sin_16( alpha+90 ))/32767 + (i_beta*sin_16(alpha))/32767;
             i_q = -(i_alpha*sin_16( alpha))/32767 + (i_beta*sin_16(alpha+90))/32767;


     */
        adc_dma_keepalive();

        switch (rx[0])
        {
            case CMD_STOP:
            {
                irq_set_enabled(IO_IRQ_BANK0, 0);
                set_pwm_all( 0, 0);
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                rundata.setpoint = 0;
                send_reg_16( REG_PWM_H, rundata.pwm_h);
                send_reg_16( REG_PWM_L, rundata.pwm_l);
                break;
            }

            case CMD_START:
            {
                //set_pwm_all( 10000, 0);
                sleep_ms(50);
                set_pwm_all( 0, 0);
                irq_set_enabled(IO_IRQ_BANK0, 1);
                hall_irq( 0, 0);
                break;
            }

            case CMD_BRAKE:
            {
                irq_set_enabled(IO_IRQ_BANK0, 0);
                //set_pwm_all( rundata.pwm_l, 0);
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                rundata.setpoint = 0;
                break;
            }

            case CMD_WREG: break;// retval = parse_wreg( &run, &rundata, rx ); break;
            case CMD_EXIT: run = 0; retval = MODE_IDLE; break;
            case PICO_ERROR_TIMEOUT: break;
            default: run = 0; retval = MODE_ERR;
        }
    }
    irq_set_enabled(IO_IRQ_BANK0, 0);
    set_pwm_all( 0, 0);

    return retval;
}

int speed_ctrl( int pid )
{
    int run = 1;
    int rx[MAX_RX_LEN];
    int retval = MODE_ERR;
    uint16_t prev_speed;
    pid_i spid;

    zero_rundata( &rundata );
    pid_init( &spid, 40000, 60000, 0);
    pid_tune( &spid, 100, 2, 0); //blizej prawdy, powoli zmienne obciazenia kompensuje

    while(run)
    {
        if( prev_speed != rundata.speed )
        {
            send_reg_16( REG_SPEED, rundata.speed );
            prev_speed = rundata.speed;
        }

        if( pid )
        {
            rundata.pwm_l = pid_calc(&spid, (int32_t) rundata.setpoint, (int32_t) rundata.speed);
            send_reg_16(REG_PWM_L, rundata.pwm_l);
        }

        sleep_ms(10);

        rx_data( rx, 0);

        switch (rx[0])
        {
            case CMD_STOP:
            {
                irq_set_enabled(IO_IRQ_BANK0, 0);
                set_pwm_all( 0, 0);
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                rundata.setpoint = 0;
                send_reg_16( REG_PWM_H, rundata.pwm_h);
                send_reg_16( REG_PWM_L, rundata.pwm_l);
                break;
            }

            case CMD_START:
            {
                set_pwm_all( 10000, 0);
                sleep_ms(50);
                set_pwm_all( 0, 0);
                irq_set_enabled(IO_IRQ_BANK0, 1);
                hall_irq( 0, 0);
                break;
            }

            case CMD_BRAKE:
            {
                irq_set_enabled(IO_IRQ_BANK0, 0);
                set_pwm_all( rundata.pwm_l, 0);
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                rundata.setpoint = 0;
                break;
            }

            case CMD_WREG: retval = parse_wreg( &run, &rundata, rx ); break;
            case CMD_EXIT: run = 0; retval = MODE_IDLE; break;
            case PICO_ERROR_TIMEOUT: break;
            default: run = 0; retval = MODE_ERR;
        }
    }
    irq_set_enabled(IO_IRQ_BANK0, 0);
    set_pwm_all( 0, 0);

    return retval;
}