/*
 * bluetooth.h
 *
 *  Created on: Jul 2, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_BLUETOOTH_BLUETOOTH_H_
#define ROBOCUP_BLUETOOTH_BLUETOOTH_H_

#include <stdbool.h>
#include "usart.h"
#include "stm32f4xx_hal_conf.h"

#include "com_interface.h"

comHandle_t bluetooth_init(bool useAsConsole);
size_t      bluetooth_read(void *pBuffer, size_t length);
size_t      bluetooth_write(const void *pBuffer, size_t length);
size_t      bluetooth_readUntilZero(void *pBuffer, size_t length);

#endif /* ROBOCUP_BLUETOOTH_BLUETOOTH_H_ */
