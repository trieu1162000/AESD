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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|
                          GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
}

void exportToLEDs(uint8_t count){

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
                 GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, count);

}

int main(void)
{
    uint8_t count = 0;

    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    // Initialize GPIO
    configureGPIO();

    while(1)
    {
        // Check count value is out of range or not (0-255)
        if (count > 255)
            count = 0;

        // Export count value to LED
        exportToLEDs(count);

        // Delay 1 second
        SysCtlDelay(SysCtlClockGet() / 3);

        // Increase count value
        count ++;
    }
}
