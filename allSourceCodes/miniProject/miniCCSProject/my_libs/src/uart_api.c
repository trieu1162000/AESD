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

uint8_t receiveFrame[FRAME_LENGTH];

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
    while (1) {
        // Wait until the UART receiver has data
        while (!UARTCharsAvail(UART1_BASE));

        // Read a byte
        char receivedByte = UARTCharGetNonBlocking(UART1_BASE);

        // Check for the header (0xFFAA)
        if (i == 0 && receivedByte == 0xFF) {
            receiveFrame[i++] = receivedByte;  // Start of the potential header
        } else if (i == 1 && receivedByte == 0xAA) {
            receiveFrame[i++] = receivedByte;  // Second byte of the header
            break;  // Exit the loop since the header is detected
        } else {
            // Reset if the received byte does not match the header
            i = 0;
        }
    }

    // Continue reading the rest of the receiveFrame
    for (; i < 5; i++) {
        // Wait until the UART receiver has data
        while (!UARTCharsAvail(UART1_BASE));

        // Read a byte
        receiveFrame[i] = UARTCharGetNonBlocking(UART1_BASE);
    }

    // Raise an ISR Receive Flag
    ISRReceiveFlag = true;

}
