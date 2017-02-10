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
#include "stdbool.h"

uint8_t MyAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xEA
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

void nrfSetRobotTX(uint8_t robotNumber) {
	TxAddress[4] = robotNumber;
    TM_NRF24L01_SetTxAddress(TxAddress);

}

void nrfSend(uint8_t * dataOut) {
	TM_NRF24L01_Transmit_Status_t transmissionStatus;
	uint8_t myStatus;


	TM_NRF24L01_Transmit(dataOut);
	//vTaskDelay(5); // Don't delete this, it's like embedded jesus for us desperate programmers!

	static uint32_t maxCount =0;
	static TickType_t maxDelta =0;
	static TickType_t minDelta = 0xffff;
	uint32_t count = 0;

	TickType_t lastWakeTime = xTaskGetTickCount();
	do {
		/* Get transmission status */
		transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
		//myStatus = TM_NRF24L01_GetStatus();
		count++;

	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
	TickType_t delta = xTaskGetTickCount() - lastWakeTime;
	if(count > maxCount){
		maxCount = count;
		maxDelta = delta;
	}
	minDelta = delta < minDelta ? delta : minDelta;
	//Get back into RX mode
	TM_NRF24L01_PowerUpRx();
}

void nrfReceive(uint8_t * dataIn) {
	while (!TM_NRF24L01_DataReady());
	TM_NRF24L01_GetData(dataIn);
}

bool nrfReceiveReady(void) {
	return TM_NRF24L01_DataReady();
}

uint8_t nrfRetransmitCount() {
	return TM_NRF24L01_GetRetransmissionsCount();
}

uint8_t nrfGetStatus() {
	return TM_NRF24L01_GetStatus();
}
