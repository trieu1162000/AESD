/*
 * bSystem_FSM_api.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_BSYSTEM_FSM_API_H_
#define MY_LIBS_INC_BSYSTEM_FSM_API_H_


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "../inc/bSystem_FSM_api.h"
#include "../inc/config_peripherals_api.h"
#include "../inc/rc522_api.h"
#include "../inc/timer_handler_api.h"

extern void bSystemStateMachineUpdate();
extern void bSystemEventUpdate();

#endif /* MY_LIBS_INC_BSYSTEM_FSM_API_H_ */
