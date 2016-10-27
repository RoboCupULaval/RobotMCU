/*
 * bluetooth.h
 *
 *  Created on: Jul 2, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_BLUETOOTH_BLUETOOTH_H_
#define ROBOCUP_BLUETOOTH_BLUETOOTH_H_

#include "usart.h"

#include "com_interface.h"

comHandle_t bluetooth_init(void);
size_t      bluetooth_read(void *pBuffer, size_t length);
size_t      bluetooth_write(const void *pBuffer, size_t length);
size_t      bluetooth_readUntilZero(void *pBuffer, size_t length);

#endif /* ROBOCUP_BLUETOOTH_BLUETOOTH_H_ */
