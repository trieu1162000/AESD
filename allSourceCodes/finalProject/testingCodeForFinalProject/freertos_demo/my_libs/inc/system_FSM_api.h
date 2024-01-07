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

typedef struct{
    bSystemEvents_t event_;
    bSystemState_t state_;
} bFSM_t;

typedef struct gFSM_t{
    gSystemEvents_t event_;
    gSystemState_t state_;
} gFSM_t;

extern gFSM_t gFSM_;
extern bFSM_t bFSM_;

// This is used by bFSM
extern SemaphoreHandle_t bTimerEventSemaphore_;
extern SemaphoreHandle_t bAcceptEventSemaphore_;
extern SemaphoreHandle_t bDispatchEventSemaphore_;

// This is used by gFSM
extern SemaphoreHandle_t gTimerEventSemaphore_;
extern SemaphoreHandle_t gUARTEventSemaphore_;
extern SemaphoreHandle_t gAcceptEventSemaphore_;
extern SemaphoreHandle_t gDispatchEventSemaphore_;

// This is used by both
extern SemaphoreHandle_t switchGUIEventSemaphore_;
extern SemaphoreHandle_t switchBareEventSemaphore_;

#endif /* MY_LIBS_INC_SYSTEM_FSM_API_H_ */
