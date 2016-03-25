/*
 * spi_wrapper.c
 *
 *  Created on: 2016-03-23
 *      Author: Gagnon
 */

#include "spi_wrapper.h"

void SPI_write_8bits(uint8_t data) {
	HAL_SPI_Transmit_IT(&hspi2, &data, 1);
}

uint8_t SPI_read(void) {
	uint8_t retData = 0;
	HAL_SPI_Receive(&hspi2, &retData, 1, 100);
	return retData;
}
