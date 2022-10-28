#ifndef INVERTER_COMMS_H
#define INVERTER_COMMS_H

#include <pico/stdio.h>
#include <pico/printf.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>

#define MAX_RX_LEN 10

#define INFO_ERR 0xFF

#define LED 25

enum Modes{ MODE_IDLE, MODE_SYNC_POLL, MODE_SYNC_IRQ, MODE_VECT, MODE_MAN_STEP, MODE_ERR};
enum Regs{ REG_MODE, REG_PWM_L, REG_PWM_H, REG_PWM_R, REG_DIR, REG_STATE, REG_DT, REG_C_STATE};
enum Cmds{ CMD_EXIT, CMD_STOP, CMD_BRAKE, CMD_WREG, CMD_RREG, CMD_STEP, CMD_START};
enum Errors{ ERR_NONE, ERR_TOUT, ERR_OC, ERR_OV, ERR_INV_CMD, ERR_NOT_IMPL};

extern int sync_rotation();
extern int manual_step();
extern int irq_work();
void pc_control();

#endif //INVERTER_COMMS_H
