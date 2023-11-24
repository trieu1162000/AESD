/*
 * bSystem_FSM_api.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_BSYSTEM_FSM_API_H_
#define MY_LIBS_INC_BSYSTEM_FSM_API_H_

#include "actions_api.h"
#include "events.h"
#include "timer_handler_api.h"
#include "debug.h"

typedef enum {
    S_BASE_SYSTEM_STOPPED = 0,
    S_BASE_SYSTEM_VERIFYING,
    S_BASE_SYSTEM_WARNING,
    S_BASE_SYSTEM_UNLOCKING,
    S_BASE_SYSTEM_UPLOADING,
    S_BASE_SYSTEM_UPLOADED,
} bSystemState_t;

static void dumpHex(unsigned char* buffer, int len);

extern void bSystemStateMachineUpdate();
extern void bSystemEventUpdate();

#endif /* MY_LIBS_INC_BSYSTEM_FSM_API_H_ */
