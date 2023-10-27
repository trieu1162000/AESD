#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"


void configureUART(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void configureADC(void){
    //
    // Enable the ADC0 module.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    //
    // Wait for the ADC0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    {
    }
    //
    // Enable the first sample sequencer to capture the value of channel 0 when
    // the processor trigger occurs.
    //
    ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 2, 3, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_TS);
    ADCSequenceEnable(ADC0_BASE, 2);

}

void UARTStringPut(uint32_t ui32Base,const char *str, size_t count){

    size_t i;
    char ch;

    for(i = 0; i < count; i++){
        ch = str[i];
        UARTCharPut(ui32Base, (char) ch );
    }
}

int main(void) {

    uint32_t ui32Temp[4];
    double tempAvg;
    double finalResult;
    char tempBuffer[50] = {'\0'};
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    configureUART();
    configureADC();

    while (1)
    {

        /* Measure temperature */
        // Clear the interrupt flag which indicating the ADC conversion process is complete
        ADCIntClear(ADC0_BASE, 2);
        // Trigger the sample sequence.
        ADCProcessorTrigger(ADC0_BASE, 2);
        // Wait until the sample sequence has completed.
        while(!ADCIntStatus(ADC0_BASE, 2, false));
        // Read the value from the ADC.
        ADCSequenceDataGet(ADC0_BASE, 2, ui32Temp);
        // Calculate average value for 4 samples
        tempAvg = (double) ((ui32Temp[0] + ui32Temp[1] + ui32Temp[2] + ui32Temp[3])/4);
        // Convert ADC value to Temperature
        finalResult = round((double)((1475 * 4096 - (75 * 33 * tempAvg)) / 40960));

        /* Transmit to UART */
        // Convert the unsigned integer ui32Temp value to a string tempBuffer.
        sprintf(tempBuffer, "Current Temp: %u\r\n", (uint32_t) finalResult);
        // Transmit
        UARTStringPut(UART0_BASE, tempBuffer, strlen(tempBuffer));

        /* Delay 1s */
        SysCtlDelay(SysCtlClockGet() / 3);

    }

}
