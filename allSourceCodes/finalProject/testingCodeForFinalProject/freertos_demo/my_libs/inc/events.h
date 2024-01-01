/*
 * events.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */
#include "FreeRTOS.h"
#include <semphr.h>

#ifndef MY_LIBS_INC_EVENTS_API_H_
#define MY_LIBS_INC_EVENTS_API_H_

typedef enum {
    // Events which used for bFSM
    BARE_E_DETECTED = 0,          // the card is detected
    BARE_E_AUTHORIZED,            // card is authorized
    BARE_E_DENIED,                // card is denied
    BARE_E_UNLOCKED,              // unlocked Timer is raised
    BARE_E_WARNED,                // warned Timer is raised
    BARE_E_FINISHED,              // warningTimer is raised
    BARE_E_GUI_REQUEST,           // GUI is requesting
} bSystemEvents_t;

typedef enum {
    // Events which used for gFSM
    GUI_E_COMPLETED = 0,          // initial event or after each action is completed
    GUI_E_FINISHED,               // after save action, turn to finished
    GUI_E_ADD,                    // add event
    GUI_E_UPDATE,                 // update event
    GUI_E_DETECTED,               // card is detected
    GUI_E_SYNC,                   // sync event
    GUI_E_REMOVE,                 // remove event
    GUI_E_AU_TIMEOUT,             // no card is detected

} gSystemEvents_t;

#endif /* MY_LIBS_INC_EVENTS_H_ */
