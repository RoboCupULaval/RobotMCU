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
#include "../util.h"

uint8_t MyAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xE8
};

uint8_t TxAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xEA
};

void nrfInit(const size_t packetSize) {
	TM_NRF24L01_Init(100, packetSize);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_1M, TM_NRF24L01_OutputPower_0dBm);
	MyAddress[4] = robot_getID();
	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
	TM_NRF24L01_PowerUpRx();
}

void nrfSend(uint8_t * dataOut) {
	TM_NRF24L01_Transmit_Status_t transmissionStatus;
	uint8_t myStatus;

	TM_NRF24L01_Transmit(dataOut);
	vTaskDelay(10); // Don't delete this, it's like embedded jesus for us desperate programmers!

	do {
		// Get transmission status
		transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
		myStatus = TM_NRF24L01_GetStatus();
	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
    //Get back into RX mode
	TM_NRF24L01_PowerUpRx();
}

void nrfReceive(uint8_t * dataIn) {
	while (!TM_NRF24L01_DataReady()) {
		osDelay(1);// Prevent active wait
	}
	TM_NRF24L01_GetData(dataIn);
}

uint8_t nrfRetransmitCount(void) {
	return TM_NRF24L01_GetRetransmissionsCount();
}

uint8_t nrfGetStatus(void) {
	return TM_NRF24L01_GetStatus();
}
