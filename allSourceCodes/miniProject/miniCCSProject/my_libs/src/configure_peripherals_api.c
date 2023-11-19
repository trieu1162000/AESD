/*
 * configure_peripherals_api.c
 *
 *  Created on: Oct 27, 2023
 *      Author: trieu
 */

#include "../inc/config_peripherals_api.h"

void initPeriphs(void){
    // TBD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
}

void configureI2C(void){
    //
    // Enable the I2C0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
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

void initSPIIRQ(void (*pIRQHandler)(void))
{
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTE_BASE, pIRQHandler);
    IntEnable(INT_GPIOE);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_PIN_2);
    IntMasterEnable();

}

void configureSPI(void){
    uint32_t junkAuxVar;

    // TBD. Need to accordingly change Port and Pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);

    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
//    GPIOPinConfigure(GPIO_PD1_SSI3FSS);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1); // CS Pin
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2); // IRQ Pin
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

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

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

#ifdef DEBUG
void initConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
#endif
