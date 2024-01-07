/*
 * states.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_STATES_H_
#define MY_LIBS_INC_STATES_H_

typedef enum {
    BARE_S_STOPPED = 0,
    BARE_S_VERIFYING,
    BARE_S_WARNING,
    BARE_S_UNLOCKING,
} bSystemState_t;

typedef enum {
    GUI_S_STOPPED = 0,
    GUI_S_ADDING,
    GUI_S_UPDATING,
    GUI_S_REMOVING,
    GUI_S_SYNCHRONIZING,
    GUI_S_MODIFYING,
} gSystemState_t;

#endif /* MY_LIBS_INC_STATES_H_ */
