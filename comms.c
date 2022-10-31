#include "comms.h"

void pc_control()
{
    int mode = MODE_IDLE;
    int rx[MAX_RX_LEN];
    int i = 0;

    while(1)
    {
        i = -1;
        do
        {
            rx[++i] = getchar_timeout_us(0);
        } while (i < MAX_RX_LEN && rx[i] != PICO_ERROR_TIMEOUT );

        switch (rx[0])
        {
            case CMD_WREG:
            {
                if( rx[1] == REG_MODE ) mode = rx[2];
                break;
            }
            case PICO_ERROR_TIMEOUT: break;
            default: mode = MODE_ERR;
        }

        putchar_raw(REG_MODE);
        putchar_raw(mode);

        switch( mode )
        {
            case MODE_IDLE:
            {
                sleep_ms(1000);
                gpio_xor_mask((1<<LED));
                break;
            }

            case MODE_MAN_STEP: mode = manual_step(); break;
            case MODE_SPEED_CTL: mode = speed_ctrl(); break;
            case MODE_SYNC_IRQ: mode = irq_work(); break;
            case MODE_VECT:
            {
                mode = MODE_IDLE;
                putchar_raw(INFO_ERR);
                putchar_raw(ERR_NOT_IMPL);
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