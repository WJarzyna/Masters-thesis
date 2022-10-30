#ifndef INVERTER_BRIDGE_H
#define INVERTER_BRIDGE_H

#include <hardware/pwm.h>
#include <pico/stdio.h>
#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include "hardware/irq.h"
#include "comms.h"

typedef struct
{
    uint16_t pwm_l, pwm_h, pwm_r, dir;
    uint32_t dt;
}rt_data;

/*
 * sterowanie po lewej
 * 0-5 fazy (od usb 0, 1, GND, 2-5 braz-czerw-masa-nieb-ziel-nieb-szary
 * pwm na dole
 * 14 rotor PWM7A
 * 15 main PWM7B
 * sensory 16, 17, 18 (od dolu od prawej)
 */

#define PH_A 0
#define PH_B 1
#define PH_C 2


#define A_L 0
#define A_H 1
#define B_L 2
#define B_H 3
#define C_L 4
#define C_H 5

#define CTAB_AH { 0, 0, 0, 1, 1, 0 }
#define CTAB_AL { 1, 1, 0, 0, 0, 0 }
#define CTAB_BH { 1, 0, 0, 0, 0, 1 }
#define CTAB_BL { 0, 0, 1, 1, 0, 0 }
#define CTAB_CH { 0, 1, 1, 0, 0, 0 }
#define CTAB_CL { 0, 0, 0, 0, 1, 1 }

#define H1 16 //red
#define H2 17 //green
#define H3 18 //violet

#define H_ALL (1<<H1)|(1<<H2)|(1<<H3)

// 0-1-3-7-6-4
#define TRTAB { 3, 4, 254, 5, 2, 254, 1, 0} //base hall->corresponding commutation

#define DEAD_TIME 10

#define FWD 1

#define PWM_MAX 60000

int sync_rotation();
void bridge_init();
int manual_step();
void set_pwm_all( uint16_t pwm_l, uint16_t pwm_h);
void send_reg_16( int name, uint16_t reg);
void rx_data( int rx[], int advance );
int parse_wreg( int* run, volatile rt_data* data, const int rx[] );
void set_out_state( int step, uint16_t pwm_l, uint16_t pwm_h );
void rotate_stupid( volatile rt_data* rundata, int state);
void step( volatile rt_data* rundata );
void hall_irq( uint gpio, uint32_t events );
int irq_work();
void zero_rundata( volatile rt_data* rundata);

#endif //INVERTER_BRIDGE_H
