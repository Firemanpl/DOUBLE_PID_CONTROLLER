#include "main.h"
#include <math.h>
void PID_Init(motor_str *m, int max)
{
    m->max = max;
    m->motorDirection = Direct;
}

void PID_calculate(motor_str *m)
{
    uint32_t prevT = 0;
    float eprev = 0;
    float eintegral = 0;
    uint32_t currT = time_us_32();
    float deltaT = ((float)(currT - prevT / 1e6));
    int e = m->pulse_count - m->set_target;
    float dedt = (e - eprev) / (deltaT);
    eintegral = eintegral + e * deltaT;
    float u = MOTOR_A_Kp * e + MOTOR_A_Ki * dedt + MOTOR_A_Kd * eintegral;
    int pwr = (int)fabs(u);
    if (pwr > m->max)
        pwr = m->max;
    if (u < 0) // negative value: CCW
        m->motorDirection = -1;
    else if (u > 0) // positive: CW
        m->motorDirection = 1;
    m->actual_PWM = pwr;
    eprev = e;
}