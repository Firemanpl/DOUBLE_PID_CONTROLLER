#ifndef MOTOR_CALIBRATION_H_
#define MOTOR_CALIBRATION_H_

#define X_axis_1 10
#define X_axis_2 11
#define Y_axis_1 12
#define Y_axis_2 13

void GPIO_init_for_calibrate();
bool save_delay(uint32_t);
typedef struct
{
    int32_t pulse_count;
    volatile int32_t set_target;
    int actual_PWM;
    int max;
    int8_t motorDirection;
    uint8_t PWMmotor_1;
    uint8_t PWMmotor_2;
    uint8_t channel_1;
    uint8_t channel_2;
    uint8_t slice_1;
    uint8_t slice_2;
} motor_str;

enum Direction
{
    Direct = 1,
    Reverse = -1
};

#endif