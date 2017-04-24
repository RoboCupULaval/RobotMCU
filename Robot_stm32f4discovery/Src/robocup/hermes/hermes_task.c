#include "hermes_task.h"
#include "../nrfDriver/nrfDriver.h"

// This is the main task, it is intended to run indefinitely
void hermes_task_slave(void) {
	// We have a small stack, this is why they are static
	static char packetBuffer[COBS_MAX_PAYLOAD_LEN];
	static unsigned char dataBuffer[COBS_MAX_PACKET_LEN];
	size_t payloadLen = 0;
	int result_status;
	for(;;) {
		// Get data from device
		size_t bytesReceived = g_hermesHandle.com.readUntilZero(packetBuffer, COBS_MAX_PACKET_LEN);

		// Check if we actually have received a packet
		if(bytesReceived == 0){
			// It's more efficient to wait a few ticks before trying again
			// TODO: REMOVE the wait!
			osDelay(1);
			continue;
		}

		// Check if we actually have received a possibly valid packet, which needs a complete header
		if(bytesReceived < sizeof(packetHeaderStruct_t)+sizeof(uint8_t)){
			LOG_ERROR_AND_BUFFER("The received packet is too small", packetBuffer, bytesReceived);
			continue;
	    }

		// The packet is decoded
		result_status = decobifyData(packetBuffer, bytesReceived, dataBuffer, &payloadLen);
		if (result_status != 0){
			LOG_ERROR_AND_BUFFER("Failed decoding", packetBuffer, bytesReceived);
			continue;
		}

		// The payload is validated
		packetHeaderStruct_t* currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		result_status = hermes_validate_payload(currentPacketHeaderPtr, payloadLen);

		// The packet is not to be executed
		if (result_status != 0) {
			continue;
		}

		// Find the corresponding packet in the packet table
		packet_t packet = g_packetsTable[(size_t) (currentPacketHeaderPtr->packetType)];

		// Call callback that handles the packet if need be.
		if (packet.callback != NULL) {
		    packet.callback(1, dataBuffer + sizeof(packetHeaderStruct_t *));
		}

		// This is use to give back control to other task
		// TODO: REMOVE!
		osDelay(1);
	}
}
