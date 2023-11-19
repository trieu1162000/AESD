#include "my_libs/inc/config_peripherals_api.h"
#include "my_libs/inc/rc522_api.h"
#include "my_libs/inc/uart_api.h"
#include "my_libs/inc/lcd_i2c_api.h"
#include "my_libs/inc/timer_handler_api.h"
#include "my_libs/inc/bSystem_FSM_api.h"

#define CARD_LENGTH 10
#define MAX_LEN 16

unsigned char str[MAX_LEN];
unsigned char cardID[CARD_LENGTH];

volatile uint8_t rc522IRQFlag = 0;


void initLeds(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
}

void dumpHex(unsigned char* buffer, int len);

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


int main(void) {

    int8_t status;
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//    configureUART();
    initPeriphs();
    configureSPI();
    initLeds();
#ifdef  DEBUG
    initConsole();
#endif
    DBG("SSI Enabled! SPI Mode!  \r\nData: 8bits.\n\r");
    rc522Init();
    initTimer();


    //===========================================================================
    // Testing RFID portion
    //===========================================================================
    //
////    rc522WriteRaw(RC522_REG_COMM_IRQ, 0x7F);
//    rc522WriteRaw(RC522_REG_COMM_IE_N, 0xA0);
////    rc522WriteRaw(RC522_REG_DIV1_EN, 0x14);

    while(1)
    {


        bSystemStateMachineUpdate();
        bSystemEventUpdate();
//        status = rc522Request(PICC_REQIDL, str);
//        if(status == MI_OK){
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, HIGH_PIN);
//            DBG("Cartao Detectado! \r\n"); //Card Detected
//        }
//
//       status = rc522Anticoll(&str[2]);
//        memcpy(cardID, &str[2], 5);
//
//        if(status == MI_OK){
//            DBG("ID: \n\r");
//            dumpHex((unsigned char *)cardID, CARD_LENGTH);
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LOW_PIN);
//            SysCtlDelay(SysCtlClockGet()/3); //Delay
//        }

    }




    //===========================================================================

    // Testing LCD portion
//    configureI2C();

//    struct lcd_i2c *lcd = NULL;
//    lcd = malloc(sizeof(*lcd));
//    hd44780_init(lcd, lcd_i2c_geometries[0]);
//    SysCtlDelay( (SysCtlClockGet()/3 / 500)); // Delay ms
//
//    lcdInit(lcd);
//    SysCtlDelay( (SysCtlClockGet()/3 / 500)); // Delay ms
//
//    lcdSetCursorBlink(lcd, false);
//    lcdSetCursorDisplay(lcd, false);


//    lcdInit();
//    lcdClearDisplay();
//    lcdGotoXY(1, 1);
//    lcdSendString("Hello world");
//    SysCtlDelay( (SysCtlClockGet()/3)); // Delay ms
//    while(1){

////        if(rc522IRQFlag == 1){
////            rc522IRQFlag = 0;
////            DBG("About to raise ISR\n");
////
////            SysCtlDelay( (SysCtlClockGet()/3)); // Delay ms
//            DBG("Start raise ISR 1\n");
//
//            status = rc522Request(PICC_REQIDL, str);
////            if(status == MI_OK){
////                GPIOIntDisable(GPIO_PORTE_BASE, GPIO_PIN_2);
////
//////                rc522IRQFlag = 1;
////                DBG("Cartao Detectado! \r\n"); //Card Detected
////            }
//            DBG("Start raise ISR 2\n");
////        if(rc522IRQFlag == 1){
////            rc522IRQFlag = 0;
////            status = rc522Anticoll(str);
////            memcpy(cardID, str, 10);
////
////            if(status == MI_OK){
////                DBG("ID: \n\r");
////                dumpHex((unsigned char *)cardID, CARD_LENGTH);
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LOW_PIN);
//                SysCtlDelay(SysCtlClockGet()/2); //Delay
////                DBG("Flag: %d\n\r", rc522IRQFlag);
////            }
////            GPIOIntEnable(GPIO_PORTE_BASE, GPIO_PIN_2);
////
//////            rc522WriteRaw(RC522_REG_COMM_IRQ, 0x7F);
////
////        }
//
////        lcdPrint(lcd, "hello world\n");
//////        lcd->dirty = true;
////        hd44780_init(lcd, lcd_i2c_geometries[0]);
////        SysCtlDelay( (SysCtlClockGet()/3)); // Delay ms
//
//
////        lcdGotoXY(2, 0);
////        lcdSendString("Hello world");
////        lcdGotoXY(3, 0);
////        lcdSendString("Hello hpntrieu");
////        lcdGotoXY(4, 0);
////        lcdSendString("okie hpntrieu");
////        SysCtlDelay( (SysCtlClockGet()/3*2)); // Delay ms
//
//
//        // UART testing portion
////        UARTStringPut(UART1_BASE, "Trieu Huynh toi choi! \r\n"); //Card Detected
////        SysCtlDelay(SysCtlClockGet()/3); //Delay



//    }
}


//void dumpHex(unsigned char* buffer, int len){
//    int i;
////    char tempBuffer[10] = {'\0'};
//
//    UARTStringPut(UART0_BASE, " ");
//    for(i=0; i < len; i++) {
//        UARTprintf("0x%x, ", buffer[i]);
////        UARTprintf(tempBuffer);
//    }
//    UARTprintf("  FIM! \r\n"); //End
//
//}

//
//
////*****************************************************************************
//
//#include <stdbool.h>
//#include <stdint.h>
//#include "inc/hw_i2c.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_types.h"
//#include "driverlib/gpio.h"
//#include "driverlib/i2c.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/uart.h"
//#include "utils/uartstdio.h"
//#include "driverlib/rom_map.h"
//
//#define SLAVE_ADDRESS0 0x7E
//
////==============================================================================
//void I2C_init(uint32_t data)
//{
//                //
//                // Enable Peripheral Clocks
//                //
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//
//    //reset module
//    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
//                //
//                // Enable pin PA7 for I2C1 I2C1SDA
//                //
////                MAP_GPIOPinConfigure(GPIO_PA7_I2C1SDA);
////                MAP_GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
//
//                //
//                // Enable pin PA6 for I2C1 I2C1SCL
//                //
//                GPIOPinConfigure(GPIO_PB2_I2C0SCL);
//                GPIOPinConfigure(GPIO_PB3_I2C0SDA);
//                GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
//                GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
////                MAP_GPIOPinConfigure(GPIO_PA6_I2C1SCL);
////                MAP_GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
//                //
//                // Enable and initialize the I2C0 master module.  Use the system clock for
//                // the I2C0 module.  The last parameter sets the I2C data transfer rate.
//                // If false the data rate is set to 100kbps and if true the data rate will
//                // be set to 400kbps.  For this example we will use a data rate of 100kbps.
//                //
//                I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
//
//                //
//                // Modifiy the data direction to true, so that seeing the address will
//                // indicate that the I2C Master is initiating a read from the slave.
//                //
//                I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS0, false);
//
//                 //clear I2C FIFOs
//    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
//
//}
////==============================================================================
//static void write_slave(uint32_t data)
//{
//                //
//                // Modifiy the data direction to true, so that seeing the address will
//                // indicate that the I2C Master is initiating a read from the slave.
//                //
//                I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS0, false);
//                //
//        // Place the data to be sent in the data register
//        //
//        I2CMasterDataPut(I2C0_BASE, data);
//
//        //
//        // Initiate send of data from the master.
//        //
//        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
//
//        //
//        // Wait until the slave has received and acknowledged the data.
//        //
//       // while(!(I2CSlaveStatus(I2C0_BASE) & I2C_SLAVE_ACT_RREQ))
//        //{
//        //}
//                while(I2CMasterBusy(I2C0_BASE));
//}
////*****************************************************************************
////==============================================================================
///*======Mã (HEX) Lenh denn thanh ghi cua LCD=========
//01 Xoá màn hình hien thi
//02 Tro ve dau dòng
//04 Giam con tro(dich con tro sang trái )
//06 Tang con tro(dich con tro sang phai)
//05 Dich hien thi sang phai
//07 Dich hien thi sang trái
//08 Tat con tro, tat hiin thi ok
//0a Tat hien thi, bat con tro
//0c Bat hien thi, tat con tro ok
//0e Bat hien thi, nhap nháy con tro
//0f nhap nháy con tro ok
//10 Dich vi trí con tro sang trái
//14 Dich vi trí con tro sang phai
//18 Dich toàn bo hien thi sang trái
//1c Dich toàn bo hien thi sang phai
//80 Ép con tro ve dau dòng thu nhat
//c0 Ép con tro ve dau dòng thu hai
//38 Hai dòng và ma tran kieu5x7.
//*/
////==============================================================================
//static void Delay_lcd(uint16_t nCount)
//{
//  /* Decrement nCount value */
//  while (nCount != 0)
//  {
//    nCount--;
//  }
//}
////==============================================================================
//void Lcd_write_4bit(uint8_t RS,uint8_t RW,uint8_t data,uint8_t led) // ghi 4 bit thap
//// RS = 0 lenh,= 1 du lieu, RW = 0 ghi, = 1 doc, led = 1 on, = 0 off
//{
//  uint8_t a = 0;
//  a = (data & 0x0F)<<4; // 4 bit low
//  if(RS==1) a += 0x1;   // bit 0
//  if(RW==1) a += 0x2;   // bit 1
//  a           += 0x4 ;  // bit 2 , EN = 1
//  if(led>0) a += 0x8;   // bit 3
//  write_slave(a); // EN = 1
//  Delay_lcd(200);
//  a -= 0x4 ; // bit 2 , EN = 0
//  write_slave(a); // EN = 0
//  Delay_lcd(200);
//}
////==============================================================================
//void Lcd_write(uint8_t RS,uint8_t RW,uint8_t data,uint8_t led)
//{// RS = 0 lenh,= 1 du lieu, RW = 0 ghi, = 1 doc, led = 1 on, = 0 off
//  Lcd_write_4bit(RS,RW,data>>4   ,led); // 4 bit high
//  Lcd_write_4bit(RS,RW,data      ,led); // 4 bit low
//}
////==============================================================================
//void Lcd_write_char(uint8_t data,uint8_t led)
//{// data ky tu can ghi, led = 1 on, = 0 off
//  Lcd_write(1,0,data,led);
//}
////==============================================================================
//void LCD_Puts (char *s)
//{//Ham ghi 1 chuoi ky tu
//        while (*s){
//                Lcd_write_char(*s,1);
//                s++;
//        }
//}
////==============================================================================
//void Lcd_write_1(uint8_t num,uint8_t led)
//{// ghi 1 chu so len lcd, led = 1 on, = 0 off
//  if((num<=9)) Lcd_write(1,0,num+0x30,led);
//}
////==============================================================================
//uint8_t Lcd_write_digit(uint8_t n,uint16_t num,uint8_t space,uint8_t led)
//{// ghi chu so thu n (tinh tu so hang nghin)cua so num len lcd, led = 1 on, = 0 off
//  // neu chu so duoc ghi = 0 va space = 1 thi ghi ra khoang trang thay vi so 0
//  uint8_t temp;
//  if(n==1) // chu so hang nghin
//  {
//    temp = num/1000; // lay so hang nghin
//    if((space>0)&(temp==0)) Lcd_write_char(0x20,led); else
//    Lcd_write_1(temp,led); // ghi len lcd
//  }
//  else if(n==2) // chu so hang tram
//  {
//    num = num/100; // lay so hang nghin
//    temp = num %10; // lay phan du
//    if((space>0)&(temp==0)) Lcd_write_char(0x20,led); else
//    Lcd_write_1(temp,led); // ghi len lcd
//  }
//  else if(n==3) // chu so hang chuc
//  {
//    num = num/10; // lay so hang chuc
//    temp = num %10; // lay phan du
//    if((space>0)&(temp==0)) Lcd_write_char(0x20,led); else
//    Lcd_write_1(temp,led); // ghi len lcd
//  }
//  else if(n==4) // chu so hang dvi
//  {
//    temp = num%10; // lay so hang dvi
//    Lcd_write_1(temp,led); // ghi len lcd
//  }
//  if((space>0)&(temp==0)) return 1 ; else return 0; // kiem tra xem chu so nay co duoc hien thi hay khong = 1 ko, = 0 co
//}
////==============================================================================
//void Lcd_write_4(uint8_t n,uint16_t num,uint8_t led)
//{// ghi n chu so cua so num len lcd, led = 1 on, = 0 off
//  // chu so vo nghia duoc thay bang dau cach
//  uint8_t space;
//  if     (n==1) // 1 chu so
//  {
//    Lcd_write_digit(4,num,0,1); // so hang dvi
//  }
//  else if(n==2) // 2 chu so
//  {
//    Lcd_write_digit(3,num,1,1); // so hang chuc
//    Lcd_write_digit(4,num,0,1); // so hang dvi
//  }
//  else if(n==3)  // 3 chu so
//  {
//    space = Lcd_write_digit(2,num,1,1); // so hang tram
//    Lcd_write_digit(3,num,space,1); // so hang chuc
//    Lcd_write_digit(4,num,0,1); // so hang dvi
//  }
//  else if(n==4) // 4 chu so
//  {
//    space = Lcd_write_digit(1,num,1,1); // so hang nghin
//    space = Lcd_write_digit(2,num,space,1); // so hang tram
//    Lcd_write_digit(3,num,space,1); // so hang chuc
//    Lcd_write_digit(4,num,0,1); // so hang dvi
//  }
//}
////==============================================================================
//void Lcd_Goto(unsigned char x, unsigned char y)
//{ // di chuyen con tro den cot x hang y
//  // x = 0 -> 19
//  // y = 0 -> 3
//        unsigned char address;
//        if     (y==0) address=(0x80+x);
//        else if(y==1) address=(0xC0+x);
//        else if(y==2) address=(0x94+x);
//        else if(y==3) address=(0xD4+x);
//        Lcd_write(0,0,address  ,1); // ghi lenh
//}
////==============================================================================
//void Lcd_init(void)
//{
//  Lcd_write(0,0,0x32   ,1); //
//  Lcd_write(0,0,0x28   ,1); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
//  Lcd_write(0,0,0x0c   ,1); // cho phep hien thi man hinh
//  Lcd_write(0,0,0x06   ,1); // tang ID, khong dich hinh
//  Lcd_write(0,0,0x01   ,1); // xoa man hinh
//}
//
//
//int main(){
//        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
//        Lcd_init();
//        Lcd_Goto(0, 0);
//        LCD_Puts("Hello world");
//        while(1)
//        {
//
//        }
//
//}



