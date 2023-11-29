#include "comms.h"

void pc_control()
{
    int mode = MODE_IDLE;
    int rx[MAX_RX_LEN];

    while(1)
    {
        rx_data( rx, 0);

        switch (rx[0])
        {
            case CMD_WREG:
            {
                if( rx[1] == REG_MODE ) mode = rx[2];
                break;
            }
            case PICO_ERROR_TIMEOUT: break;
            default: send_reg_8(INFO_ERR, ERR_INV_CMD); mode = MODE_ERR;
        }

        send_reg_8(REG_MODE, mode);

        switch( mode )
        {
            case MODE_IDLE:
            {
                sleep_ms(1000);
                gpio_xor_mask((1<<LED));
                break;
            }

            case MODE_MAN_STEP: mode = manual_step(); break;
            case MODE_SPEED_CTL: mode = speed_ctrl(1); break;
            case MODE_SYNC_IRQ: mode = speed_ctrl(0); break;
            case MODE_VECT:
            {
                mode = MODE_IDLE;
                send_reg_8(INFO_ERR, ERR_NOT_IMPL);
                break;
            }

            default:
            {
                mode = MODE_ERR;
                sleep_ms(100);
                gpio_xor_mask((1<<LED));
            }
        }
    }
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

int parse_wreg( int* run, volatile rt_data* data, volatile pid_i* pid, const int rx[] )
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

        case REG_PWM_R:
        {
            data->pwm_r = (rx[2] << 8) + rx[3];
            send_reg_16(REG_PWM_R, data->pwm_r);
            break;
        }
        case REG_SET_SPEED:
        {
            data->set_speed = (rx[2] << 8) + rx[3];
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