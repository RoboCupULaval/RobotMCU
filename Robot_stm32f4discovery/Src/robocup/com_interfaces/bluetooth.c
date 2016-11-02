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

static uint8_t* s_rxSerialBuffer;
static size_t s_rxSerialBufferLen = 0;
static volatile bool s_receivedPacket;

size_t bluetooth_readUntilZero(void *pBuffer, size_t length){
	if (length < 1)
		return 0;

	s_receivedPacket = false;
	s_rxSerialBuffer = pBuffer;
	s_rxSerialBufferLen = 0;

	// This setup a uart interrupt that is call at each time a byte is received.
	// The HAL_UART_RxCpltCallback callback handle the reception of the packet
	// and the detection of the zero character
	HAL_UART_Receive_IT(&huart5, s_rxSerialBuffer, 1);
	while(!s_receivedPacket);

	// length == strlen(s_rxSerialBuffer), so it does not count the zero character
	return s_rxSerialBufferLen;
}


// Custom callback for the reception of a packet
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	__HAL_UART_FLUSH_DRREGISTER(huart);

	char c = s_rxSerialBuffer[s_rxSerialBufferLen];
	// As long as the zero character is not received, the callback is
	// renable by calling HAL_UART_Receive_IT()
	if (c == '\0') {
		s_receivedPacket = true;
	} else {
		s_rxSerialBufferLen++;
		if (s_rxSerialBufferLen >= 255) {
			s_rxSerialBufferLen = 0;
		}
		HAL_UART_Receive_IT(&huart5, s_rxSerialBuffer + s_rxSerialBufferLen, 1);
	}
}
