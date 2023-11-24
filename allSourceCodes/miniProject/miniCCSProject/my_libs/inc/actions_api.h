/*
 * actions_api.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_ACTIONS_API_H_
#define MY_LIBS_INC_ACTIONS_API_H_


#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "actions_api.h"
#include "rc522_api.h"

#define CARD_LENGTH 5
#define MAX_LEN 16
#define AUTHORIZED_CARD_COUNT 6

#define VERIFY_PASS     1
#define VERIFY_FAIL     -1
#define YET_VERIFY      0

// This var is used for both
extern int8_t detectedFlag;
extern bool bACKedFlag;

// Actions for base system
extern int8_t bVerifyAction(void);
extern int8_t bPollingAction(void); // This action will be used by both remote and base system FSMs
extern void bPassAction(void);
extern void bFailAction(void);
extern void bStopAction(void);

// Actions for remote system
extern void rReceiveAction(void);
extern void rSyncAction(void);
extern void rWriteAction(void);
extern void rSendAction(void);

#endif /* MY_LIBS_INC_ACTIONS_API_H_ */
