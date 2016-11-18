/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "nrfDriver/tm_stm32_nrf24l01.h"

int main(void)
{

	uint8_t dataOut[32], dataIn[32];
	TM_NRF24L01_Transmit_Status_t transmissionStatus;

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

	HAL_Init();
	TM_NRF24L01_Init(15, 32);
	TM_NRF24L01_SetRF(TM_NRF24L01_DataRate_2M, TM_NRF24L01_OutputPower_M18dBm);
	TM_NRF24L01_SetMyAddress(MyAddress);
	TM_NRF24L01_SetTxAddress(TxAddress);
	TM_NRF24L01_Transmit(dataOut);

	//Finished init
	/* Wait for data to be sent */
				do {
					/* Get transmission status */
					transmissionStatus = TM_NRF24L01_GetTransmissionStatus();
	} while (transmissionStatus == TM_NRF24L01_Transmit_Status_Sending);
	TM_NRF24L01_PowerUpRx();
	while (!TM_NRF24L01_DataReady());
	TM_NRF24L01_GetData(dataIn);
	for(;;);
}
