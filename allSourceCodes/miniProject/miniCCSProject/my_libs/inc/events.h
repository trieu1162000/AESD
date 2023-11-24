/*
 * events.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_EVENTS_API_H_
#define MY_LIBS_INC_EVENTS_API_H_

typedef enum {
    E_B_DETECTED = 0,         // detectedFlag is raised
    E_B_AUTHORIZED,           // verifyFllag is changed
    E_B_DENIED,               // verifyFllag is changed
    E_B_UNLOCKED,             // unlockedTimerFlag is raised
    E_B_FINISHED,             // warningTimer is raised/ detectedFlag is not raised/
    E_B_ACKED,                // SW2 is pressed
} bSystemEvents_t;

typedef enum {
    E_R_ISR_RECEIVE = 0,         // detectedFlag is raised
    E_R_SYNC,           // verifyFllag is changed
    E_R_CONFIG,               // verifyFllag is changed
    E_R_DETECT,             // unlockedTimerFlag is raised
    E_R_FINISHED,             // warningTimer is raised/ detectedFlag is not raised/
    E_R_ISR_TRANSMIT,                // SW2 is pressed
    E_R_ACKED,                // SW2 is pressed
} rSystemEvents_t;

#endif /* MY_LIBS_INC_EVENTS_H_ */