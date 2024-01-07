/*
 * timer_handler_api.c
 *
 *  Created on: Nov 19, 2023
 *      Author: trieu
 */

#include "../inc/timer_handler_api.h"

bool warningTimerFlag = false;
bool unlockedTimerFlag = false;

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


