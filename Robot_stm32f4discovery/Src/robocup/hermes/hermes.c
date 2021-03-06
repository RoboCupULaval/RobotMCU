#include "hermes.h"
#include "commands.h"
#include "../util.h"
#include "../cobs/cobs.h"
#include "../robocup_define.h"
// This is the file containing everything about the packaging/unpackaging of command

// Private functions
void hermes_create_header(uint8_t packetType, packetHeaderStruct_t* header);

hermesHandle_t g_hermesHandle;

void hermes_init(comHandle_t com){
	g_hermesHandle.com = com;
}

int hermes_validate_payload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen) {
	// TODO: add destination checking (is it the correct robot?), reorder the checking: checksum first, valid protocol version, valid id, valid length

	const uint8_t id = currentPacketHeaderPtr->packetType;
	if (currentPacketHeaderPtr->protocolVersion != PROTOCOL_VERSION) {
		LOG_ERROR("Invalid protocol version\r\n");
		return -1;
	}

	if (id >= g_packetsTableLen) {
		LOG_ERROR("Invalid command\r\n");
		return -1;
	}

	if (g_packetsTable[id].len != payloadLen-sizeof(packetHeaderStruct_t)){
		LOG_ERROR("Too small payload\r\n");
		return -1;
	}

	if (g_packetsTable[id].callback == NULL) {
		LOG_INFO("This command does not have an implemented callback. Callback == NULL\r\n");
		return -1;
	}
	if (currentPacketHeaderPtr->destAddress != robot_getPlayerID() && currentPacketHeaderPtr->destAddress != ADDR_BASE_STATION) {
		LOG_ERROR("Wrong destination!\r\n");
		return -1;
	}

	// here the checksum is computed,
	uint8_t checksum = 0;
	uint8_t* rawBytePtr = (uint8_t*)currentPacketHeaderPtr;
	const size_t offsetOfChecksum = (uint8_t*)&(currentPacketHeaderPtr->checksum) - rawBytePtr;
	// Add all the content of the packet except the checksum
	for (size_t i = 0; i < payloadLen; ++i) {
		if (i != offsetOfChecksum) {
			checksum += rawBytePtr[i];
		}
	}

	if (checksum != currentPacketHeaderPtr->checksum) {
		LOG_ERROR("Invalid checksum\r\n");
		//return -1;
	}

	return 0;
}

void hermes_create_header(uint8_t packetType, packetHeaderStruct_t* header){
	header->protocolVersion = PROTOCOL_VERSION;
	header->srcAddress = robot_getPlayerID();
	header->destAddress = ADDR_BASE_STATION;
	header->packetType = packetType;
	header->checksum = 0;
}

uint8_t hermes_compute_checksum(uint8_t* payloadBuffer, size_t payloadSize) {
	uint8_t checksum = 0;
	for (size_t i = 0; i < payloadSize; ++i) {
		checksum += payloadBuffer[i];
	}
	return checksum;
}

size_t hermes_read(uint8_t* packetBuffer, int maxBytes){
	return g_hermesHandle.com.readUntilZero(packetBuffer, maxBytes);
}

void hermes_send(uint8_t packetType, uint8_t* pData, size_t dataLen){
	size_t packetLen =  sizeof(packetHeaderStruct_t) + dataLen;

	// Initialize temporary buffer
	uint8_t payload[COBS_MAX_PAYLOAD_LEN];
	char packet[COBS_MAX_PACKET_LEN];

	// Initialize the header
	packetHeaderStruct_t* headerPtr = (packetHeaderStruct_t *)payload;
	hermes_create_header(packetType, headerPtr);

	// Copy data after the header
	if (dataLen > 0) {
	    memcpy(payload + sizeof(packetHeaderStruct_t), pData, dataLen);
	}
	headerPtr->checksum = hermes_compute_checksum(payload, packetLen);

	// Package and send the the respond
	cobifyData(&payload, packet, packetLen);

	g_hermesHandle.com.write(packet, strlen(packet) + 1); // The packet must be zero terminated
}
