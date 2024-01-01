#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include "../my_libs/inc/config_peripherals_api.h"
#include "../my_libs/inc/rc522_api.h"
#include "../my_libs/inc/uart_api.h"
#include "../my_libs/inc/lcd_i2c_api.h"
#include "../my_libs/inc/timer_handler_api.h"
#include "../my_libs/inc/eeprom_api.h"
#include "../my_libs/inc/states.h"
#include "../my_libs/inc/actions_api.h"

// Minimum stack size for FreeRTOS tasks.
#define STACK_SIZE 100

struct lcd_i2c *lcd = NULL;

// This is used by bFSM
SemaphoreHandle_t bTimerEventSemaphore_;
SemaphoreHandle_t bAcceptEventSemaphore_;
SemaphoreHandle_t bDispatchEventSemaphore_;

// This is used by gFSM
SemaphoreHandle_t gTimerEventSemaphore_;
SemaphoreHandle_t gAcceptEventSemaphore_;
SemaphoreHandle_t gDispatchEventSemaphore_;
SemaphoreHandle_t gUARTEventSemaphore_;
SemaphoreHandle_t pollingEventSemaphore_;

// This is used by both
SemaphoreHandle_t switchGUIEventSemaphore_;
SemaphoreHandle_t switchBareEventSemaphore_;

// Static functions
void dumpHex(unsigned char* buffer, int len){

    int i;
    UARTprintf(" ");
    for(i=0; i < len; i++) {
        UARTprintf("0x%x, ", buffer[i]);
    }
    UARTprintf("  FIM! \r\n"); //End

}

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}

void timerUIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

//     Raised the tRaised_
//    tRaised_ = TIMER_UNLOCKED;

//    // This will attempt to wake the MessageTask and continue execution there.
//    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//
//    // Give the semaphore and unblock the MessageTask.
//    xSemaphoreGiveFromISR(bTimerEventSemaphore_, &xHigherPriorityTaskWoken);
//
//    // If the MessageTask was successfully woken, then yield execution to it
//    //    and go there now (instead of changing context to another task).
//    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    bFSM_.event_ = BARE_E_UNLOCKED;

xSemaphoreGive(bDispatchEventSemaphore_);

}

void timerWIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // Raised the tRaised_
//    tRaised_ = TIMER_WARNED;
//
//    // This will attempt to wake the MessageTask and continue execution there.
//    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
//
//    // Give the semaphore and unblock the MessageTask.
//    xSemaphoreGiveFromISR(bTimerEventSemaphore_, &xHigherPriorityTaskWoken);
//
//    // If the MessageTask was successfully woken, then yield execution to it
//    //    and go there now (instead of changing context to another task).
//    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    bFSM_.event_ = BARE_E_WARNED;
xSemaphoreGive(bDispatchEventSemaphore_);
}

void timerAUIntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    // This will attempt to wake the MessageTask and continue execution there.
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Give the semaphore and unblock the MessageTask.
    xSemaphoreGiveFromISR(gTimerEventSemaphore_, &xHigherPriorityTaskWoken);

    // If the MessageTask was successfully woken, then yield execution to it
    //  and go there now (instead of changing context to another task).
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void gTimerTask(void *pvParameters)
{

    for (;;) {

        // Block until a timer trigger is received...
        BaseType_t taken = xSemaphoreTake(gTimerEventSemaphore_, portMAX_DELAY);
        if (taken == pdFAIL) {
            continue;
        }

        // Signal to the main task that the download is complete.
        // xSemaphoreTake(gAcceptEventSemaphore_, portMAX_DELAY);
        gFSM_.event_ = GUI_E_AU_TIMEOUT;
        xSemaphoreGive(gDispatchEventSemaphore_);

    }
}

void UARTTask(void *pvParameters)
{

    for (;;) {

        // Block until a UART trigger is received...
        BaseType_t taken = xSemaphoreTake(gUARTEventSemaphore_, portMAX_DELAY);
        if (taken == pdFAIL) {
            continue;
        }

        int i;
        bool result;
        size_t rawDataLength  = 0;

        DBG("Received Frame: ");
        for(i = 0; i<MAX_FRAME_LENGTH; i++)
            UARTprintf("%x ", mainFrame[i]);
        DBG("\n");

        rawDataLength = sizeof(mainFrame) / sizeof(mainFrame[0]);    // Get the data into the frame from the raw data
        result = parseFirstFrameInRawData((uint8_t *) mainFrame, rawDataLength);
        if(result)
        {
            // Parsing the data in receive frame into the card
            parseDataInFrame(receivedFrame, &cardNeedToDo);
            // Need to reset the frame before receiving again
            memset(rawReceivedFrame, 0, MAX_FRAME_LENGTH);
            memset(mainFrame, 0, MAX_FRAME_LENGTH);
            receivedFrameIndex = 0;

            // At here, need to switch from bareTask to GUITask
            if(bFSM_.event_ == BARE_E_GUI_REQUEST)
            {
                xSemaphoreGive(bDispatchEventSemaphore_);
            }
            else
                xSemaphoreGive(gDispatchEventSemaphore_);
        }

    }
}

void GUITask(void *pvParameters)
{

    for (;;) {

        xSemaphoreGive(gAcceptEventSemaphore_);

        // Block until an event is dispatched...
        BaseType_t taken = xSemaphoreTake(gDispatchEventSemaphore_, portMAX_DELAY);
        if (taken == pdFAIL) {
            continue;
        }

        // DBG("Bare task\n");
        bool result = false;
        switch (gFSM_.state_)
        {
            case GUI_S_STOPPED:
                switch (gFSM_.event_) {
                    case GUI_E_ADD:
                        gFSM_.state_ = GUI_S_ADDING;
                        bStartTimeOut();
                        DBG("State = ADDING\n");
                        break;
                    case GUI_E_UPDATE:
                        gFSM_.state_ = GUI_S_UPDATING;
                        bStartTimeOut();
                        DBG("State = UPDATING\n");
                        break;
                    case GUI_E_SYNC:
                        bSyncAction(&cardQueueForEEPROM);
                        gFSM_.state_ = GUI_S_SYNCHRONIZING;
                        DBG("State = SYNCHRONIZING\n");
                        break;
                    case GUI_E_REMOVE:
                        result = bRemoveAction(cardNeedToDo.id);
                        if (result)
                            printAllCards(&cardQueueForEEPROM);
                        else
                            DBG("Remove card with specify ID fail\n");
                        gFSM_.state_ = GUI_S_REMOVING;
                        DBG("State = REMOVING\n");
                        break;
                    case GUI_E_FINISHED:
                    case GUI_E_COMPLETED:
                        // Handle semaphore to back to the bare task
                        xSemaphoreGive(switchBareEventSemaphore_);
                        xSemaphoreTake(switchGUIEventSemaphore_, portMAX_DELAY);
                    default:
                        break;
                }
                break;

            case GUI_S_ADDING:
                switch (gFSM_.event_) {
                    case GUI_E_DETECTED:
                        if(bWriteAction(&cardNeedToDo))
                            DBG("Write data into card successfully\n");
                        else
                            DBG("Fail to write data into card\n");
                        gFSM_.state_ = GUI_S_MODIFYING;
                        DBG("State = MODIFYING\n");
                        break;
                    case GUI_E_AU_TIMEOUT:
                        bNACKAction();
                        gFSM_.state_ = GUI_S_STOPPED;
                        DBG("State = STOPPED\n");
                        break;
                    default:
                        break;
                }
                break;

            case GUI_S_UPDATING:
                switch (gFSM_.event_) {
                    case GUI_E_DETECTED:
                        if(bUpdateAction(&cardNeedToDo))
                            DBG("Update successfully\n");
                        else
                            DBG("Failed to update\n");
                        gFSM_.state_ = GUI_S_MODIFYING;
                        DBG("State = MODIFYING\n");
                        break;
                    case GUI_E_AU_TIMEOUT:
                        bNACKAction();
                        gFSM_.state_ = GUI_S_STOPPED;
                        DBG("State = STOPPED\n");
                        break;
                    default:
                        break;
                }
                break;

            case GUI_S_MODIFYING:
            case GUI_S_REMOVING:
            case GUI_S_SYNCHRONIZING:
                switch (gFSM_.event_) {
                    case GUI_E_ADD:
                        gFSM_.state_ = GUI_S_ADDING;
                        bStartTimeOut();
                        DBG("State = ADDING\n");
                        break;
                    case GUI_E_UPDATE:
                        gFSM_.state_ = GUI_S_UPDATING;
                        bStartTimeOut();
                        DBG("State = UPDATING\n");
                        break;
                    case GUI_E_SYNC:
                        bSyncAction(&cardQueueForEEPROM);
                        gFSM_.state_ = GUI_S_SYNCHRONIZING;
                        DBG("State = SYNCHRONIZING\n");
                        break;
                    case GUI_E_REMOVE:
                        result = bRemoveAction(cardNeedToDo.id);
                        if (result)
                            printAllCards(&cardQueueForEEPROM);
                        else
                            DBG("Remove card with specify ID fail\n");
                        gFSM_.state_ = GUI_S_REMOVING;
                        DBG("State = REMOVING\n");
                        break;
                    case GUI_E_FINISHED:
                        saveCardsToEEPROM(&cardQueueForEEPROM);
                        gFSM_.state_ = GUI_S_STOPPED;
                        gFSM_.event_ = GUI_E_COMPLETED;
                        DBG("State = STOPPED\n");
                        xSemaphoreGive(gDispatchEventSemaphore_);

                    default:
                        break;
                }
                break;

        }
    }
}

void bTimerTask(void *pvParameters)
{

    for (;;) {

        // Block until a timer trigger is received...
        BaseType_t taken = xSemaphoreTake(bTimerEventSemaphore_, portMAX_DELAY);
        if (taken == pdFAIL) {
            continue;
        }

        switch(tRaised_)
        {
            case TIMER_UNLOCKED:
                bFSM_.event_ = BARE_E_UNLOCKED;
                break;
            case TIMER_WARNED:
                bFSM_.event_ = BARE_E_WARNED;
                break;
        }
        xSemaphoreGive(bDispatchEventSemaphore_);

    }
}

void bareTask(void *pvParameters)
{

    for (;;) {

        xSemaphoreGive(bAcceptEventSemaphore_);

        // Block until an event is dispatched...
        BaseType_t taken = xSemaphoreTake(bDispatchEventSemaphore_, portMAX_DELAY);
        if (taken == pdFAIL) {
            continue;
        }

        // DBG("Bare task\n");

        switch (bFSM_.state_)
        {

            case BARE_S_STOPPED:
                switch (bFSM_.event_) {
                    case BARE_E_DETECTED:
                        bVerifyAction();
                        bFSM_.state_ = BARE_S_VERIFYING;
                        DBG("State = VERIFYING\n");
                        break;
                    case BARE_E_GUI_REQUEST:
                        bACKRequestAction();
                        DBG("Switch to the GUITask at here and wait until return back\n");
                        // Turn to the finish event
                        bFSM_.event_ = BARE_E_FINISHED;

                        xSemaphoreGive(switchGUIEventSemaphore_);
                        xSemaphoreTake(switchBareEventSemaphore_, portMAX_DELAY);
                        break;
                    default:
                        bFSM_.event_ = BARE_E_FINISHED;
                        break;
                }
                break;

            case BARE_S_VERIFYING:
                switch (bFSM_.event_) {
                    case BARE_E_AUTHORIZED:
                        /*
                            * The card is authorized
                            */
                        bPassAction();
                        bFSM_.state_ = BARE_S_UNLOCKING;
                        DBG("State = UNLOCKING\n");
                        break;
                    case BARE_E_DENIED:
                        /*
                            * The card is denied
                            */
                        bFailAction();
                        bFSM_.state_ = BARE_S_WARNING;
                        DBG("State = WARNING\n");
                        break;
                    default:
                        break;
                }
                break;

            case BARE_S_UNLOCKING:
                switch (bFSM_.event_) {
                    case BARE_E_DETECTED:
                        bVerifyAction();
                        bFSM_.state_ = BARE_S_VERIFYING;
                        DBG("State = VERIFYING\n");
                        break;
                    case BARE_E_UNLOCKED: // This is a unlock timer event
                        bStopAction();
                        bFSM_.state_ = BARE_S_STOPPED;
                        bFSM_.event_ = BARE_E_FINISHED;
                        DBG("State = STOPPED\n");
                        break;
                    default:
                        break;
                }
                break;

            case BARE_S_WARNING:
                switch (bFSM_.event_) {
                    case BARE_E_DETECTED:
                        bVerifyAction();
                        DBG("State = VERIFYING\n");
                        bFSM_.state_ = BARE_S_VERIFYING;
                        break;
                    case BARE_E_WARNED: // This is a warning timer event
                        bStopAction();
                        DBG("State = STOPPED\n");
                        bFSM_.state_ = BARE_S_STOPPED;
                        break;
                    default:
                        break;
                }
                break;

        }
    }
}

void pollingTask(void *pvParameters)
{
    for (;;) {

        if(bFSM_.state_ == BARE_S_VERIFYING)
            xSemaphoreTake(bAcceptEventSemaphore_, portMAX_DELAY);
        if(gFSM_.event_ != GUI_E_ADD && gFSM_.event_ != GUI_E_UPDATE && gFSM_.event_ != GUI_E_COMPLETED && gFSM_.event_ != GUI_E_FINISHED)
            xSemaphoreTake(gAcceptEventSemaphore_, portMAX_DELAY);

        int8_t status;
        status = rc522Request(PICC_REQIDL, str);
        if(status == MI_OK){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, HIGH_PIN);
            DBG("Card Detected! \r\n"); //Card Detected
        }

        status = rc522Anticoll(&str[2]);
        memcpy(cardUUID, &str[2], 5);

        // Handle the detected card here
        if(status == MI_OK){
            DBG("ID: \n\r");
            dumpHex((unsigned char *)cardUUID, CARD_LENGTH);
            SysCtlDelay(SysCtlClockGet()/6); //Delay
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LOW_PIN);
            // if((gFSM_.state_ == GUI_S_ADDING || gFSM_.state_ == GUI_S_UPDATING) && bFSM_.state_ == BARE_S_STOPPED)
            if(gFSM_.event_ == GUI_E_ADD || gFSM_.event_ == GUI_E_UPDATE)
            {
                gFSM_.event_ = GUI_E_DETECTED;
                xSemaphoreGive(gDispatchEventSemaphore_);
            }
            else
            {
                bFSM_.event_ = BARE_E_DETECTED;
                xSemaphoreGive(bDispatchEventSemaphore_);
            }
        }
        else
            vTaskDelay( 10/portTICK_PERIOD_MS );


    }
}

// Catch-all error handler.
static void errHandler(void)
{
        // Spin...
        while (1);
}

int initTasks()
{

    int success = -1;

    do {

        bTimerEventSemaphore_ = xSemaphoreCreateBinary();
        if (!bTimerEventSemaphore_) {
            break;
        }

        bAcceptEventSemaphore_ = xSemaphoreCreateBinary();
        if (!bAcceptEventSemaphore_) {
            break;
        }

        bDispatchEventSemaphore_ = xSemaphoreCreateBinary();
        if (!bDispatchEventSemaphore_) {
            break;
        }

        switchGUIEventSemaphore_ = xSemaphoreCreateBinary();
        if (!switchGUIEventSemaphore_) {
            break;
        }

        switchBareEventSemaphore_ = xSemaphoreCreateBinary();
        if (!switchBareEventSemaphore_) {
            break;
        }

        gUARTEventSemaphore_ = xSemaphoreCreateBinary();
        if (!gUARTEventSemaphore_) {
            break;
        }

        gTimerEventSemaphore_ = xSemaphoreCreateBinary();
        if (!gTimerEventSemaphore_) {
            break;
        }

        gAcceptEventSemaphore_ = xSemaphoreCreateBinary();
        if (!gAcceptEventSemaphore_) {
            break;
        }

        gDispatchEventSemaphore_ = xSemaphoreCreateBinary();
        if (!gDispatchEventSemaphore_) {
            break;
        }

        // The bTimer task will have a highest priority
        xTaskCreate(bTimerTask, "Timer", STACK_SIZE, NULL, 3, NULL);

        // The gTimer task will have a highest priority
        xTaskCreate(gTimerTask, "gTimer", STACK_SIZE, NULL, 3, NULL);

        // The UART task will have a highest priority
        xTaskCreate(UARTTask, "UART", STACK_SIZE * 3, NULL, 3, NULL);

        // The Bare task will have a higher priority than the Polling task.
        xTaskCreate(bareTask, "Bare", STACK_SIZE * 3, NULL, 2, NULL);

        // The GUI task will have a higher priority than the Polling task.
        xTaskCreate(GUITask, "GUI", STACK_SIZE * 3, NULL, 2, NULL);

        // Create the track tasks at the lowest priority.
        xTaskCreate(pollingTask, "Polling", STACK_SIZE * 3, NULL, 1, NULL);

        success = 0;

    }    while (pdFALSE);


    return success;

}

static void initParamsLCD(struct lcd_i2c *lcd, struct lcd_i2c_geometry *geometry)
{
    lcd->geometry = geometry;
    lcd->pos.row = 0;
    lcd->pos.col = 0;
    memset(lcd->esc_seq_buf.buf, 0, ESC_SEQ_BUF_SIZE);
    lcd->esc_seq_buf.length = 0;
    lcd->is_in_esc_seq = false;
    lcd->backlight = true;
    lcd->cursor_blink = false;
    lcd->cursor_display = false;
}

void initTestLED(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
}

int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //======================================================================================
    // Testing portion
    //======================================================================================
    // Initialize EEPROM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    EEPROMInit();
//    EEPROMMassErase();

    //======================================================================================

    initPeriphs();
    initSPI();
    initI2C();
    initLEDs();
    initLock();
    initBuzzer();
    initTimer();
#ifdef  DEBUG
    initConsole();
#endif

    initUART();

    initTestLED();

    initRC522();


    DBG("SSI Enabled! SPI Mode!  \r\nData: 8bits.\n\r");

    // Initialize the card queue
    initCardQueue(&cardQueueForEEPROM);

    loadCardsFromEEPROM(&cardQueueForEEPROM);

    printAllCards(&cardQueueForEEPROM);

//    dequeueCard(&cardQueueForEEPROM, &testCard);
//    saveCardsToEEPROM(&cardQueueForEEPROM);

    bFSM_.event_ = BARE_E_FINISHED;
    bFSM_.state_ = BARE_S_STOPPED;
    gFSM_.event_ = GUI_E_FINISHED;
    gFSM_.state_ = GUI_S_STOPPED;

    lcd = malloc(sizeof(*lcd));
    initParamsLCD(lcd, lcd_i2c_geometries[0]);
    lcdInit(lcd);

    lcdSetCursorBlink(lcd, false);
    lcdSetCursorDisplay(lcd, false);
    normalDisplay();
//    passDisplay();

    
    //======================================================================================

    if (initTasks()) {
       errHandler();
    }

    // Startup of the FreeRTOS scheduler.  The program should block here.
    vTaskStartScheduler();

    // The following line should never be reached.  Failure to allocate enough
    //    memory from the heap would be one reason.
    for (;;);

}



