/*
 * system_FSM_api.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_SYSTEM_FSM_API_H_
#define MY_LIBS_INC_SYSTEM_FSM_API_H_

#include "actions_api.h"
#include "events.h"
#include "states.h"
#include "timer_handler_api.h"
#include "uart_api.h"
#include "debug.h"

static void dumpHex(unsigned char* buffer, int len);

extern void systemStateMachineUpdate();
extern void systemEventUpdate();

#endif /* MY_LIBS_INC_SYSTEM_FSM_API_H_ */
