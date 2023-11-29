#ifndef INVERTER_BRIDGE_H
#define INVERTER_BRIDGE_H

#include <hardware/pwm.h>
#include <pico/stdio.h>
//#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include "hardware/irq.h"
#include "comms.h"

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
#define ALPHA_TAB { 180, 240, 0xFFFF, 300, 120, 0xFFFF, 60, 0 }

#define DEAD_TIME 10 //us

#define PWM_MAX 60000

void bridge_init();
int manual_step();
void set_pwm_all( uint16_t pwm_l, uint16_t pwm_h);
void set_out_state( int step, uint16_t pwm_l, uint16_t pwm_h );
void rotate_stupid( volatile rt_data* rundata, int state);
void step( volatile rt_data* rundata );
void hall_irq( uint gpio, uint32_t events );
int sin_16( int angle );

#define SIN_180 { 0, 573, 1147, 1720, 2292, 2864, 3435, 4004, 4573, 5140, 5706, 6270, 6831, 7391, 7949, 8504, 9056, \
9606, 10153, 10697, 11237, 11774, 12307, 12837, 13363, 13884, 14402, 14914, 15423, 15926, 16425, 16919, 17407, 17891, \
18368, 18840, 19307, 19767, 20221, 20670, 21111, 21547, 21975, 22397, 22813, 23221, 23622, 24016, 24402, 24781, 25152, \
25516, 25872, 26220, 26560, 26892, 27215, 27530, 27837, 28136, 28425, 28706, 28978, 29241, 29496, 29741, 29977, 30204, \
30422, 30630, 30829, 31019, 31199, 31370, 31530, 31682, 31823, 31955, 32077, 32189, 32292, 32384, 32467, 32539, 32602, \
32654, 32697, 32730, 32752, 32765, 32767, 32760, 32742, 32715, 32677, 32629, 32572, 32504, 32427, 32339, 32242, 32134, \
32017, 31890, 31754, 31607, 31451, 31285, 31110, 30925, 30731, 30527, 30314, 30092, 29860, 29620, 29370, 29111, 28843, \
28567, 28281, 27987, 27685, 27374, 27055, 26727, 26391, 26047, 25695, 25335, 24968, 24593, 24210, 23820, 23422, 23018, \
22606, 22187, 21762, 21330, 20891, 20446, 19995, 19538, 19074, 18605, 18130, 17650, 17164, 16673, 16176, 15675, 15169, \
14659, 14143, 13624, 13100, 12573, 12041, 11506, 10967, 10425, 9880, 9332, 8781, 8227, 7670, 7112, 6551, 5988, 5423, \
4857, 4289, 3720, 3149, 2578, 2006, 1433, 860, 287 }

#endif //INVERTER_BRIDGE_H
