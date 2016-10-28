/*
 * bluetooth.c
 *
 *  Created on: Jul 2, 2016
 *      Author: philippe
 */
#include "bluetooth.h"

comHandle_t bluetooth_init(void){
	comHandle_t com;
	com.read = bluetooth_read;
	com.write = bluetooth_write;
	com.readUntilZero = bluetooth_readUntilZero;
	return com;
}

size_t bluetooth_read(void *pBuffer, size_t length){
	uint16_t length16b = length & 0xFFFF;
	HAL_StatusTypeDef res;
	do {
		res = HAL_UART_Receive(&huart5, (uint8_t*) pBuffer, length16b, HAL_MAX_DELAY);
	} while(res == HAL_BUSY || res == HAL_TIMEOUT);
	return res == HAL_OK ? length : 0;
}

size_t bluetooth_write(const void *pBuffer, size_t length){
	uint16_t length16b = length & 0xFFFF;
	HAL_StatusTypeDef res;
	do {
		res = HAL_UART_Transmit(&huart5, (uint8_t*) pBuffer, length16b, HAL_MAX_DELAY);
	} while(res == HAL_BUSY);
	return res == HAL_OK ? length : 0;
}

size_t bluetooth_readUntilZero(void *pBuffer, size_t length){
	uint8_t *buf = pBuffer;
	if (length < 1)
		return 0;
	size_t index = 0;
	while(index < length){
		uint8_t c;
		HAL_StatusTypeDef res = HAL_UART_Receive(&huart5, &c, 1, HAL_MAX_DELAY);
		if(res != HAL_OK)
			return 0;
		*buf++ = c;
		if (c == '\0')
			break;
		index++;
	}
	return index;
}
