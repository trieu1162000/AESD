/*
 * actions_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */

#include "../inc/actions_api.h"

int8_t detectedFlag = MI_NOTAGERR;
unsigned char str[MAX_LEN];
unsigned char cardID[CARD_LENGTH];

char authorizedCardUUIDs[AUTHORIZED_CARD_COUNT][CARD_LENGTH] = getAuthorizedCardsUUID();
card verifiedCard;
card addedCard;

static uint8_t passWd[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

int8_t bVerifyAction(void)
{
    // Read the UID of card
    int i;

    DBG("Verify ID: \n\r");
    dumpHex((unsigned char *)cardID, CARD_LENGTH);
    for (i = 0; i < AUTHORIZED_CARD_COUNT; ++i) {
        if (memcmp(cardID, authorizedCardUUIDs[i], CARD_LENGTH) == 0) {
            verifiedCard = getCardFromUUID((uint32_t *) cardID);
            return VERIFY_PASS;  // Card is authorized
        }
    }
    return VERIFY_FAIL;  // Card is not authorized

}

int8_t bPollingAction(void)
{
    int8_t status;
    status = rc522Request(PICC_REQIDL, str);
    if(status == MI_OK){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, HIGH_PIN);
        DBG("Card Detected! \r\n"); //Card Detected
    }

    status = rc522Anticoll(&str[2]);
    memcpy(cardID, &str[2], 5);

    if(status == MI_OK){
        DBG("ID: \n\r");
        dumpHex((unsigned char *)cardID, CARD_LENGTH);
        SysCtlDelay(SysCtlClockGet()/3); //Delay
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LOW_PIN);
    }
    return status;

}

void bPassAction(void)
{
    // Here, We will unlock the door immediately

    // Simultaneously, enable the unlocked timer 0 and wait for it to expire
    // At this time, it will point to the Timer Int Handler named timerUIntHandler
    // Disable the timer before enabling it again to reset the count
    TimerDisable(TIMER0_BASE, TIMER_A);
    TimerEnable(TIMER0_BASE, TIMER_A);

    // Then, we may put some data, means that raise an TX ISR
    verifiedSending(&verifiedCard);

    // We may also turn on LED Green, Buzzer but shorter seconds
    ledControl(LEDGREEN, ON);
    buzzerControl(ON);

    // Subsequently, We may display something to the LCD
    passDisplay();

}

void bFailAction(void)
{
    // Here, We will lock the door immediately
    lockControl(ON); // ON->Lock

    // Simultaneously, enable the unlocked timer 1 and wait for it to expire
    // At this time, it will point to the Timer Int Handler named timerUIntHandler
    // Disable the timer before enabling it again to reset the count
    TimerDisable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_A);

    // Then, we may put turn on LED Red, Buzzer for longer seconds
    ledControl(LEDRED, ON);
    buzzerControl(ON);

    // Subsequently, We may want to warning something to the LCD}
    warningDisplay();
}

void bStopAction(void)
{
    // Here, We will lock the door immediately
    lockControl(OFF);

    // Turn off all leds
    ledControl(LEDGREEN, OFF);
    ledControl(LEDRED, OFF);

    // Turn off buzzer
    buzzerControl(OFF);

    // And, We may display something to the LCD
    normalDisplay();
}

void bReceiveAction(void)
{
    uint8_t parsedData = 0;

    // Parsing the receive frame
    parsedData = parseFrame((const char *) receiveFrame);

    // Check if the parsing was successful
    if (parsedData != '\0')
    {
        DBG("Parsed data: %c\n", parsedData);
        switch(parsedData)
        {
            case 'A':
                currentEvent =  E_ACKED;
                break;
            case 'C':
                currentEvent =  E_CONFIG;
                break;
            case 'S':
                currentEvent =  E_SYNC;
            case 'F':
                currentEvent =  E_FINISHED;
        }
    }
    else
        DBG("Fail to parse the data. Invalid frame format\n");

}

void bSyncAction(const cardQueue *queue)
{
    // Sync the database from Tiva C to the GUI
    int i;
    if (queue->numCards == 0) {
        DBG("No cards in the queue.\n");
        return;
    }

    for (i = 0; i < queue->numCards; i++) {
        sync1Card(&queue->authorizedCards[i]);
    }

}

// This action is used for adding new card
void bWriteAction(void)
{
    // TODO: TBD
    // Write for existing card
    writename(addedCard.name);
    writeID(addedCard.id);
    // Sync to the database in Tiva C

}

void bSaveAction(void)
{
    saveCardsToEEPROM(&cardQueueForEEPROM);
}

// Static functions
void dumpHex(unsigned char* buffer, int len){

    int i;
    UARTprintf(" ");
    for(i=0; i < len; i++) {
        UARTprintf("0x%x, ", buffer[i]);
    }
    UARTprintf("  FIM! \r\n"); //End

}
// Function to sending the data of the verified card
void verifiedSending(const card* myCard)
{
    int i;
    // After passinng, the data in the card will be sent to the GUI
    // Frame: 0xFFAA - 'V' - data (Name, ID) - 0xAAFF
    // Start of Frame
    UARTCharPut(UART1_BASE, 0xFF);
    UARTCharPut(UART1_BASE, 0xAA);

    // Identifier 'V' for indicating the data is from the "card" structure
    UARTCharPut(UART1_BASE, 'V');

    // Send ID
    uint8_t* idBytes = (uint8_t*)&myCard->id;
    for (i = 0; i < sizeof(myCard->id); i++) {
        UARTCharPut(UART1_BASE, idBytes[i]);
    }

    // Send Name
    for (i = 0; i < sizeof(myCard->name); i++) {
        UARTCharPut(UART1_BASE, myCard->name[i]);
    }

    // End of Frame
    UARTCharPut(UART1_BASE, 0xAA);
    UARTCharPut(UART1_BASE, 0xFF);

    // Clear the card
    initCard(&verifiedCard);
}

void normalDisplay()
{
    // TODO: TBD
    // Display normally
    // Line 2: ACCESS CONTROL SYSTEM
    // Line 3: Please verify your card!
}

void warningDisplay()
{
    // TODO: TBD
    // Display a warning
    // Line 2: ACCESS IS DENIED!
    // Line 3: Please contact the
    // Line 4: admin to help check.

}

void passDisplay()
{
    // TODO: TBD
    // Display a passing
    // Line 2: ID:
    // Line 3: Name:
}

// Function to parse the frame and retrieve the data
char parseFrame(const char* frame) {
    // Check if the header and end frame are present
    if (frame[0] == 0xFF && frame[1] == 0xAA && frame[4] == 0xAA && frame[3] == 0xFF) {
        // Extract and return the data from the frame
        return frame[2];
    } else {
        // Return an invalid value (you may want to handle this differently based on your application)
        return '\0';  // '\0' is often used to represent an invalid or null character
    }
}

void sync1Card(card* syncCard)
{
    int i = 0;
    // After passinng, the data in the card will be sent to the GUI
    // Frame: 0xFFAA - 'S' - data (Name, ID, UUID) - 0xAAFF
    // Start of Frame
    UARTCharPut(UART1_BASE, 0xFF);
    UARTCharPut(UART1_BASE, 0xAA);

    // Identifier 'V' for indicating the data is from the "card" structure
    UARTCharPut(UART1_BASE, 'S');

    // Send ID
    uint8_t* idBytes = (uint8_t*)&syncCard->id;
    for (i = 0; i < sizeof(syncCard->id); i++) {
        UARTCharPut(UART1_BASE, idBytes[i]);
    }

    // Send Name
    for (i = 0; i < sizeof(syncCard->name); i++) {
        UARTCharPut(UART1_BASE, syncCard->name[i]);
    }

    // Send UUID
        // Send Name
    for (i = 0; i < sizeof(syncCard->uuid) / sizeof(uint32_t); i++) {
        UARTCharPut(UART1_BASE, (uint8_t) syncCard->uuid[i]);
    }

    // End of Frame
    UARTCharPut(UART1_BASE, 0xAA);
    UARTCharPut(UART1_BASE, 0xFF);

}

int8_t writeID(uint8_t id)
{
    int8_t status;

    status = rc522Auth(PICC_AUTHENT1A, WRITE_ID_BLOCK, passWd, (uint8_t *) &addedCard.uuid);
    if(status!=MI_OK)
    {
        DBG("write authrioze err.\n");
        return status;
    }
    status = rc522WriteBlock(WRITE_ID_BLOCK, &id);
    if(status!=MI_OK)
        DBG("write data err.\n");
    else
        DBG("write data sucess.\n");
    return status;
}

int8_t writeName(uint8_t* name)
{
    int8_t status;

    status = rc522Auth(PICC_AUTHENT1A, WRITE_NAME_BLOCK, passWd, (uint8_t *) &addedCard.uuid);
    if(status!=MI_OK)
    {
        DBG("write authrioze err.\n");
        return status;
    }
    status = rc522WriteBlock(WRITE_NAME_BLOCK, &name[0]);
    if(status!=MI_OK)
        DBG("write data err.\n");
    else
        DBG("write data sucess.\n");
    return status;
}
