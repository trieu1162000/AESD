/*
 * queue_cards_api.c
 *
 *  Created on: Nov 26, 2023
 *      Author: trieu
 */

#include "../inc/queue_cards_api.h"

void initCard(card *card)
{
    memset(&card->name, '\0', sizeof(card->name));
    memset(&card->id, 0, sizeof(card->id));
    memset(&card->uuid, 0, sizeof(card->uuid));

}

void initCardQueue(cardQueue *queue) {
    int i = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->numCards = 0;

    for (; i < MAX_CARDS; i++) {
        // Set each element of the authorizedCards array to zero
        memset(&queue->authorizedCards[i].name, '\0', sizeof(queue->authorizedCards[i].name));
        memset(&queue->authorizedCards[i].id, 0, sizeof(queue->authorizedCards[i].id));
        memset(&queue->authorizedCards[i].uuid, 0, sizeof(queue->authorizedCards[i].uuid));

    }
}

// Enqueue a card into the queue
bool enqueueCard(cardQueue *queue, const char *name, uint32_t id, const uint32_t *uuid) {
    if (queue->numCards < MAX_CARDS) {
        queue->rear = (queue->rear + 1) % MAX_CARDS;
        card *newCard = &queue->authorizedCards[queue->rear];
        strncpy(newCard->name, name, sizeof(newCard->name) - 1);
        newCard->name[sizeof(newCard->name) - 1] = '\0';  // Ensure null-terminated string
        newCard->id = id;
        memcpy(newCard->uuid, uuid, sizeof(newCard->uuid));
        queue->numCards++;
        return true;  // Enqueue successful
    }
    else
        return false;  // Queue full
}

// Dequeue a card from the queue
bool dequeueCard(cardQueue *queue, card *dequeuedCard) {
    if (queue->numCards > 0) {
        *dequeuedCard = queue->authorizedCards[queue->front];
        queue->front = (queue->front + 1) % MAX_CARDS;
        queue->numCards--;
        return true;  // Dequeue successful
    }
    else
        return false;  // Queue empty
}

void printAllCards(const cardQueue *queue) {
    int i, j;
    if (queue->numCards == 0) {
        DBG("No cards in the queue.\n");
        return;
    }

    DBG("Printing all cards:\n");
    for (i = 0; i < queue->numCards; i++) {
        DBG("Card %d:\n", i + 1);
        DBG("Name: %s\n", queue->authorizedCards[i].name);
        DBG("ID: %d\n", queue->authorizedCards[i].id);
        DBG("UUID: ");
        for (j = 0; j < sizeof(queue->authorizedCards[i].uuid)/sizeof(uint32_t); j++) {
            UARTprintf("%02X ", queue->authorizedCards[i].uuid[j]);
        }
        DBG("\n\n");
    }
}

void deserializeCardQueue(const uint32_t* rawData, cardQueue *queue) {
    int i, j;
    // Swap bytes for each field
    for (i = 0; i < sizeof(cardQueue) / sizeof(uint32_t); i++) {
        uint32_t temp = rawData[i];
        uint8_t* bytes = (uint8_t*)&temp;
        for (j = 0; j < sizeof(uint32_t) / 2; j++) {
            uint8_t tmp = bytes[j];
            bytes[j] = bytes[sizeof(uint32_t) - j - 1];
            bytes[sizeof(uint32_t) - j - 1] = tmp;
        }
        memcpy(((uint8_t*)queue) + i * sizeof(uint32_t), &temp, sizeof(uint32_t));
    }
}
