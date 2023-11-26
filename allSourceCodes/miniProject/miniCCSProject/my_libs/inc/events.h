/*
 * events.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_EVENTS_API_H_
#define MY_LIBS_INC_EVENTS_API_H_

typedef enum {
    // Events which used for base system
    E_DETECTED = 0,         // the card is detected, detectedFlag is raised
    E_AUTHORIZED,           // verifyFllag is changed
    E_DENIED,               // verifyFllag is changed
    E_UNLOCKED,             // unlockedTimerFlag is raised
    E_FINISHED,             // warningTimer is raised/ detectedFlag is not raised/
    E_ISR_RECEIVE,          // ISR UART RX is raised, some data is received
    E_SYNC,                 // after parsing, sync event is raised
    E_CONFIG,               // after parsing, config event is raised
    E_ACKED,                // after parsing, ACK for an action is received from GUI 
} systemEvents_t;

extern systemEvents_t currentEvent;

#endif /* MY_LIBS_INC_EVENTS_H_ */
