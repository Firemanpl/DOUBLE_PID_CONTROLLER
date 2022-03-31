#include "main.h"

void L298N_5AD_init(motor_str *m)
{
    gpio_set_function(m->PWMmotor_1, GPIO_FUNC_PWM);
    gpio_set_function(m->PWMmotor_2, GPIO_FUNC_PWM);

    m->slice_1 = pwm_gpio_to_slice_num(m->PWMmotor_1);
    m->slice_2 = pwm_gpio_to_slice_num(m->PWMmotor_2);
    if (m->slice_1 != m->slice_2)
    {
        printf("Pwm pin isn't the same slice");
    }

    m->channel_1 = pwm_gpio_to_channel(m->PWMmotor_1);
    m->channel_2 = pwm_gpio_to_channel(m->PWMmotor_2);

    pwm_set_wrap(m->slice_1, 1000);
    pwm_set_wrap(m->slice_2, 1000);
}

void L298N_5AD_set_motor(motor_str *m)
{
    if (m->motorDirection == Direct)
    {
        pwm_set_chan_level(m->slice_1, m->channel_1, m->actual_PWM);
        pwm_set_chan_level(m->slice_1, m->channel_2, 0);
        pwm_set_enabled(m->slice_1, true);
    }
    else if (m->motorDirection == Reverse)
    {
        pwm_set_chan_level(m->slice_1, m->channel_2, m->actual_PWM);
        pwm_set_chan_level(m->slice_1, m->channel_1, 0);
        pwm_set_enabled(m->slice_1, true);
    }
}
void L298N_5AD_set_motor_Breake(motor_str *m)
{
    pwm_set_chan_level(m->slice_1, m->channel_1, 1000);
    pwm_set_chan_level(m->slice_1, m->channel_2, 1000);
    pwm_set_enabled(m->slice_1, true);
}
