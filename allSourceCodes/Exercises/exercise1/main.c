#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#define PIN_HIGH    0xFF
#define PIN_LOW     0x00

//*****************************************************************************
//
// Configure the GPIO and its pins.  This must be called before generateClock().
//
//*****************************************************************************
void configureGPIO(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2);
}

void generateClock1(void){

    // High pin
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, PIN_HIGH);

    // Delay 0.5s
    SysCtlDelay(SysCtlClockGet() / 6);

    // Low pin
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, PIN_LOW);

    // Delay 0.5s
    SysCtlDelay(SysCtlClockGet() / 6);

}

void generateClock2(void){
    // High pin
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, PIN_HIGH);

    // Delay 1s
    generateClock1();

    // Low pin
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, PIN_LOW);

    // Delay 1s
    generateClock1();
}

int main(void)
{
    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    // Initialize GPIO
    configureGPIO();

    while(1)
    {
        //
        // Generate clock as required
        //
        generateClock2();
    }
}
