/*
 * nrfDriver.c
 *
 *  Created on: Nov 18, 2016
 *      Author: znuxor
 */
#include "nrfDriver.h"
#include "tm_stm32_nrf24l01.h"

uint8_t MyAddress[] = {
	0xE7,
	0xE7,
	0xE7,
	0xE7,
	0xE7
};
/* Receiver address */
uint8_t TxAddress[] = {
	0x7E,
	0x7E,
	0x7E,
	0x7E,
	0x7E
};

void nrfInit() {
	TM_NRF24L01_Init(15, 32);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_2M, TM_NRF24L01_OutputPower_M18dBm);
	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
}

void nrfSend(uint8_t * dataOut) {
	TM_NRF24L01_Transmit_Status_t transmissionStatus;

	TM_NRF24L01_Transmit(dataOut);

	do {
						/* Get transmission status */
						transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
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
