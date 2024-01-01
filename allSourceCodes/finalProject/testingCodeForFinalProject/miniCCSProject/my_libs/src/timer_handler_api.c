/*
 * timer_handler_api.c
 *
 *  Created on: Nov 19, 2023
 *      Author: trieu
 */

#include "../inc/timer_handler_api.h"

void timerUIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Raise the event
    currentEvent = E_UNLOCKED;

}

void timerWIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // Raise the event
    currentEvent = E_FINISHED;

}

void timerAUIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    // Raise the event
    currentEvent = E_AU_TIMEOUT;
}

