#include <pico/stdio.h>
#include <hardware/gpio.h>
#include "bridge.h"

void init();

int main()
{
    init();

    //adc_test();
    //adc_dma();

    pc_control();
}

void init()
{
    stdio_init_all();
    //stdio_set_translate_crlf(&stdio_usb, false);

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 1);

    bridge_init();
}