#include "hermes.h"

// This is the file containing everything about communication

static const int BUFFERSIZE = 32; // maximum size for the nrf

void test_hermes() {
	const char testStr[] = "hello world";
	char encoded[256];
	char decode[256];
	char printBuffer[100];
	size_t decodeLen;
	cobifyData(testStr, strlen(testStr), encoded);
	decobifyData(encoded, strlen(encoded), decode, &decodeLen);
	if (decodeLen == strlen(testStr) && strcmp(testStr, decode) == 0) {
		sprintf(printBuffer, "Success");
	} else {
		sprintf(printBuffer, "Fail len=%d, offset=%d", strlen(decode),
				strcmp(testStr, decode));
	}

	HAL_UART_Transmit_IT(&huart2, (uint8_t*) printBuffer, strlen(printBuffer));

}

// This is the main task, it is intended to run indefinitely
void hermesTask(void * pvParameters) {
	int accumulatedBytes = 0; // number of bytes accumulated before 0 reached
	unsigned char packetBuffer[BUFFERSIZE];
	unsigned char dataBuffer[BUFFERSIZE + 2];
	packetHeaderStruct_t *currentPacketHeaderPtr;
	int packetIsCorrect = 1;
	size_t payloadLen = 0;
	Result_t res;
	while (1) {
		accumulatedBytes = 0;
		// Get data from device

		// The data is treated
		res = decobifyData(packetBuffer, accumulatedBytes, dataBuffer,
				payloadLen);
		if (res == FAILURE)
			continue;

		// we "extract" the packet header
		// This is done here because we need the size for the checksum.
		currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		res = validPayload(currentPacketHeaderPtr, payloadLen);

		if (res == FAILURE) {
			// Send a warning packet to control tower
			continue;
		}

		// Call callback that handle the packet

	}
}

Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr,
		size_t payloadLen) {
	size_t sizeOfTheData;

	sizeOfTheData = dataSizeArray[(size_t) currentPacketHeaderPtr->packetType];
	if (sizeOfTheData + sizeof(packetHeaderStruct_t) != payloadLen)
		return FAILURE;

	//TODO here the checksum is computed,

	return SUCCESS;
}

// This function creates a cobified copy of the Data
// It is the responsibility of the used to have enough space in the cobifiedData array
// (It takes 2 additionnal bytes.)
#define FinishBlock(X) (*code_ptr = (X), code_ptr = dst++, code = 0x01)
/***
 * data    : Pointer to the raw payload
 * msg_len : Length of the payload in bytes
 * dstOut  : Pointer to the encoded packet. It's zero terminated string
 */
Result_t cobifyData(const void *data, size_t msg_len, char *dstOut) {
	const unsigned char *ptr = (const unsigned char *) data;
	unsigned char *dst = (unsigned char *) dstOut;
	const unsigned char *end = (const unsigned char*) (ptr) + msg_len;
	unsigned char *code_ptr = dst++;
	unsigned char code = 0x01;

	while (ptr < end) {
		if (*ptr == 0)
			FinishBlock(code);
		else {
			*dst++ = *ptr;
			if (++code == 0xFF)
				FinishBlock(code);
		}
		ptr++;
	}

	FinishBlock(code);
	*code_ptr = 0;
	return MySUCCESS;
}

// TODO Fix retarted camelCase and hungarian_notation and remove useless parameter
/***
 * This function makes a decobified copy of the original Data
 * ptr     : Pointer to the zero terminate encoded packet
 * len     : Length of the packet (Why? It's zero terminated!?!)
 * dstOut  : Pointer to the decoded payload
 * dst_len : Number of byte in the payload
 */
Result_t decobifyData(const char *msg, size_t len, void *dstOut,
		size_t *dst_len) {
	unsigned char *ptr = (unsigned char*) msg;
	unsigned char *dst = (unsigned char*) dstOut;
	const unsigned char *end = ptr + len;
	*dst_len = 0;
	while (ptr < end) {
		int i, code = *ptr++;
		for (i = 1; i < code; i++) {
			// If we get to the end too soon, the pack is invalid
			if (ptr >= end)
				return FAILURE;
			*dst++ = *ptr++;
			(*dst_len)++;

		}
		// code mark the number of byte until a zero, so a zero is added at is position
		if (code < 0xFF)
			*dst++ = 0;
		(*dst_len)++;
	}
	return MySUCCESS;
}

