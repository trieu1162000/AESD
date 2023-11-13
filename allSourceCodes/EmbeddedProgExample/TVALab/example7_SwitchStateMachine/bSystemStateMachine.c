/*
 * bSystemStateMachine.c
 *
 *  Created on: Nov 14, 2023
 *      Author: trieu
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "bSystemStateMachine.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"

typedef enum {
    S_BASE_SYSTEM_STOPPED = 0,
    S_BASE_SYSTEM_VERIFYING,
    S_BASE_SYSTEM_WARNING,
    S_BASE_SYSTEM_UNLOCKING,
    S_BASE_SYSTEM_LOCKING,
} bSystemState_t;

typedef enum {
    E_DETECT = 0,           // SW1 is pressed and released
    E_AUTHORIZED,           // SW2 is pressed and released
    E_DENIED,               // SW1 is pressed and released more than 3s
    E_UNLOCKED,             // SW2 is pressed and released more than 3s
    E_FINISHED,             // SW2 is pressed and released more than 6s
} bSystemEvents_t;

static bSystemState_t currentState = S_BASE_SYSTEM_STOPPED;
static bSystemEvents_t currentEvent = E_FINISHED;

#ifdef  DEBUG
const  char *stateName[4]={
                            "S_LEDREDON",
                              "S_WAITLEDREDOFF",
                              "S_LEDREDOFF",
                              "S_WAITLEDREDON"
                             };

#endif
void bSystemStateMachineUpdate(void)
{

        switch (state) {

            case BASE_SYSTEM_STOPPED:
                switch (currentEvent) {
                    case E_DETECT: // SW1 is pressed
                        // Verify the detected card
                        // LED Green is on
                        verifyAction();
                        state = S_BASE_SYSTEM_VERIFYING;
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_VERIFYING:
                switch (currentEvent) {
                    case E_AUTHORIZED:
                        // Unlocking
                        // LED Blue is on
                        passAction();
                        state = S_BASE_SYSTEM_UNLOCKING;
                        break;
                    case E_DENIED:
                        // Warning
                        // LED Red is on
                        failAction();
                        state = S_BASE_SYSTEM_WARNING;
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_UNLOCKING:
                switch (currentEvent) {
                    case E_UNLOCKED:
                        // LED Blue is off
                        lockAction();
                        state = S_BASE_SYSTEM_LOCKING;
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_LOCKING:
                switch (currentEvent) {
                    case E_DETECT: // SW1 is pressed
                        // Verify the detected card
                        // LED Green is on
                        verifyAction();
                        state = S_BASE_SYSTEM_VERIFYING;
                        break;
                    case E_FINISHED:
                        // Turn off all LEDs
                        stopAction();
                        state = S_BASE_SYSTEM_STOPPED;
                        break;
                }
                break;

            case S_BASE_SYSTEM_WARNING:
                switch (currentEvent) {
                    case E_DETECT: // SW1 is pressed
                        // Verify the detected card
                        // LED Green is on
                        verifyAction();
                        state = S_BASE_SYSTEM_VERIFYING;
                        break;
                    case E_FINISHED:
                        // Turn off all LEDs
                        stopAction();
                        state = S_BASE_SYSTEM_STOPPED;
                        break;
                }
                break;

        }

}



