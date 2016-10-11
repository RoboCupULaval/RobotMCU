#include "hermes.h"

// This is the file containing everything about the packaging/unpackaging of command

hermesHandle_t g_hermesHandle;

void hermes_init(comHandle_t com){
	g_hermesHandle.com = com;
}


Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen) {
	uint8_t id = currentPacketHeaderPtr->packetType;
	if(currentPacketHeaderPtr->protocolVersion != PROTOCOL_VERSION){
		LOG_INFO("Invalid protocol\r\n");
		return FAILURE;
	}

	if(id >= g_packetsTableLen || g_packetsTable[id].callback == nop){
		LOG_INFO("Invalid command\r\n");
		return FAILURE;
	}

	if(g_packetsTable[id].len != payloadLen){
		LOG_INFO("Too small packet\r\n");
		return FAILURE;
	}

	//TODO here the checksum is computed,

	return SUCCESS;
}

void hermes_sendError(char * pStr){
	hermes_sendRespond(RobotCrashedNotification, pStr, strlen(pStr));
}


packetHeaderStruct_t hermes_createHeader(uint8_t packetType){
	packetHeaderStruct_t header;
	header.protocolVersion = PROTOCOL_VERSION;
	header.srcAddress = ADDR_ROBOT;
	header.destAddress = ADDR_BASE_STATION;
	header.packetType = packetType;
	header.checksum = 0;
	return header;
}

void hermes_sendPayloadLessRespond(uint8_t packetType){
	packetHeaderStruct_t payload = hermes_createHeader(packetType);
	char buff[sizeof(packetHeaderStruct_t) + 2];
	//char buff2[256]

	//convertBytesToStr(&payload, sizeof(packetHeaderStruct_t), buff2);
	cobifyData(&payload, sizeof(packetHeaderStruct_t), buff);
	g_hermesHandle.com.write(buff, strlen(buff) + 1);// The packet must be zero terminated
}

void hermes_sendRespond(uint8_t packetType, char* pData, size_t dataLen){
	size_t payloadLen =  sizeof(packetHeaderStruct_t) + dataLen;
	size_t packetLen =  payloadLen + 2;

	// Initialize temporary buffer
	uint8_t payload[255];
	char packet[257];

	// Initialize the header
	packetHeaderStruct_t *header = (packetHeaderStruct_t *)payload;
	*header = hermes_createHeader(packetType);

	// Copy data after the header
	memcpy(payload + sizeof(packetHeaderStruct_t), pData, dataLen);

	// Package and send the the respond
	cobifyData(&payload, payloadLen, packet);
	g_hermesHandle.com.write(packet, strlen(packet) + 1); // The packet must be zero terminated
}

#define FinishBlock(X) (*code_ptr = (X), code_ptr = dst++, code = 0x01)
/***
 * This function creates a cobified copy of the Data
 * It is the responsibility of the used to have enough space in the cobifiedData array
 * (It takes 2 additionnal bytes.)
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

// TODO Fix retarted camelCase and snake_case and remove useless parameter
/***
 * This function makes a decobified copy of the original Data
 * ptr     : Pointer to the zero terminate encoded packet
 * len     : Length of the packet (Why? It's zero terminated!?!)
 * dstOut  : Pointer to the decoded payload
 * dst_len : Number of byte in the payload, should alway be payload's len -1
 */
Result_t decobifyData(const char *msg, size_t len, void *dstOut, size_t *dst_len) {
	if(len >= COBS_MAX_PACKET_LEN)
		return FAILURE;
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
	(*dst_len)--;
	return MySUCCESS;
}

