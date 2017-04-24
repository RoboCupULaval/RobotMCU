#include "hermes.h"

// This is the file containing everything about the packaging/unpackaging of command

// Private functions
packetHeaderStruct_t hermes_create_header(uint8_t packetType);

hermesHandle_t g_hermesHandle;

void hermes_init(comHandle_t com){
	g_hermesHandle.com = com;
}

int hermes_validate_payload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen) {
	// TODO: add destination checking (is it the correct robot?), reorder the checking: checksum first, valid protocol version, valid id, valid length

	uint8_t id = currentPacketHeaderPtr->packetType;
	if(currentPacketHeaderPtr->protocolVersion != PROTOCOL_VERSION){
		LOG_ERROR("Invalid protocol version\r\n");
		return -1;
	}

	if(id >= g_packetsTableLen){
		LOG_ERROR("Invalid command\r\n");
		return -1;
	}

	if(g_packetsTable[id].len != payloadLen){
		LOG_ERROR("Too small payload\r\n");
		return -1;
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
		return -1;
	}

	return 0;
}

packetHeaderStruct_t hermes_create_header(uint8_t packetType){
	packetHeaderStruct_t header;
	header.protocolVersion = PROTOCOL_VERSION;
	header.srcAddress = robot_getID();
	header.destAddress = ADDR_BASE_STATION;
	header.packetType = packetType;
	header.checksum = 0;
	return header;
}

size_t hermes_read(uint8_t* packetBuffer, int maxBytes){
	return g_hermesHandle.com.readUntilZero(packetBuffer, maxBytes);
}

void hermes_send(uint8_t packetType, uint8_t* pData, size_t dataLen){
	size_t packetLen =  sizeof(packetHeaderStruct_t) + dataLen;

	// Initialize temporary buffer
	uint8_t payload[255];
	char packet[257];

	// Initialize the header
	packetHeaderStruct_t* headerPtr = (packetHeaderStruct_t *)payload;
	*headerPtr = hermes_create_header(packetType);

	// Copy data after the header
	if (dataLen > 0) {
	    memcpy(payload + sizeof(packetHeaderStruct_t), pData, dataLen);
	}

	// Package and send the the respond
	cobifyData(&payload, packetLen, packet);
	g_hermesHandle.com.write(packet, strlen(packet) + 1); // The packet must be zero terminated
}
