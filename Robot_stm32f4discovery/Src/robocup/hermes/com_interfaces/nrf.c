#include <string.h>

#include "nrf.h"
#include "../../util.h"
#include "../../nrfDriver/nrfDriver.h"

comHandle_t nrf_init(void){

	nrfInit(robot_getPlayerID());

	comHandle_t com;
	com.read = nrf_read;
	com.write = nrf_write;
	com.readUntilZero = nrf_readUntilZero;
	return com;
}


size_t nrf_read(__attribute__ ((unused)) void *pBuffer,
		        __attribute__ ((unused)) size_t expectedLength){
	// no need right now
	return 0;
}

size_t nrf_write(const void *pBuffer, size_t length){
	nrfSend(pBuffer);
	return length;
}

size_t nrf_readUntilZero(void *pBuffer,
		                 __attribute__ ((unused)) size_t maxLength){

	// TODO modify nrfReceive to take maxLength into account
	nrfReceive(pBuffer);
	//LOG_DEBUG_AND_BUFFER("PACKET RECEIVE", pBuffer, 20);
	return strnlen(pBuffer, PACKET_SIZE);
}
