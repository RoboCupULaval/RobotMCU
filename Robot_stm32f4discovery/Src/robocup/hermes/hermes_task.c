#include "hermes_task.h"




// This is the main task, it is intended to run indefinitely
void hermesTask(void * pvParameters) {
	// We have a small stack, this is why they are static
	static char packetBuffer[COBS_MAX_PACKET_LEN];
	static unsigned char dataBuffer[COBS_MAX_PACKET_LEN + 2];
	packetHeaderStruct_t *currentPacketHeaderPtr;
	size_t payloadLen = 0;
	Result_t res;
	while (1) {
		// Get data from device

		size_t bytesReceived = g_hermesHandle.com.readUntilZero(packetBuffer, COBS_MAX_PACKET_LEN);

		if(bytesReceived == 0){
			Debug_Print("Timeout on receiving\r\n");
			continue;
		}
		if(bytesReceived < sizeof(packetHeaderStruct_t)){
			Debug_Print("Too small packet\r\n");
			continue;
	    }

		// Extract destination address without decoding the packet and
		// check if our robot is recipient
		// TODO switch the litteral '4' to a more elegant solution
		if(packetBuffer[4] != ADDR_ROBOT && packetBuffer[4] != ADDR_BROADCAST){
			continue;
		}

		// The data is treated
		res = decobifyData(packetBuffer, bytesReceived, dataBuffer, &payloadLen);
		if (res == FAILURE){
			Debug_Print("Fail decoding\r\n");
			continue;
		}

		// we "extract" the packet header
		// This is done here because we need the size for the checksum.
		currentPacketHeaderPtr = (packetHeaderStruct_t *) dataBuffer;
		res = validPayload(currentPacketHeaderPtr, payloadLen);

		if (res == FAILURE) {
			// Send a warning packet to control tower
			Debug_Print("Invalid packet\r\n");
			continue;
		}
		packet_t packet = g_packetsTable[(size_t) currentPacketHeaderPtr->packetType];

		hermes_sendError("Success!!!\r\n");
		// Call callback that handle the packet
		packet.callback(dataBuffer);
	}
}
