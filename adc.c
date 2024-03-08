#include "adc.h"

uint16_t adc_raw[4] __attribute__((aligned(8)));
uint dma_chan;



static void adc_dma_keepalive()
{
    // Clear the interrupt request.
    dma_hw->ints0 = 1u << dma_chan; // el classico
//    dma_channel_acknowledge_irq0( dma_chan );  // SDK maybe?
    // Re-trigger, count is just for func requirements
    dma_channel_set_trans_count(dma_chan, ADC_DMA_XFER_CNT, true);
}



void adc_init_dma_irq_keepalive()
{
    dma_channel_config cfg;

    adc_gpio_init(29); // Pins init
    adc_gpio_init(28);
    adc_gpio_init(27);
    adc_gpio_init(26);
    adc_init();

    adc_set_round_robin(0x0F);  // round sample ADC0--ADC3
    adc_fifo_setup( true,             // Write each completed conversion to the sample FIFO
                    true,       // Enable DMA data request (DREQ)
                    1,       // DREQ (and IRQ) asserted when at least 1 sample present
                    true,       // 2 byte read, ERR flag on bit 15
                    false );    // No alignment


    adc_set_clkdiv(0);

    dma_chan = dma_claim_unused_channel(true); // DMA get channel
    cfg = dma_channel_get_default_config(dma_chan);

    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, false); // Reading from constant address (ADC FIFO addr)
    channel_config_set_write_increment(&cfg, true); // writing to incrementing byte addresses
    channel_config_set_ring(&cfg, true, 3); // in ring fashion (4 locations)

    channel_config_set_dreq(&cfg, DREQ_ADC); // enable ADC transfer requests

    dma_channel_set_irq0_enabled(dma_chan, true); // Raise DMA IRQ0 when done (should be rare)

    irq_set_exclusive_handler(DMA_IRQ_0, adc_dma_keepalive); // set handler
    irq_set_enabled(DMA_IRQ_0, true);

    dma_channel_configure(dma_chan, &cfg,
                          adc_raw,          // dst
                          &adc_hw->fifo,    // src
                          ADC_DMA_XFER_CNT,   // transfer count
                          true );            // start immediately

    adc_run(true); // start the shitshow
}
