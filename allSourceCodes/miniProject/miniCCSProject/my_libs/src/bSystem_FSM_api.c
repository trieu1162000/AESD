/*
 * bSystem_FSM_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */

#include "../inc/bSystem_FSM_api.h"

static bSystemState_t currentState = S_BASE_SYSTEM_STOPPED;
static bSystemEvents_t currentEvent = E_B_FINISHED;

bool bACKedFlag = false;
int8_t detectedFlag = MI_NOTAGERR;
static int8_t verifyFlag = YET_VERIFY;
static unsigned char str[MAX_LEN];
static unsigned char cardID[CARD_LENGTH];

// TODO: Need to implement for EEPROM
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
    UARTprintf(" ");
    for(i=0; i < len; i++) {
        UARTprintf("0x%x, ", buffer[i]);
    }
    UARTprintf("  FIM! \r\n"); //End

}

void bSystemStateMachineUpdate(void)
{

        switch (currentState) {

            case S_BASE_SYSTEM_STOPPED:
                switch (currentEvent) {
                    case E_B_FINISHED:
                        // Polling to detect card
                        detectedFlag =  bPollingAction();
                        break;
                    case E_B_DETECTED:
                        /*
                         * Verify the detected card
                         */
                        verifyFlag = bVerifyAction();
                        currentState = S_BASE_SYSTEM_VERIFYING;
                        DBG("State = VERIFYING\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_VERIFYING:
                switch (currentEvent) {
                    case E_B_AUTHORIZED:
                        /*
                         * The card is authorized
                         */
                        bPassAction();
                        currentState = S_BASE_SYSTEM_UNLOCKING;
                        DBG("State = UNLOCKING\n");
                        break;
                    case E_B_DENIED:
                        /*
                         * The card is denied
                         */
                        bFailAction();
                        currentState = S_BASE_SYSTEM_WARNING;
                        DBG("State = WARNING\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_UNLOCKING:
                switch (currentEvent) {
                    case E_B_UNLOCKED: // This is a unlock timer event
                        bStopAction();
                        currentState = S_BASE_SYSTEM_UPLOADING;
                        DBG("State = UPLOADING\n");

                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_UPLOADING:
                switch (currentEvent) {
                    case E_B_ACKED:
                        currentState = S_BASE_SYSTEM_STOPPED;
                        DBG("State = STOPPED\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_UPLOADED:
                switch (currentEvent) {
                    case E_B_DETECTED:
                        bVerifyAction();
                        currentState = S_BASE_SYSTEM_VERIFYING;
                        break;
                    case E_B_FINISHED: // This is a warning timer event
                        currentState = S_BASE_SYSTEM_STOPPED;
                        break;
                    default:
                        break;
                }
                break;

            case S_BASE_SYSTEM_WARNING:
                switch (currentEvent) {
                    case E_B_DETECTED:
                        bStopAction();
                        bVerifyAction();
                        currentState = S_BASE_SYSTEM_VERIFYING;
                        break;
                    case E_B_FINISHED: // This is a warning timer event
                        bStopAction();
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
        currentEvent = E_B_AUTHORIZED;
        verifyFlag = YET_VERIFY;
    }
    else if(verifyFlag == VERIFY_FAIL)
    {
        currentEvent = E_B_DENIED;
        verifyFlag = YET_VERIFY;
    }

    if(detectedFlag == MI_OK)
    {
        currentEvent = E_B_DETECTED;
        detectedFlag = MI_NOTAGERR;
    }

    // Check warning timer and raise a flag
    if(warningTimerFlag)
    {
        currentEvent = E_B_FINISHED;
        warningTimerFlag = false;
    }

    // Check unlocked timer and raise a flag
    if(unlockedTimerFlag)
    {
        currentEvent = E_B_UNLOCKED;
        unlockedTimerFlag = false;
    }

    // TODO: Check ACK flag to raise ACKed event

}





