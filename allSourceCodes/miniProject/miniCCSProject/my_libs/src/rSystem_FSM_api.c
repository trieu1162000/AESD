/*
 * rSystem_FSM_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */


#include "../inc/rSystem_FSM_api.h"

#define CARD_LENGTH 5
#define MAX_LEN 16
#define AUTHORIZED_CARD_COUNT 6

#define VERIFY_PASS     1
#define VERIFY_FAIL     -1
#define YET_VERIFY      0

static rSystemState_t currentState = S_REMOTE_SYSTEM_STOPPED;
static rSystemEvents_t currentEvent = E_R_FINISHED;

static int8_t detectedFlag = MI_NOTAGERR;
unsigned char str[MAX_LEN];
unsigned char cardID[CARD_LENGTH];
static int8_t verifyFlag = YET_VERIFY;

void receiveAction(void)
{


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

void syncAction()
{

}

void writeAction()
{
    // Here, We will lock the door immediately

    // Then, we may put turn on LED Red, Buzzer for longer seconds

    // Subsequently, We may want to warning something to the LCD}

}

void sendAction()
{

}

void rSystemStateMachineUpdate(void)
{

        switch (currentState) {

            case S_REMOTE_SYSTEM_STOPPED:
                switch (currentEvent) {
                    case E_R_ISR_RECEIVE:
                        receiveAction();
                        currentState = S_REMOTE_SYSTEM_PARSING;
                        DBG("State = PARSING\n");
                        break;
                    case E_R_ISR_TRANSMIT:
                        sendAction();
                        currentState = S_REMOTE_SYSTEM_UPLOADING;
                        DBG("State = UPLOADING\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_REMOTE_SYSTEM_PARSING:
                switch (currentEvent) {
                    case E_R_SYNC:
                        /*
                         * The card is authorized
                         */
                        // TBD: Displaying, Unlocking the door
                        syncAction();
                        currentState = S_REMOTE_SYSTEM_SYNCHRONIZING;
                        DBG("State = UNLOCKING\n");

                        break;
                    case E_R_CONFIG:
                        /*
                         * The card is denied
                         */
                        // TBD: Warning, Locking the door
                        pollingAction();
                        currentState = S_REMOTE_SYSTEM_CONFIGURATING;
                        DBG("State = CONFIGURATING\n");

                        break;
                    case E_R_FINISHED:
                        /*
                         * The card is authorized
                         */
                        currentState = S_REMOTE_SYSTEM_STOPPED;
                        DBG("State = STOPPED\n");

                        break;
                    default:
                        break;
                }
                break;

            case S_REMOTE_SYSTEM_SYNCHRONIZING:
                switch (currentEvent) {
                    case E_R_ISR_RECEIVE:
                        receiveAction();
                        currentState = S_REMOTE_SYSTEM_PARSING;
                        DBG("State = PARSING\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_REMOTE_SYSTEM_CONFIGURATING:
                switch (currentEvent) {
                    case E_R_DETECT:
                        writeAction();
                        currentState = S_REMOTE_SYSTEM_WRITING;
                        DBG("State = CONFIGURATING\n");
                        break;
                    case E_R_ISR_RECEIVE:
                        receiveAction();
                        currentState = S_REMOTE_SYSTEM_PARSING;
                        DBG("State = PARSING\n");
                        break;
                    default:
                        break;
                }
                break;

            case S_REMOTE_SYSTEM_WRITING:
                switch (currentEvent) {
                    case E_R_ISR_RECEIVE:
                        receiveAction();
                        currentState = S_REMOTE_SYSTEM_PARSING;
                        DBG("State = PARSING\n");
                        break;
                    default:
                        break;
                }
                break;
            
            case S_REMOTE_SYSTEM_UPLOADING:
                switch (currentEvent) {
                    case E_R_ACKED:
                        currentState = S_REMOTE_SYSTEM_STOPPED;
                        DBG("State = STOPPED\n");
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
        currentEvent = E_R_AUTHORIZED;
        verifyFlag = YET_VERIFY;
    }
    else if(verifyFlag == VERIFY_FAIL)
    {
        currentEvent = E_R_DENIED;
        verifyFlag = YET_VERIFY;
    }
//    else if(verifyFlag == YET_VERIFY)
//        {
//            if(currentState == S_REMOTE_SYSTEM_VERIFYING)
//                currentEvent = E_R_FINISHED
//        }
    if(detectedFlag == MI_OK)
    {
        currentEvent = E_R_DETECTED;
        detectedFlag = MI_NOTAGERR;
    }

    // Check warning timer and raise a flag
    if(warningTimerFlag)
    {
        currentEvent = E_R_FINISHED;
        warningTimerFlag = false;
    }

    // Check unlocked timer and raise a flag
    if(unlockedTimerFlag)
    {
        currentEvent = E_R_UNLOCKED;
        unlockedTimerFlag = false;
    }
}





