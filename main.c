#include "bridge.h"


void init();

void main()
{
    init();

    pc_control();
}

void init()
{
    comms_init();
    bridge_init();
    mainboard_init();
    hall_init();
    adc_init_dma_irq_keepalive();
}

