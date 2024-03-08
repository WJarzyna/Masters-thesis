#ifndef INVERTER_ADC_H
#define INVERTER_ADC_H

#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

#define ADC_DMA_XFER_CNT 0xFFFFFFFF

void adc_init_dma_irq_keepalive();

#endif //INVERTER_ADC_H
