#include "hermes.h"

// This is the file containing everything about the packaging/unpackaging of command

hermesHandle_t g_hermesHandle;

void hermes_init(comHandle_t com){
	g_hermesHandle.com = com;
}


Result_t validatePayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen) {
	uint8_t id = currentPacketHeaderPtr->packetType;
	if(currentPacketHeaderPtr->protocolVersion != PROTOCOL_VERSION){
		LOG_ERROR("Invalid protocol version\r\n");
		return RESULT_FAILURE;
	}

	if(id >= g_packetsTableLen || g_packetsTable[id].callback == nop){
		LOG_ERROR("Invalid command\r\n");
		return RESULT_FAILURE;
	}

	if(g_packetsTable[id].len != payloadLen){
		LOG_ERROR("Too small payload\r\n");
		return RESULT_FAILURE;
	}

	// here the checksum is computed,
	uint8_t checksum = 0;
	uint8_t* rawByte = (uint8_t*)currentPacketHeaderPtr;
	const size_t offsetOfChecksum = (uint8_t*)&(currentPacketHeaderPtr->checksum) - rawByte;
	// Add all the content of the packet except the checksum
	for(size_t i = 0; i < payloadLen; ++i) {
		if (i != offsetOfChecksum) {
			checksum += rawByte[i];
		}
	}

	if (checksum != currentPacketHeaderPtr->checksum) {
		LOG_ERROR("Invalid checksum\r\n");
		return RESULT_FAILURE;
	}

	return RESULT_SUCCESS;
}

//
void hermes_sendError(char * pStr){
	hermes_sendRespond(RobotCrashedNotification, pStr, strlen(pStr));
}


packetHeaderStruct_t hermes_createHeader(uint8_t packetType){
	packetHeaderStruct_t header;
	header.protocolVersion = PROTOCOL_VERSION;
	header.srcAddress = robot_getID();
	header.destAddress = ADDR_BASE_STATION;
	header.packetType = packetType;
	header.checksum = 0;
	return header;
}

void hermes_sendAcknowledgment(void) {
	hermes_sendPayloadLessRespond(Ack);
}

void hermes_sendPayloadLessRespond(uint8_t packetType){
	packetHeaderStruct_t payload = hermes_createHeader(packetType);
	char buff[sizeof(packetHeaderStruct_t) + 2];

	//convertBytesToStr(&payload, sizeof(packetHeaderStruct_t), buff2);
	cobifyData(&payload, sizeof(packetHeaderStruct_t), buff);
	g_hermesHandle.com.write(buff, strlen(buff) + 1);// The packet must be zero terminated
}

void hermes_sendRespond(uint8_t packetType, char* pData, size_t dataLen){
	size_t payloadLen =  sizeof(packetHeaderStruct_t) + dataLen;

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
