/*
 * ledRedStateMachine.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Quoc Bao
 */
#include <ledGreenStateMachine.h>


typedef     enum {//TODO}  ledGState_t;
uint32_t    ledGTimer = 0;

static ledGState_t State = S_LEDOFF;

#ifdef  DEBUG
  static const  char *stateName[6]={
                            //TODO
                             };

#endif
void ledGreenStateMachineUpdate(void)
{
  //TODO
    }
}
