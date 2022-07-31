#ifndef FALOWNIK_OLD_BRIDGE_H
#define FALOWNIK_OLD_BRIDGE_H

/*
 * sterowanie po lewej
 * 0-5 fazy (od usb 0, 1, GND, 2-5
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

#define S0 (A_L | B_H)
#define S1 (A_L | C_H)
#define S2 (B_L | C_H)
#define S3 (B_L | A_H)
#define S4 (C_L | A_H)
#define S5 (C_L | B_H)

#define H1 (1<<16)
#define H2 (1<<17)
#define H3 (1<<18)

#define T_PWM_PIN (1<<14)
#define R_PWM_PIN (1<<15)

#define T_ALL A_L|B_L|C_L|A_H|B_H|C_H
#define H_ALL H1|H2|H3

#define MAX_CS 6

#define SWTESTTAB {A_L, B_L, C_L, A_H, B_H, C_H}

#define COMTABLE {S0,S1,S2,S3,S4,S5}

#define HCTAB {S2,S3,0,S4,S1,0,S0,S5} //shift +1

#endif //FALOWNIK_OLD_BRIDGE_H
