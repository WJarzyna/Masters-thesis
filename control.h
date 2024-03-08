#ifndef INVERTER_CONTROL_H
#define INVERTER_CONTROL_H

#include "comms.h"
#include "pid.h"
#include "adc.h"
#include "bridge.h"



int speed_ctrl( int pid );
int vect_ctrl();

inline void stop( volatile rt_data* rundata )
{
//    irq_set_enabled(IO_IRQ_BANK0, 0);
    set_pwm_all_ph(0, 0);
    pwm_set_chan_level( PH_ROTOR, PWM_CHAN_B, 0);

    rundata->pwm_h = 0;
    rundata->pwm_l = 0;
    rundata->pwm_r = 0;
    rundata->set_speed = 0;
    send_reg_16( REG_PWM_H, rundata->pwm_h);
    send_reg_16( REG_PWM_L, rundata->pwm_l);
    send_reg_16( REG_PWM_R, rundata->pwm_r);
    send_reg_16( REG_SET_SPEED, rundata->set_speed);
}

#endif //INVERTER_CONTROL_H
