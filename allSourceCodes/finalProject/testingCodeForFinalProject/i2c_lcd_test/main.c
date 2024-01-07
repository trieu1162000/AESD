

/**
 * main.c
 */
#include "LCD_I2C.h"

int main () {
  LCD_I2C lcd;
    LCDI2CInit(&lcd, 0x27, 16, 2);
    backlight(&lcd);
    const char* s = "Hello World\n";
    print(&lcd, s);
  while(1) {
      const char* s1 = "Pham Nhat\n";
      print(&lcd, s1);
      SysCtlDelay(SysCtlClockGet()/3);
      const char* s2 = "Trieu Huynh\n";
      print(&lcd, s2);
      SysCtlDelay(SysCtlClockGet()/3);

  }
}
