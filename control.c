#include "control.h"

extern volatile rt_data rundata;

int vect_ctrl()
{
    int run = 1;
    uint8_t rx[MAX_RX_LEN];
    int retval = MODE_ERR;
    uint16_t alpha;
    int32_t i_alpha, i_beta, i_d, i_q;

    zero_rundata( &rundata );
    gpio_put(PWR_EN, 1);

    while(run)
    {
        alpha = rundata.alpha + (60*(time_us_32()-rundata.t))/rundata.dt;
        send_reg_16( REG_SPEED, alpha );
        /*     i_alpha = adc_raw[0];
             i_beta = (adc_raw[0]*577)/1000 + (adc_raw[1]*1154)/1000;

             i_d = (i_alpha*sin_16( alpha+90 ))/32767 + (i_beta*sin_16(alpha))/32767;
             i_q = -(i_alpha*sin_16( alpha))/32767 + (i_beta*sin_16(alpha+90))/32767;


     */
//        adc_dma_keepalive();

        if( !usb_cdc_read(rx, MAX_RX_LEN) ) continue;

        switch (rx[0])
        {
            case CMD_STOP: stop( &rundata ); break;

            case CMD_START:
            {
//                set_pwm_all( 0, 0);
//                sleep_ms(50);
                hall_irq( 0, 0);
                break;
            }

            case CMD_BRAKE:
            {
                //set_pwm_all( rundata.pwm_l, 0);
                rundata.pwm_h = 0;
                rundata.pwm_l = 0;
                rundata.set_speed = 0;
                break;
            }

            case CMD_WREG: break;// retval = parse_wreg( &run, &rundata, rx ); break;
            case CMD_EXIT: run = 0; retval = MODE_IDLE; break;
            default: run = 0; retval = MODE_ERR;
        }
    }
    set_pwm_all_ph(0, 0);
    gpio_put(PWR_EN, 0);

    return retval;
}



int speed_ctrl( int pid )
{
    int run = 1;
    uint8_t rx[MAX_RX_LEN];
    int retval = MODE_ERR;
    uint16_t prev_speed;
    pid_i spid;

    zero_rundata( &rundata );
    pid_init( &spid, 10000, 40000, -20000);
    pid_tune( &spid, 100, 2, 0); //blizej prawdy, powoli zmienne obciazenia kompensuje

    gpio_put(PWR_EN, 1);

    while(run)
    {
        if( prev_speed != rundata.speed )
        {
            send_reg_16( REG_SPEED, rundata.speed );
            prev_speed = rundata.speed;
        }

        if( pid )
        {
            rundata.pwm_l = pid_calc(&spid, (int32_t) rundata.set_speed, (int32_t) rundata.speed) + 20000;
            send_reg_16(REG_PWM_L, rundata.pwm_l);
        }

        if( time_us_32() - rundata.t > 1000000 ) rundata.speed = 0;

        sleep_ms(10);

        pwm_set_chan_level( PH_ROTOR, PWM_CHAN_B, rundata.pwm_r/6);

        if( !usb_cdc_read(rx, MAX_RX_LEN) ) continue;

        switch (rx[0])
        {
            case CMD_STOP: stop( &rundata ); break;

            case CMD_START:
            {
//                set_pwm_all( 10000, 0);
//                sleep_ms(50);
//                set_pwm_all( 0, 0);
                hall_irq( 0, 0);
                break;
            }

            case CMD_BRAKE:
            {
                set_pwm_all_ph(rundata.pwm_l, 0);
                rundata.pwm_h = 0;
//                rundata.pwm_l = 0;
                rundata.set_speed = 0;
                send_reg_16( REG_SET_SPEED, rundata.set_speed);
                break;
            }

            case CMD_WREG: retval = parse_wreg( &run, &rundata, &spid, rx ); break;
            case CMD_EXIT: run = 0; retval = MODE_IDLE; break;
            default: run = 0; retval = MODE_ERR;
        }
    }

    stop( &rundata );
    gpio_put(PWR_EN, 0);

    return retval;
}
