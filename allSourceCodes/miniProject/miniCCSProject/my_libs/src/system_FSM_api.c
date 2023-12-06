/*
 * system_FSM_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */

#include "../inc/system_FSM_api.h"

uint8_t ISRReceiveFlag = 0;
static int8_t verifyFlag = YET_VERIFY;

void systemStateMachineUpdate(void)
{

    bool result = false;
    switch (currentState)
    {

        case S_STOPPED:
            switch (currentEvent) {
                case E_DETECTED:
                    verifyFlag = bVerifyAction();
                    currentState = S_VERIFYING;
                    DBG("State = VERIFYING\n");
                    break;
                case E_ISR_RECEIVE:
                    bReceiveAction();
                    currentState = S_PARSING;
                    DBG("State = PARSING\n");
                    break;
                case E_FINISHED: // Polling to detect the card
                    detectedFlag = bPollingAction();
                    break;
                default:
                    break;
            }
            break;

        case S_VERIFYING:
            switch (currentEvent) {
                case E_AUTHORIZED:
                    /*
                        * The card is authorized
                        */
                    bPassAction();
                    currentState = S_UNLOCKING;
                    DBG("State = UNLOCKING\n");
                    break;
                case E_DENIED:
                    /*
                        * The card is denied
                        */
                    bFailAction();
                    currentState = S_WARNING;
                    DBG("State = WARNING\n");
                    break;
                default:
                    break;
            }
            break;

        case S_UNLOCKING:
            switch (currentEvent) {
                case E_DETECTED:
                    verifyFlag = bVerifyAction();
                    currentState = S_VERIFYING;
                    DBG("State = VERIFYING\n");
                    break;
                case E_UNLOCKED: // This is a unlock timer event
                    bStopAction();
                    currentState = S_STOPPED;
                    currentEvent = E_FINISHED;
                    DBG("State = STOPPED\n");
                    break;
                default:
                    break;
            }
            break;

        case S_WARNING:
            switch (currentEvent) {
                case E_DETECTED:
                    verifyFlag = bVerifyAction();
                    DBG("State = VERIFYING\n");
                    currentState = S_VERIFYING;
                    break;
                case E_FINISHED: // This is a warning timer event
                    bStopAction();
                    DBG("State = STOPPED\n");
                    currentState = S_STOPPED;
                    break;
                default:
                    break;
            }
            break;

        case S_PARSING:
            switch (currentEvent) {
                case E_SYNC:
                    bSyncAction(&cardQueueForEEPROM);
                    currentState = S_SYNCHRONIZING;
                    DBG("State = SYNCHRONIZING\n");
                    break;
                case E_ADD:
                    bStartTimeOut();
                    detectedFlag = bPollingAction();
                    currentState = S_ADDING;
                    DBG("State = ADDING\n");
                    break;
                case E_REMOVE:
                    result = bRemoveAction(cardNeedToDo.id);
                    if (result)
                        printAllCards(&cardQueueForEEPROM);
                    else
                        DBG("Remove card with specify ID fail\n");
                    currentState = S_REMOVING;
                    DBG("State = REMOVING\n");
                    break;
                case E_UPDATE:
                    bStartTimeOut();
                    detectedFlag = bPollingAction();
                    currentState = S_UPDATING;
                    DBG("State = UPDATING\n");
                    break;
                case E_GUI_FINISHED:
                    currentState = S_STOPPED;
                    currentEvent = E_FINISHED;
                    DBG("State = STOPPED\n");
                    break;
                case E_REQUEST:
                    bACKRequestAction();
                    currentState = S_MANAGING;
                    DBG("State = MANAGING\n");
                    break;
                case E_FINISHED:
                    currentState = S_STOPPED;
                    DBG("State = STOPPED\n");
                    break;
                default:
                    break;
            }
            break;

        case S_MANAGING:
            switch (currentEvent) {
                case E_ISR_RECEIVE:
                    bReceiveAction();
                    currentState = S_PARSING;
                    DBG("State = PARSING\n");
                    break;
                default:
                    break;
            }
            break;

        case S_SYNCHRONIZING:
            switch (currentEvent) {
                case E_ISR_RECEIVE:
                    bReceiveAction();
                    currentState = S_PARSING;
                    DBG("State = PARSING\n");
                    break;
                default:
                    break;
            }
            break;

        case S_ADDING:
            switch (currentEvent) {
                case E_AU_TIMEOUT:
                    bNACKAction();
                    currentState = S_MANAGING;
                    DBG("State = MAnNAGING\n");
                    break;
                case E_ADD:
                    detectedFlag = bPollingAction();
                    // DBG("State = ADDING\n");
                    break;
                case E_DETECTED:
                    bWriteAction();
                    currentState = S_MODIFYING;
                    DBG("State = MODIFYING\n");
                    break;
                default:
                    break;
            }
            break;

        case S_MODIFYING:
            switch (currentEvent) {
                case E_ISR_RECEIVE:
                    bReceiveAction();
                    currentState = S_PARSING;
                    DBG("State = PARSING\n");
                    break;
                default:
                    break;
            }
            break;

        case S_REMOVING:
            switch (currentEvent) {
                case E_ISR_RECEIVE:
                    bReceiveAction();
                    currentState = S_PARSING;
                    DBG("State = PARSING\n");
                    break;
                default:
                    break;
            }
            break;

        case S_UPDATING:
            switch (currentEvent) {
                case E_AU_TIMEOUT:
                    bNACKAction();
                    currentState = S_MANAGING;
                    DBG("State = MAnNAGING\n");
                    break;
                case E_UPDATE:
                    detectedFlag = bPollingAction();
                    // DBG("State = ADDING\n");
                    break;
                case E_DETECTED:
                    if(bUpdateAction(&cardNeedToDo))
                        DBG("Update successfully\n");
                    else
                        DBG("Failed to update\n");
                    currentState = S_MODIFYING;
                    DBG("State = MODIFYING\n");
                    break;
                default:
                    break;
            }
            break;

    }

}

void systemEventUpdate()
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

    if(detectedFlag == MI_OK)
    {
        currentEvent = E_DETECTED;
        detectedFlag = MI_NOTAGERR;
    }

    // Some data is received, the flag is already raised
    if(ISRReceiveFlag == 1 && strlen(mainFrame) > 0)
    {
        currentEvent = E_ISR_RECEIVE;
        ISRReceiveFlag = 0;
    }

}





