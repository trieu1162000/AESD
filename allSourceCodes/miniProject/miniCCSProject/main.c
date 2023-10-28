#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"
#include "my_libs/inc/config_peripherals_api.h"
#include "my_libs/inc/rc522_api.h"
#include "my_libs/inc/uart_api.h"

#define CARD_LENGTH 10
#define MAX_LEN 16

unsigned char str[MAX_LEN];
unsigned char cardID[CARD_LENGTH];

void initLeds(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
}

void dumpHex(unsigned char* buffer, int len);


int main(void) {

    int8_t status;
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    configureUART();
    configureSPI();
    initLeds();
    UARTStringPut(UART0_BASE, "SSI Enabled! SPI Mode!  \r\nData: 8bits.\n\r");
    rc522Init();


    while(1){
        status = rc522Request(PICC_REQIDL, str);
        if(status == MI_OK){
            UARTStringPut(UART0_BASE, "Cartao Detectado! \r\n"); //Card Detected
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, HIGH_PIN);
        }

        status = rc522Anticoll(str);
        memcpy(cardID, str, 10);

        if(status == MI_OK){
            UARTStringPut(UART0_BASE, "ID: \n\r");
            dumpHex((unsigned char *)cardID, CARD_LENGTH);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LOW_PIN);
            SysCtlDelay(SysCtlClockGet()/2); //Delay
        }
    }
}


void dumpHex(unsigned char* buffer, int len){
    int i;
    char tempBuffer[10] = {'\0'};

    UARTStringPut(UART0_BASE, " ");
    for(i=0; i < len; i++) {
        sprintf(tempBuffer, "0x%x, ", buffer[i]);
        UARTStringPut(UART0_BASE, tempBuffer);
    }
    UARTStringPut(UART0_BASE, "  FIM! \r\n"); //End

}
