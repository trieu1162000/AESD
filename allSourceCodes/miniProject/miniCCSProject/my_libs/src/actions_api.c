/*
 * actions_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */

#include "../inc/actions_api.h"

int8_t detectedFlag = MI_NOTAGERR;
unsigned char str[MAX_LEN] = {0};
unsigned char cardUUID[CARD_LENGTH] = {0};
unsigned char funnctionalCode = 0; 
uint32_t authorizedCardUUIDs[MAX_CARDS][CARD_LENGTH] = {0};
card verifiedCard;
char receivedFrame[MAX_FRAME_SIZE] = {0};
size_t receivedFrameLength = 0;

static uint8_t passWd[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

int8_t bVerifyAction(void)
{
    // Read the UID of card
    int i;
    getAuthorizedCardsUUID(&cardQueueForEEPROM, authorizedCardUUIDs);
    DBG("Verify ID: \n\r");
    dumpHex((unsigned char *)cardUUID, CARD_LENGTH);
    for (i = 0; i < MAX_CARDS; ++i) {
        if (memcmp(cardUUID, authorizedCardUUIDs[i], CARD_LENGTH) == 0) {
            verifiedCard = getCardFromUUID(&cardQueueForEEPROM, (uint32_t *) cardUUID);
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
    memcpy(cardUUID, &str[2], 5);

    if(status == MI_OK){
        DBG("ID: \n\r");
        dumpHex((unsigned char *)cardUUID, CARD_LENGTH);
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
    int i;
    bool result;

    DBG("Received Frame: ");
    for(i = 0; i<10; i++)
        UARTprintf("%x ", rawReceivedFrame[i]);
    DBG("\n");

    // Get the data into the frame from the raw data
    result = parseFirstFrameInRawData((char *) rawReceivedFrame, receivedFrame);
    if(result)
    {
        // Parsing the data in receive frame into the card
        parseDataInFrame(receivedFrame, &cardNeedToDo);
    }
    DBG("Failed to parse\n");

    // Need to reset the frame before receiving again
    memset(rawReceivedFrame, 0, MAX_FRAME_LENGTH);

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
    int i;

    for (i = 0; i < CARD_LENGTH; i++)
        cardNeedToDo.uuid[i] = (uint32_t) cardUUID[i];
    // Write for existing card
    writeName((uint8_t *) cardNeedToDo.name);
    writeID(cardNeedToDo.id);
    // Sync to the database in Tiva C
    enqueueCard(&cardQueueForEEPROM, cardNeedToDo.name, cardNeedToDo.id, cardNeedToDo.uuid);

    // Send Back the UUID to the GUI
    bACKAdded();

}

bool bRemoveAction(uint32_t id)
{
    return removeCard(&cardQueueForEEPROM, id);
}

bool bUpdateAction(card *updateCard)
{
    return updateCardBaseOnUUID(&cardQueueForEEPROM, updateCard->uuid, updateCard->name, updateCard->id);
}

// Function to send back the ACK when GUI Requests
void bACKRequestAction(void)
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
    // After adding, the UUID in the card will be sent back to the GUI
    // Frame: 0xFFAA - 'A' - data (UUID) - 0xAAFF
    // Start of Frame
    UARTCharPut(UART1_BASE, 0xFF);
    UARTCharPut(UART1_BASE, 0xAA);

    // Identifier 'A' for indicating the data is from the "card" structure
    UARTCharPut(UART1_BASE, 'A');

    // Send back UUID to the GUI after adding Name and ID in Tiva C
    for (i = 0; i < sizeof(cardNeedToDo.uuid) / sizeof(uint32_t); i++) {
        UARTCharPut(UART1_BASE, (uint8_t) cardNeedToDo.uuid[i]);
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
// Function to send the data of the verified card
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
bool parseFirstFrameInRawData(char *rawData, char frame[MAX_FRAME_SIZE]) {
    
    int i;
    // Reset the core frame before get the data into it
    memset(frame, 0, MAX_FRAME_SIZE);

    // Search for the start marker (0xFFAA) in the raw data
    const char* startMarker = strstr(rawData, "\xFF\xAA");
    char testFrame[10] = {0};
    for (i = 0; i< 10; i++)
        testFrame[i] = *(startMarker + i);
    if (startMarker != NULL) {
        // Search for the end marker (0xAAFF) in the raw data
        const char* endMarker = strstr(startMarker + 2, "\xDE\xCC");
        if (endMarker != NULL) {
            // Calculate the length of the frame
            size_t frameLength = endMarker - startMarker + 4; // Include the markers

            // Check if the frame length is within the maximum allowed size
            if (frameLength <= MAX_FRAME_SIZE) {
                // Copy the frame to the frame array
                strncpy(frame, startMarker, frameLength);
                frame[frameLength] = '\0';  // Ensure null-terminated string
                return true;
            } else {
                // Handle the case where the frame size exceeds the maximum allowed size
                // You may want to handle this differently based on your application
                frame[0] = '\0';  // '\0' is often used to represent an invalid or null character
            }
        } else {
            // Handle the case where the end marker is not found
            return false;
            // You may want to handle this differently based on your application
//            frame[0] = '\0';  // '\0' is often used to represent an invalid or null character
        }
    } else {
        // Handle the case where the start marker is not found
        return false;
        // You may want to handle this differently based on your application
//        frame[0] = '\0';  // '\0' is often used to represent an invalid or null character
    }
}

void parse_frame(const uint8_t *data_stream, size_t stream_length) {
    size_t i;
    size_t frame_start = 0;
    size_t frame_end = 0;

    // Find the start marker
    for (i = 0; i < stream_length - 1; ++i) {
        if ((data_stream[i] == 0xFF) && (data_stream[i + 1] == 0xAA)) {
            frame_start = i;
            break;
        }
    }

    // Find the end marker
    for (i = frame_start; i < stream_length - 1; ++i) {
        if ((data_stream[i] == 0xAA) && (data_stream[i + 1] == 0xFF)) {
            frame_end = i + 2;
            break;
        }
    }

    // Check if both markers were found
    if (frame_start < frame_end) {
        // Extract the frame and store it in the global variable
        size_t frame_length = frame_end - frame_start;
        memcpy(receivedFrame, &data_stream[frame_start], frame_length);
        receivedFrameL = frame_length;

        // If there is more data after the frame, you can process it here
    } else {
        DBG("Incomplete frame received.\n");
    }
}

// Function to modify the data based on the functional code in the frame
void parseDataInFrame(char *frame, card *dataCard)
{
    char functionalCode = frame[2];

    // Reset the card first, then parse it later
    initCard(dataCard);

    // Extract data based on the functional code
    switch (functionalCode) {
        case 'A':
            currentEvent = E_ADD;
            DBG("Add code\n");
            if (strlen(frame) >= 42) {
                strncpy(dataCard->name, frame + 6, 32);
                dataCard->name[31] = '\0';  // Ensure null-terminated string
                dataCard->id = *(uint32_t*)(frame + 38);
            }
            break;

        case 'D':
            currentEvent = E_REMOVE;
            DBG("Remove code\n");
            if (strlen(frame) >= 10) {
                dataCard->id = *(uint32_t*)(frame + 6);
            }
            break;

        case 'S':
            currentEvent = E_SYNC;
            DBG("Sync code\n");
            break;

        case 'F':
            currentEvent = E_GUI_FINISHED;
            DBG("GUI finished code\n");

            break;

        case 'R':
            currentEvent = E_REQUEST;
            DBG("Request code\n");
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
            currentEvent = E_GUI_FINISHED;
            DBG("Invalid functional code\n");
            break;
    }
}

void sync1Card(card *syncCard)
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

    status = rc522Auth(PICC_AUTHENT1A, WRITE_ID_BLOCK, passWd, (uint8_t *) &cardNeedToDo.uuid);
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

int8_t writeName(uint8_t *name)
{
    int8_t status;

    status = rc522Auth(PICC_AUTHENT1A, WRITE_NAME_BLOCK, passWd, (uint8_t *) &cardNeedToDo.uuid);
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
