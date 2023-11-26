/*
 * queue_cards_api.h
 *
 *  Created on: Nov 26, 2023
 *      Author: trieu
 */

#ifndef MY_LIBS_INC_QUEUE_CARDS_API_H_
#define MY_LIBS_INC_QUEUE_CARDS_API_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"

#define MAX_CARDS 10

typedef struct {
    char name[32];
    uint32_t id;
    uint32_t uuid[5];
} card;

typedef struct {
    card authorizedCards[MAX_CARDS];
    uint8_t front;
    int8_t rear;
    uint8_t numCards;
} cardQueue;

extern void initCardQueue(cardQueue *queue);
extern bool enqueueCard(cardQueue *queue, const char *name, uint32_t id, const uint32_t *uuid);
extern bool dequeueCard(cardQueue *queue, card *dequeuedCard);
extern void printAllCards(const cardQueue *queue);
extern void deserializeCardQueue(const uint32_t* rawData, cardQueue *queue);
extern void initCard(card *card);

#endif /* MY_LIBS_INC_QUEUE_CARDS_API_H_ */
