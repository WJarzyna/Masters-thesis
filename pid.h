#ifndef INVERTER_PID_H
#define INVERTER_PID_H

#include <pico/stdlib.h>

#define LIMIT(v,min,max) ((v)>(max)?(max):((v)<(min)?(min):(v)))

typedef struct
{
    int32_t kp, ki, kd;
    uint32_t t;
    int32_t  i_sum, e_prev, i_limit, o_max, o_min;
} pid_i;

void pid_init( pid_i* pid, int32_t i_limit, int32_t o_max, int32_t o_min );
void pid_tune( pid_i* pid, int32_t kp, int32_t ki, int32_t kd );
int32_t pid_calc( pid_i* pid, int32_t u, int32_t q );

#endif //INVERTER_PID_H
