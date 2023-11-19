/*
 * bSystem_FSM_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */


#include "../inc/bSystem_FSM_api.h"

#define CARD_LENGTH 5
#define MAX_LEN 16
#define AUTHORIZED_CARD_COUNT 6

#define VERIFY_PASS     1
#define VERIFY_FAIL     -1
#define YET_VERIFY      0

typedef enum {
    S_BASE_SYSTEM_STOPPED = 0,
    S_BASE_SYSTEM_VERIFYING,
    S_BASE_SYSTEM_WARNING,
    S_BASE_SYSTEM_UNLOCKING,
    S_BASE_SYSTEM_UPLOADING,
    S_BASE_SYSTEM_UPLOADED,
} bSystemState_t;

typedef enum {
    E_DETECTED = 0,         // detectedFlag is raised
    E_AUTHORIZED,           // verifyFllag is changed
    E_DENIED,               // verifyFllag is changed
    E_UNLOCKED,             // unlockedTimerFlag is raised
    E_FINISHED,             // warningTimer is raised/ detectedFlag is not raised/
    E_ACKED,                // SW2 is pressed
} bSystemEvents_t;

static bSystemState_t currentState = S_BASE_SYSTEM_STOPPED;
static bSystemEvents_t currentEvent = E_FINISHED;

static int8_t detectedFlag = MI_NOTAGERR;
unsigned char str[MAX_LEN];
unsigned char cardID[CARD_LENGTH];
static int8_t verifyFlag = YET_VERIFY;

const char authorizedCardIDs[AUTHORIZED_CARD_COUNT][CARD_LENGTH] = {
                           {0x25, 0xbd, 0x9d, 0x2d, 0x28},
                           {0x88, 0x1d, 0x6a, 0x32, 0xcd},
                           {0x88, 0x1d, 0x6d, 0x32, 0xca},
                           {0x88, 0x1d, 0x6b, 0x32, 0xcc},
                           {0x25, 0xbd, 0x9d, 0x2d, 0x28},
                           {0x25, 0xbd, 0x9d, 0x2d, 0x28}
};

void dumpHex(unsigned char* buffer, int len){
    int i;
//    char tempBuffer[10] = {'\0'};

    UARTprintf(" ");
    for(i=0; i < len; i++) {
        UARTprintf("0x%x, ", buffer[i]);
//        UARTprintf(tempBuffer);
    }
    UARTprintf("  FIM! \r\n"); //End

}

int8_t verifyAction(void)
{
    // Read the UID of card
    int i;
    memcpy(cardID, str, 5);

    for (i = 0; i < AUTHORIZED_CARD_COUNT; ++i) {
        if (memcmp(cardID, authorizedCardIDs[i], CARD_LENGTH) == 0) {
            return VERIFY_PASS;  // Card is authorized
        }
    }
    return VERIFY_FAIL;  // Card is not authorized

}

int8_t pollingAction(void)
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

void passAction()
{
    // Here, We will unlock the door immediately

    // Simultaneously, enable the unlocked timer and wait for it to expire
    // At this time, it will point to the Timer Int Handler named timerUIntHandler
    TimerEnable(TIMER0_BASE, TIMER_A);

    // Then, we may put some data, means that raise an TX ISR

    // We may also turn on LED Green, Buzzer but shorter seconds

    // Subsequently, We may display something to the LCD
}

void failAction()
{
    // Here, We will lock the door immediately

    // Then, we may put turn on LED Red, Buzzer for longer seconds

    // Subsequently, We may want to warning something to the LCD}

}
void stopAction()
{
    // Here, We will lock the door after seconds

    // And, We may display something to the LCD
}

void bSystemStateMachineUpdate(void)
{

        switch (currentState) {

            case S_BASE_SYSTEM_STOPPED:
                switch (currentEvent) {
                    case E_FINISHED:
                        // Polling to detect card
                        detectedFlag =  pollingAction();
                        break;
                    case E_DETECTED:
                        /*
                         * Verify the detected card
                         */
                        verifyFlag = verifyAction();
                        currentState = S_BASE_SYSTEM_VERIFYING;
                        DBG("State = VERIFYING\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_VERIFYING:
                switch (currentEvent) {
                    case E_AUTHORIZED:
                        /*
                         * The card is authorized
                         */
                        // TBD: Displaying, Unlocking the door
                        passAction();
                        currentState = S_BASE_SYSTEM_UNLOCKING;
                        break;
                    case E_DENIED:
                        /*
                         * The card is denied
                         */
                        // TBD: Warning, Locking the door
                        failAction();

                        currentState = S_BASE_SYSTEM_WARNING;
                        DBG("State = WARNING\n");

                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_UNLOCKING:
                switch (currentEvent) {
                    case E_ACKED: // This is a unlock timer event
                        // TBD: Displaying, Locking the door
                        stopAction();
                        currentState = S_BASE_SYSTEM_UPLOADING;
                        DBG("State = UPLOADING\n");

                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_UPLOADING:
                switch (currentEvent) {
                    case E_ACKED:
                        currentState = S_BASE_SYSTEM_STOPPED;
                        DBG("State = STOPPED\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_WARNING:
                switch (currentEvent) {
                    case E_DETECTED:
                        stopAction();
                        verifyAction();
                        currentState = S_BASE_SYSTEM_VERIFYING;
                        break;
                    case E_FINISHED: // This is a warning timer event
                        stopAction();
                        currentState = S_BASE_SYSTEM_STOPPED;
                        break;
                    default:
                        break;
                }
                break;

        }

}


void bSystemEventUpdate()
{
    if(verifyFlag == VERIFY_PASS)
    {
        currentEvent = E_AUTHORIZED;
        verifyFlag = YET_VERIFY;
    }
    else if(verifyFlag == VERIFY_FAIL)
    {
        currentEvent = E_DENIED;
        verifyFlag = YET_VERIFY;
    }
//    else if(verifyFlag == YET_VERIFY)
//        {
//            if(currentState == S_BASE_SYSTEM_VERIFYING)
//                currentEvent = E_FINISHED
//        }
    if(detectedFlag == MI_OK)
    {
        currentEvent = E_DETECTED;
        detectedFlag = MI_NOTAGERR;
    }

    // Check warning timer and raise a flag
    if(warningTimerFlag)
    {
        currentEvent = E_FINISHED;
        warningTimerFlag = false;
    }

    // Check unlocked timer and raise a flag
    if(unlockedTimerFlag)
    {
        currentEvent = E_UNLOCKED;
        unlockedTimerFlag = false;
    }
}





