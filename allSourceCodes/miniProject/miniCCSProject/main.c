#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "my_libs/inc/config_peripherals_api.h"
#include "my_libs/inc/rc522_api.h"
#include "my_libs/inc/uart_api.h"


int main(void) {


//    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    configureUART();
    configureSPI();

    while (1)
    {

        // TBD

    }

}