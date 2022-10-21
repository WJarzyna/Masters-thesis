#ifndef INVERTER_BRIDGE_H
#define INVERTER_BRIDGE_H

#include <hardware/pwm.h>
#include <pico/stdio.h>
#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>

void sync_rotation();
void bridge_init();
void manual_step();

/*
 * sterowanie po lewej
 * 0-5 fazy (od usb 0, 1, GND, 2-5 braz-czerw-masa-nieb-ziel-nieb-szary
 * pwm na dole
 * 14 rotor PWM7A
 * 15 main PWM7B
 * sensory 16, 17, 18 (od dolu od prawej)
 */

#define A_L (1<<0)
#define A_H (1<<1)
#define B_L (1<<2)
#define B_H (1<<3)
#define C_L (1<<4)
#define C_H (1<<5)

#define PH_A 0
#define PH_B 1
#define PH_C 2

#define S0 (A_L | B_H)
#define S1 (A_L | C_H)
#define S2 (B_L | C_H)
#define S3 (B_L | A_H)
#define S4 (C_L | A_H)
#define S5 (C_L | B_H)

#define H1 (1<<16) //red
#define H2 (1<<17) //green
#define H3 (1<<18) //violet

#define H_ALL H1|H2|H3

#define HCTAB {       S2,       S3,     0,     S4,       S1,     0,    S0,         S5} //shift +1
#define HCTAB_R { B_L | C_H, B_L | A_H, 0, C_L | A_H, A_L | C_H, 0, A_L | B_H, C_L | B_H} //shift +1
#define HCTAB_AL {    0,          0,    0,     0,         1,     0,     1,          0}
#define HCTAB_AH {    0,          1,    0,     1,         0,     0,     0,          0}
#define HCTAB_BL {    1,          1,    0,     0,         0,     0,     0,          0}
#define HCTAB_BH {    0,          0,    0,     0,         0,     0,     1,          1}
#define HCTAB_CL {    0,          0,    0,     1,         0,     0,     0,          1}
#define HCTAB_CH {    1,          0,    0,     0,         1,     0,     0,          0}
#define CTAB_AL { 0, 0, 0, 1, 1, 0 }
#define CTAB_AH { 1, 1, 0, 0, 0, 0 }
#define CTAB_BL { 1, 0, 0, 0, 0, 1 }
#define CTAB_BH { 0, 0, 1, 1, 0, 0 }
#define CTAB_CL { 0, 1, 1, 0, 0, 0 }
#define CTAB_CH { 0, 0, 0, 0, 1, 1 }

// 0-2-3-7-5-4

#endif //INVERTER_BRIDGE_H
