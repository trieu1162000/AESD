/*
 * lcd_i2c_api.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#include "config_peripherals_api.h"

#define FRAME_LENGTH 5

extern bool ISRReceiveFlag;
extern uint8_t receiveFrame[FRAME_LENGTH];

extern void UARTStringPut(uint32_t, const char*);
