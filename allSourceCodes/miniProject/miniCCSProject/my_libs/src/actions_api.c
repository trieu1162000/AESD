/*
 * actions_api.c
 *
 *  Created on: Nov 17, 2023
 *      Author: trieu
 */

#include "../inc/actions_api.h"

int8_t bVerifyAction(void)
{
    // Read the UID of card
    int i;

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

    // Simultaneously, enable the unlocked timer and wait for it to expire
    // At this time, it will point to the Timer Int Handler named timerUIntHandler
    TimerEnable(TIMER0_BASE, TIMER_A);

    // Then, we may put some data, means that raise an TX ISR

    // We may also turn on LED Green, Buzzer but shorter seconds

    // Subsequently, We may display something to the LCD
}

void bFailAction(void)
{
    // Here, We will lock the door immediately

    // Then, we may put turn on LED Red, Buzzer for longer seconds

    // Subsequently, We may want to warning something to the LCD}

}
void bStopAction(void)
{
    // Here, We will lock the door immediately

    // And, We may display something to the LCD
}

void rReceiveAction(void)
{
    // TODO: TBD
}

void rSyncAction(void)
{
    // TODO: TBD
}

void rWriteAction(void)
{
    // TODO: TBD
}

void rSendAction(void)
{
    // TODO: TBD
}

