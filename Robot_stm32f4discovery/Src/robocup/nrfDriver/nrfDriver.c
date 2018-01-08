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
	0x0
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
	const TickType_t startTime = xTaskGetTickCount();
	int retry = 100;
	do {
		TM_NRF24L01_Transmit(dataOut);
		do {
			/* Get transmission status */
			transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
			//retry--;
		} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending && xTaskGetTickCount()-startTime < 1);
		//Get back into RX mode
		TM_NRF24L01_PowerUpRx();

		retry--;
	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Lost && retry > 0);

	if (retry == 0 || xTaskGetTickCount()-startTime >= 1) {
		LOG_ERROR("Transmission lost, fail to send\r\n");
	}
	if (retry > 0 && retry < 99 && xTaskGetTickCount()-startTime == 0) {
		LOG_ERROR("Transmission save by a retry\r\n");
	}
	taskYIELD();
	//static char str_tmp[100] = {0};
	//sprintf(str_tmp, "Transmission tooks %u\r\n", xTaskGetTickCount()-startTime);
	//LOG_INFO(str_tmp);
}

void nrfReceive(uint8_t * dataIn) {
	while (!TM_NRF24L01_DataReady()) {
		osDelay(1);// Prevent active wait
		//taskYIELD();
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
