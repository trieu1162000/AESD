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
    E_SYNC,                 // after parsing, sync card event is raised
    E_ADD,                  // after parsing, add card event is raised
    E_UPDATE,               // after parsing, update card event is raised
    E_REMOVE,               // after parsing, remove card event is raised
    E_GUI_FINISHED,                // after parsing, ACK for finishing is received from GUI
    E_REQUEST,              // GUI send an initiate request to start exchange data with the system
} systemEvents_t;

extern systemEvents_t currentEvent;

#endif /* MY_LIBS_INC_EVENTS_H_ */
