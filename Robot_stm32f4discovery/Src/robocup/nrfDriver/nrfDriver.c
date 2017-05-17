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

void nrfInit(const size_t packetSize, const uint8_t robot_id) {
	TM_NRF24L01_Init((uint8_t)NRF_DEFAULT_RF_CH, (uint8_t)packetSize);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_1M, TM_NRF24L01_OutputPower_0dBm);

	MyAddress[4] = robot_id;

	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
	TM_NRF24L01_PowerUpRx();
}

void nrfSend(uint8_t * dataOut) {
	TM_NRF24L01_Transmit_Status_t transmissionStatus;
	int retry = 100;
	do {
		TM_NRF24L01_Transmit(dataOut);
		do {
			/* Get transmission status */
			transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
			taskYIELD();
			retry--;
		} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending && retry > 0);
		//Get back into RX mode
		TM_NRF24L01_PowerUpRx();

		retry--;
	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Lost && retry > 0);

	if (retry == 0) {
		LOG_ERROR("Transmission lost, after too many retries");
	}
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

bool nrfVerifySPI(void) {
	int val = TM_NRF24L01_ReadRegister(NRF_REG_RF_CH);
	if(val == NRF_DEFAULT_RF_CH)
		return true;
	else
		return false;
}
