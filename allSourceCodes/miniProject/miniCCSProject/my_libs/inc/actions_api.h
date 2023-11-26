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
#include "leds_buzzer_lock.h"
#include "rc522_api.h"
#include "uart_api.h"
#include "events.h"

#define CARD_LENGTH 5
#define MAX_LEN 16
#define AUTHORIZED_CARD_COUNT 6

#define VERIFY_PASS     1
#define VERIFY_FAIL     -1
#define YET_VERIFY      0

extern unsigned char str[MAX_LEN];
extern unsigned char cardID[CARD_LENGTH];

// This var is used for both
extern int8_t detectedFlag;

static void dumpHex(unsigned char* buffer, int len);
static void upLoading(void);
static void normalDisplay(void);
static void warningDisplay(void);
static void passDisplay(void);
static char parseFrame(const char* frame);

// Actions for base system
extern int8_t bVerifyAction(void);
extern int8_t bPollingAction(void); // This action will be used by both remote and base system FSMs
extern void bPassAction(void);
extern void bFailAction(void);
extern void bStopAction(void);
extern void bReceiveAction(void);
extern void bSyncAction(void);
extern void bWriteAction(void);

#endif /* MY_LIBS_INC_ACTIONS_API_H_ */
