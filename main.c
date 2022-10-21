#include <pico/stdio.h>
#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include "bridge.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

uint16_t adc_raw[4] __attribute__((aligned(8)));
dma_channel_config cfg;
uint dma_chan;

#define LED 25

void adc_test();
void adc_dma();

void hall_irq( uint gpio, uint32_t events )
{
    uint32_t state = ( gpio_get_all() & (H_ALL) ) >> 16;
    printf("State: %lu\n", state);
}

void irq_work()
{
    uint32_t run = 1;

    gpio_set_irq_enabled_with_callback( H1, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    gpio_set_irq_enabled_with_callback( H2, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    gpio_set_irq_enabled_with_callback( H3, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, 1, hall_irq);
    puts("IRQ ENABLED");

    while(run)
    {
        switch( getchar_timeout_us(0) )
        {
            case 'e':;
            case 'E': run = 0; break;

            default: break;
        }
    }
    irq_set_enabled(IO_IRQ_BANK0, 0);
}

int main()
{
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false);

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 1);

    for (uint32_t i = 0; i < 50; ++i)
    {
        puts("Waiting...");
        sleep_ms(100);
        gpio_xor_mask((1<<LED));
    }

    puts("Inverter online");

    gpio_init_mask(  H_ALL );
    gpio_set_dir_in_masked( H_ALL );

    bridge_init();

    //adc_test();
    //adc_dma();

    while(1)
    {
        switch( getchar_timeout_us(0) )
        {
            case 'm':;
            case 'M': manual_step(); break;

            case 's':;
            case 'S': sync_rotation(); break;

            case 'q':;
            case 'Q': irq_work(); break;

            default: break;
        }
        gpio_xor_mask((1<<LED));
        sleep_ms(100);
        puts("Idle");
    }
}

void adc_dma()
{
    // Init GPIO for analogue use: hi-Z, no pulls, disable digital input buffer.
    adc_gpio_init(29);
    adc_gpio_init(28);
    adc_gpio_init(27);
    adc_gpio_init(26);
    adc_init();
    //adc_select_input(2);
    adc_set_round_robin(15);
    adc_fifo_setup(
            true,    // Write each completed conversion to the sample FIFO
            true,    // Enable DMA data request (DREQ)
            1,       // DREQ (and IRQ) asserted when at least 1 sample present XXX
            true,   // We won't see the ERR bit because of 8 bit reads; disable. XXX
            false     // Shift each sample to 8 bits when pushing to FIFO XXX
    );

    adc_set_clkdiv(0);

    printf("Arming DMA\n");

    // Set up the DMA to start transferring data as soon as it appears in FIFO
    dma_chan = dma_claim_unused_channel(true);
    cfg = dma_channel_get_default_config(dma_chan);

    // Reading from constant address, writing to incrementing byte addresses
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, false);
    channel_config_set_write_increment(&cfg, true);
    channel_config_set_ring(&cfg, true, 3);

    // Pace transfers based on availability of ADC samples
    channel_config_set_dreq(&cfg, DREQ_ADC);

    dma_channel_configure(dma_chan, &cfg,
                          adc_raw,    // dst
                          &adc_hw->fifo,  // src
                          0xFFFF,  // transfer count
                          true            // start immediately
    );

    printf("Starting capture\n");
    adc_run(true);

    for(;;)
    {
        gpio_xor_mask((1<<25));
        printf("%u %u %u %u %s\n", adc_raw[0], adc_raw[1], adc_raw[2], adc_raw[3],\
        dma_channel_is_busy(dma_chan)?"DMA Busy":"DMA Idle");
        if( !dma_channel_is_busy(dma_chan) )
        {
            puts("Restarting DMA & ADC");
            adc_run(false);
            adc_fifo_drain();
            dma_channel_set_write_addr(dma_chan, adc_raw, true);
            //dma_channel_start(dma_chan);
            adc_select_input(0);
            adc_run(true);
        }
        //dma_channel_set_trans_count(dma_chan, 0xFFFF, false);
        sleep_ms(100);
    }
}

void adc_test()
{
    uint16_t result;

    adc_init();
    adc_gpio_init(28);
    adc_select_input(2);

    for(;;)
    {
        result = adc_read();
        printf("%u", result);
        sleep_ms(100);
    }
}