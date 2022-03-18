#include <stdio.h>
#include "pico/stdlib.h"
#include "communication_USB.h"

int64_t TargetXAxis, TargetYAxis;
uint8_t ReceivedData[42];
uint8_t FireFlag;
int main(void)
{
    stdio_init_all();
    printf("\n\nHello World\n");
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (true)
    {
        int8_t buf = buffor_start(ReceivedData);

        for (int8_t i = 0; i < buf; i++)
        {
            printf("%c", ReceivedData[i]);
        }
        receive_message(&TargetXAxis, &TargetYAxis, ReceivedData);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(100);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(100);
    }
    return 0;
}
