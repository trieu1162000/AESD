
//*****************************************************************************
//
// These UART API are supposed to be used for 2 purposes: 
// Debug logs in terminal
// Transmit/recieve to/from Desktop App by CC2530 Module
//
//*****************************************************************************

#include "uart_api.h"

void configureUART(void){

    // TBD. Need to update for using two UART Peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

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

