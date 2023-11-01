/*
 * config_peripherals_api.h
 *
 *  Created on: Oct 27, 2023
 *      Author: Trieu Huynh Pham Nhat
 */

#ifndef MY_LIBS_INC_CONFIG_PERIPHERALS_API_H_
#define MY_LIBS_INC_CONFIG_PERIPHERALS_API_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/uart.h"
#include "driverlib/i2c.h"

extern void configureSPI(void);
extern void configureUART(void);
extern void configureI2C(void);

#endif /* MY_LIBS_INC_CONFIG_PERIPHERALS_API_H_ */
