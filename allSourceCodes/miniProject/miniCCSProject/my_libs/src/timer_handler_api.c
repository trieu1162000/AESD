/*
 * timer_handler_api.c
 *
 *  Created on: Nov 19, 2023
 *      Author: trieu
 */

#include "../inc/timer_handler_api.h"

bool warningTimerFlag = false;
bool unlockedTimerFlag = false;

void initTimer(void)
{
    TimerConfigure(TIMER1_BASE, TIMER_CFG_ONE_SHOT);
    TimerLoadSet(TIMER1_BASE, TIMER_A, 5*SysCtlClockGet()-1);
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 5*SysCtlClockGet()-1);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
}

void timerUIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Raise the flag
    unlockedTimerFlag = true;

}

void timerWIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // Raise the flag
    warningTimerFlag = true;

}


