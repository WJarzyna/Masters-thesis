#include "pid.h"

void pid_init( pid_i* pid, int32_t i_limit, int32_t o_max, int32_t o_min )
{
    pid->t = 0;
    pid->e_prev = 0;
    pid->i_sum = 0;
    pid->i_limit = i_limit;
    pid->o_max = o_max;
    pid->o_min = o_min;
}

void pid_tune( pid_i* pid, int32_t kp, int32_t ki, int32_t kd )
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}
int32_t pid_calc( pid_i* pid, int32_t u, int32_t q )
{
    int32_t e, d, de, i, out;
    uint32_t dt;

    e = u - q;
    de = e - pid->e_prev;
    pid->e_prev = e;

    dt = time_us_32() - pid->t;
    pid->t = time_us_32();

    i = e * (dt/1000);
    pid->i_sum = LIMIT(pid->i_sum+i, -pid->i_limit, pid->i_limit);

    d = (de*1000)/dt;

    out = pid->kp*e + pid->ki*pid->i_sum + pid->kd*d;

    return LIMIT(out, pid->o_min, pid->o_max);
}