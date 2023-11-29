#ifndef INVERTER_ADC_H
#define INVERTER_ADC_H

#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "comms.h"

uint16_t adc_raw[4] __attribute__((aligned(8)));
dma_channel_config cfg;
uint dma_chan;

void adc_test();
void adc_dma();
void adc_init_dma();
void adc_dma_keepalive();

#endif //INVERTER_ADC_H
