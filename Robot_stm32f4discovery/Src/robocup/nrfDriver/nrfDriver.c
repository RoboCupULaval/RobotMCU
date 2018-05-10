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

void nrfInit(const uint8_t robot_id) {
	TM_NRF24L01_Init((uint8_t)NRF_DEFAULT_RF_CH, (uint8_t)PACKET_SIZE);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_1M, TM_NRF24L01_OutputPower_0dBm);

	MyAddress[4] = robot_id;

	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
	TM_NRF24L01_PowerUpRx();

	if (!nrfVerifySPI()) {
		LOG_ERROR("NRF SPI IS FAILING\r\n");
	}
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

#ifdef DELTA
	uint32_t ulNotificationValue;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(1000);

	while (!TM_NRF24L01_DataReady()) {
		// Wait for the interrupt EXTI15_10_IRQHandler to wake us up
		ulNotificationValue = ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
		// Timeout
		if (ulNotificationValue != 1) {
			if (!nrfVerifySPI()) {
				LOG_ERROR("NRF has reset for some reason, reconf nrf...\r\n");
				nrfInit(MyAddress[4]);
			}
			//else {
			//	LOG_INFO("Reset nrf just in case...\r\n");
			//}
		}
	}
#else
	int i = 0;
	while (!TM_NRF24L01_DataReady()) {
		osDelay(1);// Prevent active wait
		i++;
		if (i > 500) {
			if (!nrfVerifySPI()) {
			LOG_ERROR("NRF has reset for some reason, reconfigurating nrf...\r\n");
			nrfInit(MyAddress[4]);
			}
			i = 0;
		}
	}

#endif
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
	return val == NRF_DEFAULT_RF_CH;
}
