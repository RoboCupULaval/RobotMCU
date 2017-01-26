/*
 * nrfDriver.c
 *
 *  Created on: Nov 18, 2016
 *      Author: znuxor
 */
#include "nrfDriver.h"
#include "tm_stm32_nrf24l01.h"
#include "FreeRTOS.h"
#include "task.h"

uint8_t MyAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xE7
};

uint8_t TxAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xE8
};

void nrfInit() {
	TM_NRF24L01_Init(2, 20);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_1M, TM_NRF24L01_OutputPower_0dBm);
	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
	TM_NRF24L01_PowerUpRx();
}

void nrfSend(uint8_t * dataOut) {
	TM_NRF24L01_Transmit_Status_t transmissionStatus;
	uint8_t myStatus;

	TM_NRF24L01_Transmit(dataOut);
	vTaskDelay(5); // Don't delete this, it's like embedded jesus for us desperate programmers!

	do {
		/* Get transmission status */
		transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
		myStatus = TM_NRF24L01_GetStatus();
	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
    //Get back into RX mode
	TM_NRF24L01_PowerUpRx();
}

void nrfReceive(uint8_t * dataIn) {
	while (!TM_NRF24L01_DataReady());
	TM_NRF24L01_GetData(dataIn);
}

uint8_t nrfRetransmitCount() {
	return TM_NRF24L01_GetRetransmissionsCount();
}

uint8_t nrfGetStatus() {
	return TM_NRF24L01_GetStatus();
}
