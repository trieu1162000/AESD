

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#define LED_PIN GPIO_PIN_1 // Change this based on your actual LED pin

void LEDOn(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_PIN, LED_PIN);
}

void LEDOff(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_PIN, 0);
}

int main(void)
{
    uint32_t ui32Period;
    // Set the system clock to 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Enable peripherals (GPIO and Timer)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);

    // Configure the GPIO pins
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_PIN);

    ui32Period = (SysCtlClockGet()*5);
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);
    while (1)
    {


    }
}



uint8_t Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Read the current state of the GPIO pin and
    // write back the opposite state
    // Toggle the LED state
    if (GPIOPinRead(GPIO_PORTF_BASE, LED_PIN) == 0)
        LEDOn();
    else
        LEDOff();
    return 2;
//    TimerEnable(TIMER0_BASE, TIMER_A);

}
