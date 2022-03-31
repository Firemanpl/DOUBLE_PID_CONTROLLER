#include "main.h"

void GPIO_init_for_calibrate(motor_str *mA, motor_str *mB)
{
	// set L298N_5AD pins
	gpio_init(X_axis_1);
	gpio_set_dir(X_axis_1, GPIO_IN);
	gpio_init(X_axis_2);
	gpio_set_dir(X_axis_2, GPIO_IN);
	gpio_init(Y_axis_1);
	gpio_set_dir(Y_axis_1, GPIO_IN);
	gpio_init(Y_axis_2);
	gpio_set_dir(Y_axis_2, GPIO_IN);
}

void calibrate_motor(motor_str *mA, motor_str *mB, uint8_t pwm, bool *calibrate_end)
{

	mA->actual_PWM = pwm;
	mB->actual_PWM = pwm;
	//		Motor - A
	while (1)
	{
		mA->motorDirection = Direct;
		if (gpio_get(X_axis_1) != 1)
		{
			L298N_5AD_set_motor(mA);
		}
		else
		{
			mA->pulse_count = 0;
			mA->set_target = 0;
			L298N_5AD_set_motor_Breake(mA);

			break;
		}
	}
	while (1)
	{
		mA->motorDirection = Reverse;
		if (gpio_get(X_axis_2) != 1)
		{
			L298N_5AD_set_motor(mA); /* code */
		}
		else
		{
			L298N_5AD_set_motor_Breake(mA);
			mA->set_target = mA->pulse_count / 2;
			break;
		}
	}
	//			Motor - B
	while (1)
	{
		mA->motorDirection = Direct;
		if (gpio_get(Y_axis_1) != 1)
		{
			L298N_5AD_set_motor(mB);
		}
		else
		{
			bool block_while_1;
			mB->pulse_count = 0;
			mB->set_target = 0;
			L298N_5AD_set_motor_Breake(mB);
			// delay
			break;
		}
	}
	while (1)
	{
		mB->motorDirection = Reverse;
		if (gpio_get(Y_axis_2) != 1)
		{
			L298N_5AD_set_motor(mB); /* code */
		}
		else
		{
			L298N_5AD_set_motor_Breake(mB);
			mB->set_target = mB->pulse_count / 2;
			break;
		}
	}

	// Summary calibration Motor A & B

	while (1)
	{
		PID_calculate(mA);
		PID_calculate(mB);
		L298N_5AD_set_motor(mA);
		L298N_5AD_set_motor(mB);
		if (mA->set_target == mA->pulse_count && mB->set_target == mB->pulse_count)
		{
			*calibrate_end = true;
			break;
		}
	}
}
bool save_delay(uint32_t time)
{
	uint32_t savedTime;
	uint32_t actualTime = time_us_32();
	uint32_t timeDifference = actualTime - savedTime;

	if (timeDifference >= time)
	{
		savedTime = actualTime;
		return true;
	}
}
