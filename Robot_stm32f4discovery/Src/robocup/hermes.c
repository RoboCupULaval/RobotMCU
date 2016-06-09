
#include "hermes.h"

// This is the file containing everything about communication

static const int BUFFERSIZE = 32; // maximum size for the nrf

typedef struct{
	char protocolVersion;
	char srcAddress;
	char destAddress;
	char packetType;
	char checksum;
}packetHeaderStruct_t;

// This is the main task, it is intended to run indefinitely
void hermesTask(void * pvParameters) {
	int accumulatedBytes = 0; // number of bytes accumulated before 0 reached
	unsigned char packetBuffer[BUFFERSIZE];
	unsigned char dataBuffer[BUFFERSIZE+2];
	packetHeaderStruct_t *currentPacketHeaderPtr;
	int packetIsCorrect = 1;
	size_t payloadLen = 0;
	Result_t res;
	while (1){
		accumulatedBytes = 0;
		// Get data from device


		// The data is treated
		res = decobifyData(packetBuffer, accumulatedBytes, dataBuffer, payloadLen);
		if(res == FAILURE)
			continue;

		// we "extract" the packet header
		// This is done here because we need the size for the checksum.
		currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		res = validPayload(currentPacketHeaderPtr, payloadLen);

		if(res == FAILURE){
			// Send a warning packet to control tower
			continue;
		}


		// Call callback that handle the packet



	}
}

Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen){
    int sizeOfTheData;

    sizeOfTheData = dataSizeArray[currentPacketHeaderPtr->packetType];
    if(sizeOfTheData + sizeof(packetHeaderStruct_t) != payloadLen)
    	return FAILURE;

    //TODO
    // here the checksum is computed,


	return SUCCESS;
}






// This function creates a cobified copy of the Data
// It is the responsibility of the used to have enough space in the cobifiedData array
// (It takes 2 additionnal bytes.)
#define FinishBlock(X) (*code_ptr = (X), code_ptr = dst++, code = 0x01)
Result_t cobifyData(const unsigned char *ptr, size_t msg_len, unsigned char *dst){

	const unsigned char *end = ptr + msg_len;
	unsigned char *code_ptr = dst++;
	unsigned char code = 0x01;

	while (ptr < end){
		if (*ptr == 0)
			FinishBlock(code);
		else{
			*dst++ = *ptr;
			if (++code == 0xFF)
				FinishBlock(code);
		}
		ptr++;
	}

	FinishBlock(code);//*/
	*code_ptr = 0;
	return MySUCCESS;
}

// This function makes a decobified copy of the original Data
Result_t decobifyData(const char *data, size_t len, char *dst, size_t *dst_len)
{
	const unsigned char *ptr = (const unsigned char*)data;
	const unsigned char *end = ptr + len;
	dst_len = 0;
	while (ptr < end){
		int i, code = *ptr++;
		for(i = 1; i < code; i++){
			// If we get to the end too soon, the pack is invalid
			if(ptr >= end)
				return FAILURE;
			*dst++ = *ptr++;
			(*dst_len)++;

		}
		if (code < 0xFF)
			*dst++ = 0;
		(*dst_len)++;
	}
	return MySUCCESS;
}


