/*
 * rSystem_FSM_api.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_RSYSTEM_FSM_API_H_
#define MY_LIBS_INC_RSYSTEM_FSM_API_H_


#include "actions_api.h"
#include "events.h"

typedef enum {
    S_REMOTE_SYSTEM_STOPPED = 0,
    S_REMOTE_SYSTEM_PARSING,
    S_REMOTE_SYSTEM_SYNCHRONIZING,
    S_REMOTE_SYSTEM_CONFIGURATING,
    S_REMOTE_SYSTEM_WRITING,
    S_REMOTE_SYSTEM_UPLOADING,
} rSystemState_t;

extern void rSystemStateMachineUpdate();
extern void rSystemEventUpdate();

#endif /* MY_LIBS_INC_RSYSTEM_FSM_API_H_ */
