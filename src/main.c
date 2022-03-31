#include "main.h"

// pins for driver L298N_5AD
#define CW_MOTOR_1 6
#define CCW_MOTOR_2 7
#define CW_MOTOR_3 8
#define CCW_MOTOR_4 9

// init encoder 1
const uint PIN_AB1 = 2;
PIO pio_1 = pio0;
const uint sm = 0;
// init encoder 2
const uint PIN_AB2 = 4;
PIO pio_2 = pio1;

motor_str motorA, motorB;

uint8_t ReceivedData[42];
uint8_t FireFlag;

int main(void)
{
    stdio_init_all();
    GPIO_init_for_calibrate();
    uint offset_1 = pio_add_program(pio_1, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio_1, sm, offset_1, PIN_AB1, 0);
    uint offset_2 = pio_add_program(pio_2, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio_2, sm, offset_2, PIN_AB2, 0);
    PID_Init(&motorA, 1000);
    PID_Init(&motorB, 1000);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (true)
    {

        motorA.pulse_count = quadrature_encoder_get_count(pio_1, sm) / 4;
        motorB.pulse_count = quadrature_encoder_get_count(pio_2, sm) / 4;
        int8_t buf = buffor_start(ReceivedData);

        // for (int8_t i = 0; i < buf; i++)
        // {
        //     printf("%c", ReceivedData[i]);
        // }

        receive_message(&motorA.set_target, &motorB.set_target, ReceivedData);
        PID_calculate(&motorA);
        PID_calculate(&motorB);
        L298N_5AD_set_motor(&motorA);
        L298N_5AD_set_motor(&motorB);

        if (motorA.set_target == motorA.pulse_count && motorB.set_target == motorB.pulse_count)
        {
            // may be fire
        }

        printf("EC(A):%ld PWM(A):%d Target(A):%ld Direction(A):%d\n", motorA.pulse_count, motorA.actual_PWM, motorA.set_target, motorA.motorDirection);
        printf("EC(B):%ld PWM(B):%d Target(B):%ld Direction(B):%d\n", motorB.pulse_count, motorB.actual_PWM, motorB.set_target, motorB.motorDirection);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(100);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(100);
    }
    return 0;
}
