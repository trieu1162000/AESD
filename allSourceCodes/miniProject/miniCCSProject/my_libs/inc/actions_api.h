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
#include "queue_cards_api.h"
#include "eeprom_api.h"

#define WRITE_NAME_BLOCK      1
#define WRITE_ID_BLOCK        2
#define MAX_LEN               16

#define VERIFY_PASS           1
#define VERIFY_FAIL           (-1)
#define YET_VERIFY            0

extern unsigned char str[MAX_LEN];
extern unsigned char cardID[CARD_LENGTH];

// This var is used for both
extern int8_t detectedFlag;
extern uint32_t authorizedCardUUIDs[MAX_CARDS][CARD_LENGTH];
extern card verifiedCard;

// These functions only be used in actions_api
static void dumpHex(unsigned char* buffer, int len);
static void verifiedSending(const card* myCard);
static void normalDisplay(void);
static void warningDisplay(void);
static void passDisplay(void);
static char parseFrame(const char* frame);
static void sync1Card(card* syncCard);
static int8_t writeID(uint8_t id);
static int8_t writeName(uint8_t* name);

// Actions for base system. These will be used
extern int8_t bVerifyAction(void);
extern int8_t bPollingAction(void);
extern void bPassAction(void);
extern void bFailAction(void);
extern void bStopAction(void);
extern void bReceiveAction(void);
extern void bSyncAction(cardQueue *queue);
extern void bWriteAction(void);
extern void bUpdateAction(void);
extern void bRemoveAction(void);

#endif /* MY_LIBS_INC_ACTIONS_API_H_ */
