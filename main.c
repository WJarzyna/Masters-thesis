#include <hardware/pwm.h>
#include <pico/stdio.h>
#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include "bridge.h"

void blind_rotation( uint32_t erots )
{
    uint32_t blindcomtab[6] = COMTABLE;

    for ( unsigned er = 0; er<erots; ++er)
    {
        for ( unsigned i = 0; i < MAX_CS; ++i)
        {
            gpio_clr_mask(T_ALL);
            sleep_us(10);
            gpio_put_all( blindcomtab[i]);
            sleep_ms(100);
        }
    }
    gpio_clr_mask(T_ALL);
}

void sync_rotation()
{
    uint32_t hallcomtab[8] = HCTAB;
    uint32_t state = 0, prev_state = 0;

    while(1)
    {
        while( state == prev_state ) state = (gpio_get_all() >> 16) - 256;
        prev_state = state;
        gpio_clr_mask(T_ALL);
        sleep_us(10);
        gpio_put_all( hallcomtab[state]);
        printf("State: %d\n", state);
    }
}

int main()
{
    stdio_init_all();
    sleep_ms(5000);
    printf("Inverter online");

    gpio_init_mask( T_ALL | H_ALL );
    gpio_clr_mask( T_ALL );
    gpio_set_dir_out_masked( T_ALL );

    gpio_set_dir_in_masked( H_ALL );

    gpio_set_function( 14, GPIO_FUNC_PWM);
    gpio_set_function( 15, GPIO_FUNC_PWM);

    pwm_set_wrap(7, 60000);
    pwm_set_chan_level(7, PWM_CHAN_A, 40000);
    pwm_set_chan_level(7, PWM_CHAN_B, 20000);
    pwm_set_enabled(7, true);

    //blind_rotation(10000);
    sync_rotation();
}
