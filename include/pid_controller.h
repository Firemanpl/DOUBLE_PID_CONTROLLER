#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

#define MOTOR_A_Kp 1.2
#define MOTOR_A_Ki 0.025
#define MOTOR_A_Kd 0

void PID_Init(motor_str *m, int max);
void PID_calculate(motor_str *);

#endif