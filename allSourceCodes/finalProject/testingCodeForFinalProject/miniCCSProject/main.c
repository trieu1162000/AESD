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
//    // Initialize EEPROM
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
//    EEPROMInit();
//    EEPROMMassErase();
//
//    //======================================================================================
//
    initPeriphs();
//    initSPI();
//    initLEDs();
//     initLock();
//    initBuzzer();
//    initTimer();
#ifdef  DEBUG
    initConsole();
#endif

    initI2C();
//    initUART();
//    DBG("SSI Enabled! SPI Mode!  \r\nData: 8bits.\n\r");
//    initRC522();
//    initTestLED();

    struct lcd_i2c *lcd = NULL;
    lcd = malloc(sizeof(*lcd));
    hd44780_init(lcd, lcd_i2c_geometries[0]);

    lcdInit(lcd);


    lcdSetCursorBlink(lcd, false);
    lcdSetCursorDisplay(lcd, false);
    lcdPrint(lcd, "Tr\nHuynh");
    lcd->dirty = true;



    while(1)
    {


    }
}

