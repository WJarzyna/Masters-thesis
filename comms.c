#include "comms.h"

volatile uint32_t led_status;
extern volatile uint32_t cdc_status;

void pc_control()
{
    int mode = MODE_IDLE;
    uint8_t error = ERR_NONE;
    uint8_t rx[MAX_RX_LEN] = {};

    while(1)
    {
        send_reg_8(REG_MODE, mode);

        while( cdc_status != CONNECTED )
        {
            led_status = LED_OFF;
            sleep_ms(100);
        }

        switch( mode )
        {
            case MODE_IDLE: led_status = LED_BSLOW; sleep_ms(100); break;
            case MODE_MAN_STEP: led_status = LED_ON; mode = manual_step(); break;
            case MODE_SPEED_CTL: led_status = LED_ON; mode = speed_ctrl(1); break;
            case MODE_SYNC_IRQ: led_status = LED_ON; mode = speed_ctrl(0); break;
            case MODE_VECT:
            {
                mode = MODE_IDLE;
                send_reg_8(INFO_ERR, ERR_NOT_IMPL);
                break;
            }

            default:
            {
                led_status = LED_BFAST;
                while(1)
                {
                    send_reg_8(REG_MODE, mode);
                    send_reg_8(INFO_ERR, error);
                    sleep_ms(100);
                }
            }
        }

        if( !usb_cdc_read(rx, MAX_RX_LEN) ) continue;

        switch (rx[0])
        {
            case CMD_WREG:
            {
                if( rx[1] == REG_MODE ) mode = rx[2];
                break;
            }
            case CMD_NONE: break;
            default: error = rx[0]; mode = MODE_ERR;
        }
    }
}



int parse_wreg( int* run, volatile rt_data* data, volatile pid_i* pid, const uint8_t rx[] )
{
    switch (rx[1])
    {
        case REG_DIR:
        {
            data->dir = rx[2];
            send_reg_8(REG_DIR, data->dir);
            break;
        }
        case REG_PWM_H:
        {
            data->pwm_h = (rx[3] << 8) + rx[2];
            send_reg_16(REG_PWM_H, data->pwm_h);
            break;
        }
        case REG_PWM_L:
        {
            data->pwm_l = (rx[3] << 8) + rx[2];
            send_reg_16(REG_PWM_L, data->pwm_l);
            break;
        }

        case REG_PWM_R:
        {
            data->pwm_r = (rx[3] << 8) + rx[2];
            send_reg_16(REG_PWM_R, data->pwm_r);
            break;
        }

        case REG_SET_SPEED:
        {
            data->set_speed = (rx[3] << 8) + rx[2];
            send_reg_16( REG_SET_SPEED, data->set_speed);
            break;
        }

        case REG_PID_P:
        {
            pid_tune( pid, rx[2], pid->ki, pid->kd);
            send_reg_8( REG_PID_P, pid->kp);
            break;
        }

        case REG_PID_I:
        {
            pid_tune( pid, pid->kp, rx[2], pid->kd);
            send_reg_8( REG_PID_I, pid->ki);
            break;
        }

        case REG_PID_D:
        {
            pid_tune( pid, pid->kp, pid->ki, rx[2]);
            send_reg_8( REG_PID_D, pid->kd);
            break;
        }

        default: *run = 0; return MODE_ERR;
    }

    return MODE_IDLE;
}

void zero_rundata( volatile rt_data* data)
{
    data->pwm_l = 0;
    data->pwm_h = 0;
    data->pwm_r = 0;
    data->dir = FWD;
    data->speed = 0;
    data->set_speed = 0;
    data->dt = 0xFFFF;
    data->alpha = 0;
    data->t = 0;
}


static bool led_blinking_task(repeating_timer_t* timer)
{
    switch (led_status)
    {
        case LED_ON: gpio_put(LED, 1); return 1;
        case LED_BFAST: timer->delay_us = 100000; break;
        case LED_BSLOW: timer->delay_us = 1000000; break;
        default: gpio_put(LED, 0); return 1;
    }
    gpio_xor_mask((1<<LED));
}


void comms_init()
{
    usb_cdc_init();

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 1);

    static repeating_timer_t blink_timer;
    add_repeating_timer_ms(1000, led_blinking_task, NULL, &blink_timer);
}