#ifndef INVERTER_POSITION_H
#define INVERTER_POSITION_H

#include "hardware/gpio.h"

#define H1 0 //red
#define H2 1 //green
#define H3 2 //violet

#define ENC_A 7 //
#define ENC_B 9 //
#define ENC_Z 8 //

#define ENC_MASK (1<<ENC_A)|(1<<ENC_B)|(1<<ENC_Z)
#define H_ALL (1<<H1)|(1<<H2)|(1<<H3)

#define ALPHA_TAB { 180, 240, 0xFFFF, 300, 120, 0xFFFF, 60, 0 }

#define ENC_OFFSET 0


void pos_irq( uint gpio, uint32_t events );
void enc_init();
void hall_init();

#endif //INVERTER_POSITION_H
