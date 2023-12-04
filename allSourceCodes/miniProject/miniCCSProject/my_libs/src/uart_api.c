/*
 * uart_api.c
 *
 *  Created on: Oct 27, 2023
 *      Author: trieu
 */


//*****************************************************************************
//
// These UART API are supposed to be used for 2 purposes: 
// Debug logs in terminal
// Transmit/recieve to/from Desktop App by CC2530 Module
//
//*****************************************************************************

#include "../inc/uart_api.h"

uint8_t rawReceivedFrame[MAX_FRAME_LENGTH] = {0};
uint8_t mainFrame[MAX_FRAME_LENGTH] = {0};

// uint8_t rawReceivedFrame[MAX_FRAME_LENGTH] = {0};

uint8_t receivedFrameIndex = 0;
//volatile uint8_t isInFrame = 0;

void UARTStringPut(uint32_t ui32Base,const char *str){

    size_t count;
    size_t i;
    char ch;

    count = strlen(str);
    for(i = 0; i < count; i++){
        ch = str[i];
        UARTCharPut(ui32Base, (char) ch );
    }
}

// Using UART1
void UARTIntHandler(void)
{
    uint32_t ui32Status;
    int16_t i = 0;

    //
    // Get the interrrupt status.
    //
    ui32Status = UARTIntStatus(UART1_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    UARTIntClear(UART1_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    // Wait until the UART receiver has data
    // while (UARTCharsAvail(UART1_BASE))
    // {

    //     // Read a byte
    //     rawReceivedFrame[i] = UARTCharGetNonBlocking(UART1_BASE);
    //     i++;

    // }

    while (UARTCharsAvail(UART1_BASE))
    {
        uint8_t receivedByte = UARTCharGetNonBlocking(UART1_BASE);

        rawReceivedFrame[i] = receivedByte;
        i++;
    }
    int j;
    for (j = 0; j < i && receivedFrameIndex < MAX_FRAME_LENGTH; j++) {
        mainFrame[receivedFrameIndex] = rawReceivedFrame[j];
        receivedFrameIndex++;
    }
//        // Check for the start of the frame
//        if (!isInFrame && receivedByte == FRAME_START1)
//        {
//            isInFrame = 1;
//            receivedFrameIndex = 0;
//            rawReceivedFrame[0] = receivedByte;
//        }
//        else if (isInFrame)
//        {
//            rawReceivedFrame[++receivedFrameIndex] = receivedByte;
//
//            // Check for the end of the frame
//            if (receivedByte == FRAME_END2)
//            {
//                // Process the complete frame
//                // (you can add your processing logic here)
//                receivedFrameIndex = 0;
//                // Reset for the next frame
//                isInFrame = 0;
//            }
//        }



    // Raise an ISR Receive Flag
    ISRReceiveFlag = 1;

}
