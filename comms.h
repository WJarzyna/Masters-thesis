#ifndef INVERTER_COMMS_H
#define INVERTER_COMMS_H


#include <hardware/gpio.h>
#include "usb_cdc.h"

#include "pid.h"

#define MAX_RX_LEN 10

#define INFO_ERR 0xFF

#define FWD 1

#define LED 25

typedef union
{
    uint8_t bytes[2];
    uint32_t reg;
} reg16;

typedef struct
{
    uint16_t pwm_l, pwm_h, pwm_r, dir, speed, set_speed, alpha;
    uint32_t dt, t;
} rt_data;

enum Modes{ MODE_IDLE, MODE_SPEED_CTL, MODE_SYNC_IRQ, MODE_VECT, MODE_MAN_STEP, MODE_ERR};

enum Regs{ REG_MODE=1, REG_PWM_L, REG_PWM_H, REG_PWM_R, REG_DIR, REG_STATE, REG_SPEED, REG_C_STATE,\
REG_SET_SPEED, REG_PID_P, REG_PID_I, REG_PID_D};

enum Cmds{ CMD_NONE, CMD_EXIT, CMD_STOP, CMD_BRAKE, CMD_WREG, CMD_RREG, CMD_STEP, CMD_START};

enum Errors{ ERR_NONE, ERR_TOUT, ERR_OC, ERR_OV, ERR_INV_CMD, ERR_NOT_IMPL};

enum Led_States{ LED_OFF, LED_BSLOW, LED_BFAST, LED_ON};

void comms_init();
extern int manual_step();
void pc_control();
extern int speed_ctrl( int pid );
int parse_wreg( int* run, volatile rt_data* data, volatile pid_i* pid, const uint8_t rx[] );
void zero_rundata( volatile rt_data* data);

inline void send_reg_8( int name, int reg)
{
    uint8_t buf[3];
    buf[0] = name;
    buf[1] = reg;
    buf[2] = 0;
    usb_cdc_write(buf, 3);
}

inline void send_reg_16( int name, uint16_t reg)
{
    reg16 reg_u;
    reg_u.reg = reg;

    uint8_t buf[3];
    buf[0] = name;
    buf[1] = reg_u.bytes[1];
    buf[2] = reg_u.bytes[0];

    usb_cdc_write(buf, 3);
};

#endif //INVERTER_COMMS_H
