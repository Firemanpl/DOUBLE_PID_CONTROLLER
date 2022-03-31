#include "main.h"
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
            ReceivedDataFlag = 1;
        }
        else
        {
            break;
        }
    }
    return buffer_index;
}

void receive_message(int32_t *TargetXAxis, int32_t *TargetYAxis, uint8_t *ReceivedData)
{
    char *pEnd;
    if (ReceivedDataFlag == 1)
    {
        if (ReceivedData[0] == 'X' && strchr((const char *)ReceivedData, 'Y') != NULL)
        {
            *TargetXAxis = strtol((const char *)ReceivedData + 1, &pEnd, 10);
            *TargetYAxis = strtol(pEnd + 1, NULL, 10);
            printf("\nOK X=%ld Y=%ld\n", *TargetXAxis, *TargetYAxis);
        }
        else if (ReceivedData[0] == 'C')
        {
            // calibrate motor function not added yet
            printf("Calibration in progress...\n");
            // calibrate_motor();
        }
        else if (ReceivedData[0] == 'F')
        {
            FireFlag++;
            printf("OK\n");
        }
        else
        {
            printf("BAD_SYNTAX!\n");
        }
        ReceivedDataFlag = 0;
    }
}