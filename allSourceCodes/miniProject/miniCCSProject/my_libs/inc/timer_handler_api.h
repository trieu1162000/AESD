/*
 * timer_handler_api.h
 *
 *  Created on: Nov 19, 2023
 *      Author: trieu
 */

#ifndef MY_LIBS_INC_TIMER_HANDLER_API_H_
#define MY_LIBS_INC_TIMER_HANDLER_API_H_

#include "../inc/config_peripherals_api.h"

extern bool warningTimerFlag;
extern bool unlockedTimerFlag;

extern void initTimer(void);

#endif /* MY_LIBS_INC_TIMER_HANDLER_API_H_ */
