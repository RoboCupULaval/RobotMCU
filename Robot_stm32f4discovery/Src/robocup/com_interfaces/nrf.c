#include "nrf.h"
#include "../nrfDriver/nrfDriver.h"

comHandle_t nrf_init(void){
	nrfInit();

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
	LOG_INFO_AND_BUFFER("PACKET RECEIVE GLORY TO CHUTCHUL", pBuffer, 20);
	return strlen(pBuffer);
}
