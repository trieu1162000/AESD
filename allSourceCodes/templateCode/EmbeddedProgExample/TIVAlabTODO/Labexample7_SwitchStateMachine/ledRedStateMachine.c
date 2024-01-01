/*
 * ledRedStateMachine.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "ledRedStateMachine.h"
#include "driverlib/gpio.h"
#include "switches.h"
#include "led.h"
#include "uartstdio.h"
#include "debug.h"

typedef     enum {S_LEDON=0,S_WAITLEDOFF, S_LEDOFF, S_WAITLEDON}  ledRState_t;

static ledRState_t State = S_LEDOFF;

#ifdef  DEBUG
  const  char *stateName[4]={
                            "S_LEDREDON",
                              "S_WAITLEDREDOFF",
                              "S_LEDREDOFF",
                              "S_WAITLEDREDON"
                             };

#endif
void ledRedStateMachineUpdate(void)
{
    //TODO
//    }
}
