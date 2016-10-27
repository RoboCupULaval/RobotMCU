#include "hermes_task.h"

// This is the main task, it is intended to run indefinitely
void hermesTask(void) {
	// We have a small stack, this is why they are static
	static char packetBuffer[COBS_MAX_PAYLOAD_LEN];
	static unsigned char dataBuffer[COBS_MAX_PACKET_LEN];
	size_t payloadLen = 0;
	Result_t res;
	for(;;) {
		// Get data from device

		size_t bytesReceived = g_hermesHandle.com.readUntilZero(packetBuffer, COBS_MAX_PACKET_LEN);

		if(bytesReceived == 0){
			LOG_INFO("Timeout on receiving\r\n");
			continue;
		}
		if(bytesReceived < sizeof(encodedPacketHeaderStruct_t)){
			LOG_INFO("Too small packet\r\n");
			continue;
	    }

		// Extract destination address without decoding the packet and
		// check if our robot is recipient
		encodedPacketHeaderStruct_t* encodedHeader = (encodedPacketHeaderStruct_t *) packetBuffer;
		if (encodedHeader->header.destAddress != ADDR_ROBOT && encodedHeader->header.destAddress != ADDR_BROADCAST) {
			continue;
		}

		// The packet is decoded
		res = decobifyData(packetBuffer, bytesReceived, dataBuffer, &payloadLen);
		if (res == FAILURE){
			LOG_INFO("Fail decoding\r\n");
			continue;
		}

		// we "extract" the packet header
		// This is done here because we need the size for the checksum.
		packetHeaderStruct_t* currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		res = validPayload(currentPacketHeaderPtr, payloadLen);

		if (res == FAILURE) {
			// Send a warning packet to control tower
			LOG_INFO("Invalid packet\r\n");
			continue;
		}
		packet_t packet = g_packetsTable[(size_t) (currentPacketHeaderPtr->packetType)];

		LOG_INFO("Success!!!\r\n");
		// Call callback that handle the packet
		packet.callback(dataBuffer);
	}
}
