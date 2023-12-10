#include "my_libs/inc/config_peripherals_api.h"
#include "my_libs/inc/rc522_api.h"
#include "my_libs/inc/uart_api.h"
#include "my_libs/inc/lcd_i2c_api.h"
#include "my_libs/inc/timer_handler_api.h"
#include "my_libs/inc/system_FSM_api.h"
#include "my_libs/inc/eeprom_api.h"

//const uint32_t authorizedTestCardIDs[AUTHORIZED_CARD_COUNT][CARD_LENGTH] = {
//                        //    {0x25, 0xbd, 0x9d, 0x2d, 0x28},
//                           {0x25, 0xbd, 0x9d, 0x2d, 0x28},
//                           {0x88, 0x1d, 0x6a, 0x32, 0xcd},
//                           {0x88, 0x1d, 0x6d, 0x32, 0xca},
//                           {0x88, 0x1d, 0x6b, 0x32, 0xcc},
//                           {0x25, 0x30, 0x9d, 0x2d, 0x28},
//                           {0x25, 0x3d, 0x9d, 0x2d, 0x28}
//};

// uint32_t pui32Data[2];
uint32_t pui32Read[sizeof(card)*2];
// pui32Data[0] = 0x12345678;
// pui32Data[1] = 0x56789abc;

static void hd44780_init(struct lcd_i2c *lcd, struct lcd_i2c_geometry *geometry)
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
    // EEPROMMassErase();

    //======================================================================================

    initPeriphs();
    initSPI();
    initLEDs();
     initLock();
    initBuzzer();
    initTimer();
#ifdef  DEBUG
    initConsole();
#endif
    initUART();
    DBG("SSI Enabled! SPI Mode!  \r\nData: 8bits.\n\r");
    initRC522();
    initTestLED();

    //======================================================================================
    // Testing portion
    //======================================================================================
    // Initialize the card queue
    initCardQueue(&cardQueueForEEPROM);
    // enqueueCard(&myCardQueue, "Huynh Pham Nhat Trieu", 2370014, authorizedTestCardIDs[0]);
    // enqueueCard(&myCardQueue, "Huynh Pham Nhat", 2370015, authorizedTestCardIDs[1]);
    // enqueueCard(&myCardQueue, "Huynh Pham Trieu", 2370016, authorizedTestCardIDs[2]);
    // enqueueCard(&myCardQueue, "Huynh Nhat Trieu", 2370017, authorizedTestCardIDs[3]);
    // enqueueCard(&myCardQueue, "Pham Nhat Trieu", 2370018, authorizedTestCardIDs[4]);

    // saveCardsToEEPROM(&myCardQueue);
    // DBG("Save successfully\n");

    loadCardsFromEEPROM(&cardQueueForEEPROM);
    
    // printAllCards(&cardQueueForEEPROM);

    // uint32_t authorizedCardTestUUIDs[MAX_CARDS][CARD_LENGTH]  = {0};
    // card verifiedTestCard;
    // initCard(&verifiedTestCard);
    // getAuthorizedCardsUUID(&myCardQueueRead, authorizedCardTestUUIDs);
    // verifiedTestCard = getCardFromUUID(&myCardQueueRead, authorizedCardTestUUIDs[0]);
    // removeCard(&myCardQueueRead, 2370014);
    // result = updateCardBaseOnUUID(&myCardQueueRead, newCardUUID, "Trieu Huynh toi choi", 2366666);
    // printAllCards(&myCardQueueRead);



    //======================================================================================

    while(1)
    {
//        ledControl(LEDGREEN, ON);
//        SysCtlDelay(SysCtlClockGet()/3); //Delay

//        ledControl(LEDGREEN, OFF);
//        SysCtlDelay(SysCtlClockGet()/3); //Delay
         systemStateMachineUpdate();
         systemEventUpdate();

    }
}


