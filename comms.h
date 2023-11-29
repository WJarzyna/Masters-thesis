#ifndef INVERTER_COMMS_H
#define INVERTER_COMMS_H

#include <pico/stdio.h>
#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include "pid.h"

#define MAX_RX_LEN 10

#define INFO_ERR 0xFF

#define FWD 1

#define LED 25

typedef struct
{
    uint16_t pwm_l, pwm_h, pwm_r, dir, speed, set_speed, alpha;
    uint32_t dt, t;
} rt_data;

enum Modes{ MODE_IDLE, MODE_SPEED_CTL, MODE_SYNC_IRQ, MODE_VECT, MODE_MAN_STEP, MODE_ERR};

enum Regs{ REG_MODE, REG_PWM_L, REG_PWM_H, REG_PWM_R, REG_DIR, REG_STATE, REG_SPEED, REG_C_STATE,\
REG_SET_SPEED, REG_PID_P, REG_PID_I, REG_PID_D};

enum Cmds{ CMD_EXIT, CMD_STOP, CMD_BRAKE, CMD_WREG, CMD_RREG, CMD_STEP, CMD_START};

enum Errors{ ERR_NONE, ERR_TOUT, ERR_OC, ERR_OV, ERR_INV_CMD, ERR_NOT_IMPL};

extern int manual_step();
void pc_control();
extern int speed_ctrl( int pid );
void rx_data( int rx[], int advance );
int parse_wreg( int* run, volatile rt_data* data, volatile pid_i* pid, const int rx[] );
void zero_rundata( volatile rt_data* data);

inline void send_reg_8( int name, int reg)
{
    putchar_raw(name);
    putchar_raw(reg);
}

inline void send_reg_16( int name, uint16_t reg)
{
    putchar_raw(name);
    putchar_raw(reg >> 8);
    putchar_raw(reg & 0xFF);
};

#endif //INVERTER_COMMS_H
