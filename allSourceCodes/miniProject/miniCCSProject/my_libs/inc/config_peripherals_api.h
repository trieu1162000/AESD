/*
 * config_peripherals_api.h
 *
 *  Created on: Oct 27, 2023
 *      Author: trieu
 */

#ifndef MY_LIBS_INC_CONFIG_PERIPHERALS_API_H_
#define MY_LIBS_INC_CONFIG_PERIPHERALS_API_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

extern void configureSPI(void);
extern void configureUART(void);


#endif /* MY_LIBS_INC_CONFIG_PERIPHERALS_API_H_ */
