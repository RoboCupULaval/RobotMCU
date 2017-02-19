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
#include "nrfDriver/nrfDriver.h"

uint8_t dataOut[32], dataIn[32];
int main(void)
{

	uint8_t dataOut[15] = {0, 1, 2, 3, 4, 42, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    uint8_t dataIn[15] = {0};
    SystemInit();
	HAL_Init();
	nrfInit();
    while(1) {
    	//nrfReceive(dataIn);
    	nrfSend(dataOut);
    	//for(int i=0; i<10000; i++);

    }
}
