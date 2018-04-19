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

#define NRF24L01_SPI SPI2

#define NRF24L01_EN_CRC			3
#define NRF24L01_CRCO			2
#define NRF24L01_PWR_UP			1
#define NRF24L01_PRIM_RX		0

#define NRF24L01_REG_CONFIG			0x00	//Configuration Register
#define NRF24L01_REG_OBSERVE_TX		0x08	//Transmit observe register
#define NRF24L01_REG_RX_ADDR_P0		0x0A	//Receive address data pipe 0. 5 Bytes maximum length.
#define NRF24L01_REG_RX_ADDR_P1		0x0B	//Receive address data pipe 1. 5 Bytes maximum length.
#define NRF24L01_REG_TX_ADDR		0x10	//Transmit address. Used for a PTX device only

#define NRF24L01_CONFIG			((1 << NRF24L01_EN_CRC) | (0 << NRF24L01_CRCO))

#define NRF24L01_FLUSH_TX_MASK				0xE1
#define NRF24L01_FLUSH_RX_MASK				0xE2

#define NRF24L01_REGISTER_MASK				0x1F
#define NRF24L01_WRITE_REGISTER_MASK(reg)	(0x20 | (NRF24L01_REGISTER_MASK & reg)) //Last 5 bits will indicate reg. address


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

void lowerCE(void) {
	HAL_GPIO_WritePin(NRF24L01_CE_PORT, NRF24L01_CE_PIN, GPIO_PIN_RESET);
}

void liftCE(void) {
	HAL_GPIO_WritePin(NRF24L01_CE_PORT, NRF24L01_CE_PIN, GPIO_PIN_SET);
}

void nrfInit(const size_t packetSize, const uint8_t robot_id) {
	TM_NRF24L01_Init((uint8_t)NRF_DEFAULT_RF_CH, (uint8_t)packetSize);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_1M, TM_NRF24L01_OutputPower_0dBm);

	MyAddress[4] = robot_id;

	// my address
	lowerCE();
	NRF24L01_CSN_LOW;
	TM_SPI_Send(NRF24L01_SPI, NRF24L01_WRITE_REGISTER_MASK(NRF24L01_REG_RX_ADDR_P1));
	TM_SPI_WriteMulti(NRF24L01_SPI, MyAddress, 5);
	NRF24L01_CSN_HIGH;
	liftCE();

	// tx address
	NRF24L01_CSN_LOW;
	TM_SPI_Send(NRF24L01_SPI, NRF24L01_WRITE_REGISTER_MASK(NRF24L01_REG_RX_ADDR_P0));
	TM_SPI_WriteMulti(NRF24L01_SPI, TxAddress, 5);
	TM_SPI_Send(NRF24L01_SPI, NRF24L01_WRITE_REGISTER_MASK(NRF24L01_REG_TX_ADDR));
	TM_SPI_WriteMulti(NRF24L01_SPI, TxAddress, 5);
	NRF24L01_CSN_HIGH;


	// power up rx
	/* Disable RX/TX mode */
	lowerCE();
	/* Clear RX buffer */
	flushRX();
	/* Clear interrupts */
	TM_NRF24L01_WriteRegister(0x07, 0x70);
	/* Setup RX mode */
	TM_NRF24L01_WriteRegister(NRF24L01_REG_CONFIG, NRF24L01_CONFIG | 1 << NRF24L01_PWR_UP | 1 << NRF24L01_PRIM_RX);
	/* Start listening */
	lowerCE();
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
		vTaskDelay(1);// Prevent active wait
		//taskYIELD();
	}
	TM_NRF24L01_GetData(dataIn);
}

bool nrfVerifySPI(void) {
	int val = TM_NRF24L01_ReadRegister(NRF_REG_RF_CH);
	if(val == NRF_DEFAULT_RF_CH)
		return true;
	else
		return false;
}
