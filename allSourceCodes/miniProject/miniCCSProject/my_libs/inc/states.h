/*
 * states.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_STATES_H_
#define MY_LIBS_INC_STATES_H_

typedef enum {
    S_STOPPED,
    S_VERIFYING,
    S_WARNING,
    S_UNLOCKING,
    S_PARSING,
    S_SYNCHRONIZING,
    S_ADDING,
    S_REMOVING,
    S_UPDATING,
    S_WRITING,
    S_MANAGING,
} systemState_t;

extern systemState_t currentState;

#endif /* MY_LIBS_INC_STATES_H_ */
