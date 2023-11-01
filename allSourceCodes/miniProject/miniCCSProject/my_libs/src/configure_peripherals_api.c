/*
 * configure_peripherals_api.c
 *
 *  Created on: Oct 27, 2023
 *      Author: trieu
 */

#include "../inc/config_peripherals_api.h"

void enablePeriphs(void){
    // TBD
}

void configureI2C(void){
    //
    // Enable the I2C0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    //
    // Initialize Master and Slave
    //
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), true);
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;

}

void configureSPI(void){
    uint32_t junkAuxVar;

    // TBD. Need to accordingly change Port and Pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
//    GPIOPinConfigure(GPIO_PD1_SSI3FSS);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1); // CS Pin
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1); // RST Pin
    GPIOPinConfigure(GPIO_PD2_SSI3RX);
    GPIOPinConfigure(GPIO_PD3_SSI3TX);
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_0);
    SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 4000000, 8);

    SSIEnable(SSI3_BASE);

    while(SSIDataGetNonBlocking(SSI3_BASE, &junkAuxVar)){}

}


void configureUART(void){

    // TBD. Need to update for using two UART Peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

