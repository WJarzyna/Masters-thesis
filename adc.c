#include "adc.h"

void adc_dma()
{
    // Init GPIO for analogue use: hi-Z, no pulls, disable digital input buffer.
    adc_gpio_init(29);
    adc_gpio_init(28);
    adc_gpio_init(27);
    adc_gpio_init(26);
    adc_init();

    adc_set_round_robin(15);
    adc_fifo_setup( true,    // Write each completed conversion to the sample FIFO
                    true,    // Enable DMA data request (DREQ)
                    1,       // DREQ (and IRQ) asserted when at least 1 sample present
                    true,   // 2 byte read, ERR flag on bit 15
                    false );    // No alignment


    adc_set_clkdiv(0);

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
                          0xFFFFFFFF,  // transfer count
                          true );           // start immediately

    adc_run(true);

    for(;;)
    {
        gpio_xor_mask((1<<LED));
        printf("%u %u %u %u %s\n", adc_raw[0], adc_raw[1], adc_raw[2], adc_raw[3],\
        dma_channel_is_busy(dma_chan)?"DMA Busy":"DMA Idle");

        if( !dma_channel_is_busy(dma_chan) )
        {
            puts("Restarting DMA & ADC");
            adc_run(false);
            adc_fifo_drain();
            dma_channel_set_write_addr(dma_chan, adc_raw, true);
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