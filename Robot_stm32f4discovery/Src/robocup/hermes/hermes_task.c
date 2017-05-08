#include "hermes_task.h"
#include "../nrfDriver/nrfDriver.h"
#include "commands.h"
#include "../log.h"
#include "../cobs/cobs.h"

// This is the main task, it is intended to run indefinitely
void hermes_task_slave(void) {
	if (robot_isDebug()) {
		vTaskSuspend(NULL); //No hermes in debug mode
	}

	// We have a small stack, this is why they are static
	static uint8_t packetBuffer[ COBS_MAX_PAYLOAD_LEN ];
	static uint8_t dataBuffer[ COBS_MAX_PACKET_LEN ];
	size_t payloadLen = 0;
	int result_status;
	for(;;) {
		// Get data from device
		size_t bytesReceived = hermes_read(packetBuffer, COBS_MAX_PACKET_LEN);

		// Check if we actually have received a packet
		if (bytesReceived == 0) {
			// It's more efficient to wait a few ticks before trying again
			// TODO: REMOVE the wait! Maybe taskYIELD?
			taskYIELD();
			continue;
		}

		// Check if we actually have received a possibly valid packet, which needs a complete header
		if (bytesReceived < sizeof(uint8_t) + sizeof(packetHeaderStruct_t)) {
			LOG_ERROR_AND_BUFFER("The received packet is too small", packetBuffer, bytesReceived);
		}
		// Check if our robot is recipient, before decoding
		//encodedPacketHeaderStruct_t* encodedHeader = (encodedPacketHeaderStruct_t *) packetBuffer;
		//if (encodedHeader->header.destAddress != robot_getPlayerID() && encodedHeader->header.destAddress != ADDR_BROADCAST) {
		//	LOG_ERROR_AND_BUFFER("Wrong dest", packetBuffer, bytesReceived);
		//	continue;
	    //}

		// The packet is decoded
		result_status = decobifyData(packetBuffer, dataBuffer, &payloadLen);
		if (result_status != 0) {
			LOG_ERROR_AND_BUFFER("Failed decoding", packetBuffer, bytesReceived);
			continue;
		}

		// The payload is validated
		packetHeaderStruct_t* currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		result_status = hermes_validate_payload(currentPacketHeaderPtr, payloadLen);

		// The packet is not to be executed
		if (result_status != 0) {
			LOG_ERROR_AND_BUFFER("packet is invalid", packetBuffer, bytesReceived);
			continue;
		}

		// Find the corresponding packet in the packet table
		packet_t packet = g_packetsTable[(size_t) (currentPacketHeaderPtr->packetType)];

		// Call callback that handles the packet if need be.
		if (packet.callback != NULL) {
		    packet.callback(1, dataBuffer + sizeof(packetHeaderStruct_t));
		}

		// This is use to give back control to other task
		// TODO: REMOVE the wait! Maybe taskYIELD?
		taskYIELD();
	}
}
