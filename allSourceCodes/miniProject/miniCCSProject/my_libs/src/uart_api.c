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
    int8_t i = 0;
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
    while (!UARTCharsAvail(UART1_BASE))
    {

        // Read a byte
        rawReceivedFrame[i] = UARTCharGetNonBlocking(UART1_BASE);
        i++;

    }

    // Raise an ISR Receive Flag
    ISRReceiveFlag = true;

}
