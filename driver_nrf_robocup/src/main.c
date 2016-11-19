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

	uint8_t dataOut[32] = {8,0,7,0,6,0,5,0,0};
    uint8_t dataIn[32] = {0,0,0,0,0,0,0,0,0};
    SystemInit();
	//HAL_Init();
	nrfInit();

    int maVar = dataIn[7];
    uint8_t maVar2;
    uint8_t maVar3;
    while(1) {
    	nrfSend(dataOut);
    	nrfReceive(dataIn);
        maVar2 = nrfRetransmitCount();
        maVar3 = nrfGetStatus();
    }
	for(;;);
}
