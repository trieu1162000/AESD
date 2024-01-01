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
unsigned char funnctionalCode = 0; 

uint32_t authorizedCardUUIDs[MAX_CARDS][CARD_LENGTH] = {0};
card verifiedCard;
card addedCard;
char receivedFrame[MAX_FRAME_SIZE] = {0};

static uint8_t passWd[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

int8_t bVerifyAction(void)
{
    // Read the UID of card
    int i;
    getAuthorizedCardsUUID(&cardQueueForEEPROM, authorizedCardUUIDs);
    DBG("Verify ID: \n\r");
    dumpHex((unsigned char *)cardID, CARD_LENGTH);
    for (i = 0; i < MAX_CARDS; ++i) {
        if (memcmp(cardID, authorizedCardUUIDs[i], CARD_LENGTH) == 0) {
            verifiedCard = getCardFromUUID(&cardQueueForEEPROM, (uint32_t *) cardID);
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
    // Get the frame
    parseFirstFrameInRawData((char *) rawReceivedFrame, receivedFrame);
    // Parsing the receive frame
    parseDataInFrame(receivedFrame, &cardNeedToDo);
}

void bSyncAction(cardQueue *queue)
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
    // Write for existing card
    writeName((uint8_t *) addedCard.name);
    writeID(addedCard.id);
    // Sync to the database in Tiva C

}

bool bRemoveAction(uint32_t id)
{
    return removeCard(&cardQueueForEEPROM, id);
}

bool bUpdateAction(uint32_t id, const char *name, uint32_t *uuid)
{
    return updateCardBaseOnUUID(&cardQueueForEEPROM, uuid, name, id);
}

void bACKRequest(void)
{
    // Frame: 0xFFAA - 'O' - 0xAAFF
    // Start of Frame
    UARTCharPut(UART1_BASE, 0xFF);
    UARTCharPut(UART1_BASE, 0xAA);

    // Identifier 'O' for OK to send back to the GUI
    UARTCharPut(UART1_BASE, 'O');

    // End of Frame
    UARTCharPut(UART1_BASE, 0xAA);
    UARTCharPut(UART1_BASE, 0xFF);
}

void bACKAdded(void)
{
    int i = 0;
    // After passinng, the data in the card will be sent to the GUI
    // Frame: 0xFFAA - 'A' - data (UUID) - 0xAAFF
    // Start of Frame
    UARTCharPut(UART1_BASE, 0xFF);
    UARTCharPut(UART1_BASE, 0xAA);

    // Identifier 'A' for indicating the data is from the "card" structure
    UARTCharPut(UART1_BASE, 'A');

    // Send UUID
    for (i = 0; i < sizeof(syncCard->uuid) / sizeof(uint32_t); i++) {
        UARTCharPut(UART1_BASE, (uint8_t) syncCard->uuid[i]);
    }

    // End of Frame
    UARTCharPut(UART1_BASE, 0xAA);
    UARTCharPut(UART1_BASE, 0xFF);
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

// Function to parse the first frame in raw data
void parseFirstFrameInRawData(char *rawData, char frame[MAX_FRAME_SIZE]) {
    
    memset(frame, 0, MAX_FRAME_SIZE);

    // Search for the start marker (0xFFAA) in the raw data
    const char* startMarker = strstr(rawData, "\xFF\xAA");
    if (startMarker != NULL) {
        // Search for the end marker (0xAAFF) in the raw data
        const char* endMarker = strstr(startMarker, "\xAA\xFF");
        if (endMarker != NULL) {
            // Calculate the length of the frame
            size_t frameLength = endMarker - startMarker + 4; // Include the markers

            // Check if the frame length is within the maximum allowed size
            if (frameLength <= MAX_FRAME_SIZE) {
                // Copy the frame to the frame array
                strncpy(frame, startMarker, frameLength);
                frame[frameLength] = '\0';  // Ensure null-terminated string
            } else {
                // Handle the case where the frame size exceeds the maximum allowed size
                // You may want to handle this differently based on your application
                frame[0] = '\0';  // '\0' is often used to represent an invalid or null character
            }
        } else {
            // Handle the case where the end marker is not found
            // You may want to handle this differently based on your application
            frame[0] = '\0';  // '\0' is often used to represent an invalid or null character
        }
    } else {
        // Handle the case where the start marker is not found
        // You may want to handle this differently based on your application
        frame[0] = '\0';  // '\0' is often used to represent an invalid or null character
    }
}

// Function to modify the data based on the functional code in the frame
void parseDataInFrame(char *frame, card* dataCard)
{
    char functionalCode = frame[2];

    // Extract data based on the functional code
    switch (functionalCode) {
        case 'A':
            currentEvent = E_ADD;
            if (strlen(frame) >= 42) {
                strncpy(dataCard->name, frame + 6, 32);
                dataCard->name[31] = '\0';  // Ensure null-terminated string
                dataCard->id = *(uint32_t*)(frame + 38);
            }
            break;

        case 'D':
            currentEvent = E_REMOVE;
            if (strlen(frame) >= 10) {
                dataCard->id = *(uint32_t*)(frame + 6);
            }
            break;

        case 'V':
            currentEvent = E_ACKED;
            break;

        case 'S':
            currentEvent = E_SYNC;
            break;

        case 'F':
            currentEvent = E_FINISHED;
            break;

        case 'R':
            currentEvent = E_REQUEST;
            break;

        case 'U':
            currentEvent = E_UPDATE;
            if (strlen(frame) >= 46) {
                strncpy(dataCard->name, frame + 6, 32);
                dataCard->name[31] = '\0';  // Ensure null-terminated string
                dataCard->id = *(uint32_t*)(frame + 38);
                memcpy(dataCard->uuid, frame + 42, sizeof(dataCard->uuid));
            }
            break;
        default:
            // Handle invalid functional code
            break;
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
