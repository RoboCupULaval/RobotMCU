/*
 * nrf.h
 *
 *  Created on: Jan 11, 2017
 *      Author: znuxor
 */

#ifndef ROBOCUP_COM_INTERFACES_NRF_H_
#define ROBOCUP_COM_INTERFACES_NRF_H_

#include "stddef.h"

#include "../util.h"
#include "com_interface.h"


comHandle_t nrf_init(void);
size_t      nrf_read(void *pBuffer, size_t length);
size_t      nrf_write(const void *pBuffer, size_t length);
size_t      nrf_readUntilZero(void *pBuffer, size_t length);

#endif /* ROBOCUP_COM_INTERFACES_NRF_H_ */
