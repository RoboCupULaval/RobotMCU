#include "hermes_task.h"
#include "../nrfDriver/nrfDriver.h"

// This is the main task, it is intended to run indefinitely
void hermes_taskEntryPoint(void) {
	// We have a small stack, this is why they are static
	static char packetBuffer[COBS_MAX_PAYLOAD_LEN];
	static unsigned char dataBuffer[COBS_MAX_PACKET_LEN];
	size_t payloadLen = 0;
	Result_t res;
	for(;;) {
		// Get data from device

		size_t bytesReceived = g_hermesHandle.com.readUntilZero(packetBuffer, COBS_MAX_PACKET_LEN);

		if(bytesReceived == 0){
			//LOG_INFO("Timeout on receiving\r\n");
			// It's more efficient to wait a few ticks before trying again
			osDelay(1);
			continue;
		}
		if(bytesReceived < sizeof(encodedPacketHeaderStruct_t)){
			LOG_ERROR_AND_BUFFER("Too small packet", packetBuffer, bytesReceived);
			continue;
	    }

		// Check if our robot is recipient, before decoding
		encodedPacketHeaderStruct_t* encodedHeader = (encodedPacketHeaderStruct_t *) packetBuffer;
		if (encodedHeader->header.destAddress != robot_getID() && encodedHeader->header.destAddress != ADDR_BROADCAST) {
			LOG_ERROR_AND_BUFFER("Wrong dest", packetBuffer, bytesReceived);
			continue;
		}

		// The packet is decoded
		res = decobifyData(packetBuffer, bytesReceived, dataBuffer, &payloadLen);
		if (res == RESULT_FAILURE){
			//LOG_ERROR("Fail decoding\r\n");
			LOG_ERROR_AND_BUFFER("Fail decoding", packetBuffer, bytesReceived);
			continue;
		}

		packetHeaderStruct_t* currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		res = validate_payload(currentPacketHeaderPtr, payloadLen);

		if (res == RESULT_FAILURE) {
			continue;
		}

		// Find the corresponding packet in the packet table
		packet_t packet = g_packetsTable[(size_t) (currentPacketHeaderPtr->packetType)];

		LOG_INFO("Success!!!\r\n");
		// Call callback that handle the packet
		packet.callback(dataBuffer);

		// This is use to give back control to other task
		osDelay(1);
	}
}
