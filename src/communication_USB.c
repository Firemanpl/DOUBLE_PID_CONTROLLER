#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "communication_USB.h"
#include "communication_USB.h"
#include <string.h>

static uint8_t ReceivedDataFlag;
extern uint8_t FireFlag;
const uint8_t BUFFER_LENGTH = 42;

int8_t buffor_start(uint8_t *buffer)
{
    int8_t buffer_index = 0;
    while (true)
    {
        int c = getchar_timeout_us(100);
        if (c != PICO_ERROR_TIMEOUT && buffer_index <= BUFFER_LENGTH)
        {
            buffer[buffer_index++] = (c & 0xFF);
            // printf("%c", buffer[buffer_index]);
            ReceivedDataFlag = 1;
        }
        else
        {
            break;
        }
    }
    return buffer_index;
}

void receive_message(int64_t *TargetXAxis, int64_t *TargetYAxis, uint8_t *ReceivedData)
{
    static char *endXarg;
    if (ReceivedDataFlag == 1)
    {
        ReceivedDataFlag = 0;
        if (ReceivedData[0] == 'X' && strchr((const char *)ReceivedData, 'Y'))
        {
            *TargetXAxis = strtoll((const char *)ReceivedData + 1, &endXarg, 10);
            *TargetYAxis = strtoll(endXarg + 1, NULL, 10);
            printf("OK X=%ld Y=%ld\n\r", *TargetXAxis, *TargetYAxis);
        }
        else if (ReceivedData[0] == 'C')
        {
            // calibrate motor function not added yet
            printf("Calibration in progress...\n");
        }
        else if (ReceivedData[0] == 'F')
        {
            FireFlag++;
            printf("OK\n");
        }
        else
        {
            printf("BAD_SYNTAX!");
        }
    }
}