/*
 * spi_wrapper.h
 *
 *  Created on: 2016-03-23
 *      Author: Gagnon
 */

#ifndef APPLICATION_USER_SPI_WRAPPER_H_
#define APPLICATION_USER_SPI_WRAPPER_H_

#include "stm32f4xx_hal.h"

#include "robocup_define.h"

void SPI_write_8bits(uint8_t data);
uint8_t SPI_read(void);

#endif /* APPLICATION_USER_SPI_WRAPPER_H_ */
