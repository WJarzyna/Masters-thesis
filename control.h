#ifndef INVERTER_CONTROL_H
#define INVERTER_CONTROL_H

#include "comms.h"
#include "pid.h"
#include "adc.h"
#include "bridge.h"



int speed_ctrl( int pid );
int vect_ctrl();



#endif //INVERTER_CONTROL_H
