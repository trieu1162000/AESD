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

