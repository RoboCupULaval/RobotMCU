/*
 * nrfDriver.c
 *
 *  Created on: Nov 18, 2016
 *      Author: Frederic St-Pierre
 *      This is basically an interface.
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
	TM_NRF24L01_Init(100, 23);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_1M, TM_NRF24L01_OutputPower_0dBm);
	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
	TM_NRF24L01_PowerUpRx();
}

void nrfSetRobotTX(uint8_t robotNumber) {
	TxAddress[4] = robotNumber;
    TM_NRF24L01_SetTxAddress(TxAddress);

}

void nrfSend(uint8_t * dataOut) {//, bool forceRetryBool) {
	TM_NRF24L01_Transmit_Status_t transmissionStatus;
	//uint8_t myStatus;

	//do {
	TM_NRF24L01_Transmit(dataOut);
	do {
		/* Get transmission status */
		transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
		//myStatus = TM_NRF24L01_GetStatus();
	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
	//} while (forceRetryBool && transmissionStatus == TM_NRF24L01_Transmit_Status_Lost);
    if (transmissionStatus == TM_NRF24L01_Transmit_Status_Lost) {
    	HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
    }
    if (transmissionStatus == TM_NRF24L01_Transmit_Status_Ok) {
    	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
    }
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
