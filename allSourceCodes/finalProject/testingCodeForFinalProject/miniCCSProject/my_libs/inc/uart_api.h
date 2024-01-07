/*
 * lcd_i2c_api.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#include "config_peripherals_api.h"

#define MAX_FRAME_LENGTH 60
#define FRAME_START1 0xAA
#define FRAME_START2 0xBB
#define FRAME_END1   0xCC
#define FRAME_END2   0xDD

extern uint8_t receivedFrameIndex;
extern volatile uint8_t isInFrame;
extern uint8_t ISRReceiveFlag;
extern uint8_t rawReceivedFrame[MAX_FRAME_LENGTH];
extern uint8_t mainFrame[MAX_FRAME_LENGTH];


extern void UARTStringPut(uint32_t, const char*);
