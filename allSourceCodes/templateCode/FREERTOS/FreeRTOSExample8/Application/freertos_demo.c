//*****************************************************************************
//
// freertos_demo.c - Simple FreeRTOS example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "led_task.h"
#include "switch_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#define TARGET_IS_BLIZZARD_RB1
#include "driverlib/rom.h"
#include "drivers/led.h"
#include "drivers/switches.h"
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>FreeRTOS Example (freertos_demo)</h1>
//!
//! This application demonstrates the use of FreeRTOS on Launchpad.
//!
//! The application blinks the user-selected LED at a user-selected frequency.
//! To select the LED press the left button and to select the frequency press
//! the right button.  The UART outputs the application status at 115,200 baud,
//! 8-n-1 mode.
//!
//! This application utilizes FreeRTOS to perform the tasks in a concurrent
//! fashion.  The following tasks are created:
//!
//! - An LED task, which blinks the user-selected on-board LED at a
//!   user-selected rate (changed via the buttons).
//!
//! - A Switch task, which monitors the buttons pressed and passes the
//!   information to LED task.
//!
//! In addition to the tasks, this application also uses the following FreeRTOS
//! resources:
//!
//! - A Queue to enable information transfer between tasks.
//!
//! - A Semaphore to guard the resource, UART, from access by multiple tasks at
//!   the same time.
//!
//! - A non-blocking FreeRTOS Delay to put the tasks in blocked state when they
//!   have nothing to do.
//!
//! For additional details on FreeRTOS, refer to the FreeRTOS web page at:
//! http://www.freertos.org/
//
//*****************************************************************************


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
xSemaphoreHandle xBinarySemaphore;

#define     TASK0       0
#define     TASK1       1
#define     TASK2       2
#define     TASK3       3
#define     TASK4       4
#define     TASK5       5
/* The two task functions. */
static  void vButtonLeftTask( void *pvParameters );
static  void vButtonRightTask( void *pvParameters );
static  void vUartTask( void *pvParameters );
static  void vLedTask( void *pvParameters );

/* Declare a variable of type xQueueHandle.  This is used to store the queue
that is accessed by all three tasks. */
xQueueHandle xQueue;

/* Define the structure type that will be passed on the queue. */
typedef struct
{   //unsigned char Uart_val;
    sw_t buttonValue;
    unsigned int taskSource;
} Data_t;
const char b[10]="ONGREEN\r\n";
const char c[11]="OFFGREEN\r\n";
char Data_Uart[9];
uint16_t i =0;



void UARTIntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;


    while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
    {
        Data_Uart[i] = UARTCharGetNonBlocking(UART0_BASE);
        if (Data_Uart[i]=='O')
        {
            i=0;
        }
            UARTprintf("\n\rky tu %d la:",i);
            UARTCharPutNonBlocking(UART0_BASE, Data_Uart[i]);//echo character

            i++;
            if (i>8)
                i=0;
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
            SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); //turn off LED

    }
        xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
        portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
int main(void)
{

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ConfigureUART();
    switchInit();
    ledInit();
    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART0); //enable the UART interrupt
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
    vSemaphoreCreateBinary( xBinarySemaphore );
    xQueue = xQueueCreate( 2, sizeof( Data_t ) );

    xTaskCreate( vUartTask, "UART", 1000, NULL, 3, NULL );
    xTaskCreate( vButtonLeftTask, "SW 1", 1000, NULL, 1, NULL );
    xTaskCreate( vButtonRightTask, "SW 2", 1000, NULL, 1, NULL );
    xTaskCreate( vLedTask, "LED", 1000, NULL, 2, NULL );
    vTaskStartScheduler();
    for( ;; );
}

static  void vButtonLeftTask( void *pvParameters )
{
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    sw_t    preVal, currentVal;
    Data_t  data;
    //data.taskSource = TASK1;
    preVal = switchState(1);
    for( ;; )
    {
        currentVal = switchState(1);
        if (currentVal != preVal)
        {
                data.buttonValue = currentVal;
                preVal = currentVal;
                if( data.buttonValue == 0)
                data.taskSource = TASK0;
                if( data.buttonValue == 1)
                data.taskSource = TASK1;
              xStatus = xQueueSend( xQueue, &data, xTicksToWait );
                if( xStatus != pdPASS )
                {
                   // UARTprintf( "Task 1 could not send to the queue.\n" );
                }
        }
    }
}
static  void vButtonRightTask( void *pvParameters )
{
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    sw_t    preVal, currentVal;
    Data_t  data;

  //  data.taskSource = TASK2;
    preVal = switchState(2);

    for( ;; )
    {
        currentVal = switchState(2);
        if (currentVal != preVal)
        {
                data.buttonValue = currentVal;
                preVal = currentVal;
                if( data.buttonValue == 0)
                data.taskSource = TASK4;
                if( data.buttonValue == 1)
                data.taskSource = TASK5;
              xStatus = xQueueSend( xQueue, &data, xTicksToWait );
                if( xStatus != pdPASS )
                {
                    //UARTprintf( "Task 2 could not send to the queue.\n" );
                }
        }
    }
}
static  void vUartTask( void *pvParameters )
{
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    Data_t  data;

    for( ;; )
    {
        xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
        int count_1=0;
        int count_2=0;
        int a;
        for(a=0; a<9;a++){

            if (Data_Uart[a]==b[a])
                count_1++;
            if (Data_Uart[a]==c[a])
                count_2++;
        }


        if (count_1 ==8)
            data.taskSource = TASK2;

        if (count_2 ==9)
            data.taskSource = TASK3;
            xStatus = xQueueSend( xQueue, &data, xTicksToWait );

    }
}
static void vLedTask( void *pvParameters )
{
/* Declare the structure that will hold the values received from the queue. */
    Data_t   data;
    portBASE_TYPE xStatus;
   // const portTickType xTicksToWait = 5000 / portTICK_RATE_MS;

    /* This task is also defined within an infinite loop. */


    for( ;; )
    {
     // xStatus = xQueueReceive( xQueue, &data, xTicksToWait );
        xStatus = xQueueReceive( xQueue, &data, portMAX_DELAY );
        if( xStatus == pdPASS )
        {
            /* Data was successfully received from the queue, print out the received
            value and the source of the value. */
            if( data.taskSource == TASK0 )
            {
                ledControl(LEDRED, ON);
            }
            if( data.taskSource == TASK1 )
            {
                ledControl(LEDRED, OFF);
            }
            if( data.taskSource == TASK2 )
            {
                ledControl(LEDGREEN, ON);
            }
            if( data.taskSource == TASK3 )
            {
                ledControl(LEDGREEN, OFF);
            }
            if( data.taskSource == TASK4 )
            {
                ledControl(LEDBLUE, ON);
            }
            if( data.taskSource == TASK5 )
            {
                ledControl(LEDBLUE, OFF);
            }
        }
        else
        {
            UARTprintf( "Could not receive from the queue in 5  sec\n" );
        }
    }
}
