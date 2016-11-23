/*
 * spi_wrapper.c
 *
 *  Created on: 2016-03-23
 *      Author: Gagnon
 */

#include "spi_wrapper.h"

#include "stm32f4xx_hal_spi.h"

void SPI_write_8bits(uint8_t data) {
	//for(int i =0;i<1000;++i);
	HAL_SPI_TransmitReceive(&hspi2, &data, &data, 1, 2000);
}




uint8_t SPI_read(void) {
	uint8_t sevData = 0;
	uint8_t retData = 0;
	//for(int i =0;i<100;++i);
	HAL_SPI_TransmitReceive(&hspi2, &sevData, &retData, 1, 2000);
	return retData;
}
