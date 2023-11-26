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
// TODO: Need to implement for EEPROM
const char authorizedCardIDs[AUTHORIZED_CARD_COUNT][CARD_LENGTH] = {
                        //    {0x25, 0xbd, 0x9d, 0x2d, 0x28},
                           {0x25, 0xbd, 0x9d, 0x2d, 0x28},
                           {0x88, 0x1d, 0x6a, 0x32, 0xcd},
                           {0x88, 0x1d, 0x6d, 0x32, 0xca},
                           {0x88, 0x1d, 0x6b, 0x32, 0xcc},
                           {0x25, 0x30, 0x9d, 0x2d, 0x28},
                           {0x25, 0x3d, 0x9d, 0x2d, 0x28}
};

void dumpHex(unsigned char* buffer, int len){

    int i;
    UARTprintf(" ");
    for(i=0; i < len; i++) {
        UARTprintf("0x%x, ", buffer[i]);
    }
    UARTprintf("  FIM! \r\n"); //End

}

int8_t bVerifyAction(void)
{
    // Read the UID of card
    int i;

    DBG("Verify ID: \n\r");
    dumpHex((unsigned char *)cardID, CARD_LENGTH);
    for (i = 0; i < AUTHORIZED_CARD_COUNT; ++i) {
        if (memcmp(cardID, authorizedCardIDs[i], CARD_LENGTH) == 0) {
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
    upLoading();

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

void bSyncAction(void)
{
    // TODO: TBD
    // Sync the database from Tiva C to the GUI

}

void bWriteAction(void)
{
    // TODO: TBD
    // Write for existing card

    // Sync to the database in Tiva C

}

void upLoading()
{
    // TODO: TBD
    // After passinng, the data in the card will be sent to the GUI
    
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
