#include "hermes.h"

// This is the file containing everything about communication

static const int BUFFERSIZE = 32; // maximum size for the nrf

void Debug_Print(char * pStr){
	HAL_UART_Transmit(&huart2, (uint8_t*) pStr, strlen(pStr), HAL_MAX_DELAY);

}


// TODO Implement a routine to execute N numbers of UnitTest base on callback (or use a library)
void test_hermes() {
	Result_t res;

	Debug_Print("HERMES - Test encoding and decoding of normal string... ");
	const char testStr[] = "hello world";
	res = test_hermes_try_encode_decode(testStr, strlen(testStr));
	if(res)
		Debug_Print("[OK]\r\n");
	else
		Debug_Print("[FAIL]\r\n");

	Debug_Print("HERMES - Test encoding and decoding of string with escape character... ");
	const char testStrWithZeroChar[] = "hello\0world";
	res = test_hermes_try_encode_decode(testStrWithZeroChar, strlen(testStr));
	if(res)
		Debug_Print("[OK]\r\n");
	else
		Debug_Print("[FAIL]\r\n");

	Debug_Print("HERMES - Test encoding and decoding of empty string");
	res = test_hermes_try_encode_decode('\0', (size_t)0);
	if(res)
		Debug_Print("[OK]\r\n");
	else
		Debug_Print("[FAIL]\r\n");

	Debug_Print("HERMES - Test encoding and decoding of a packet of more than 255 characters");
	char *buffer = (char *)malloc(300);
	memset(buffer, 'a', 300);
	buffer[299] = '\0';
	res = test_hermes_try_encode_decode(buffer, strlen(buffer));
	if(res == FAILURE)
		Debug_Print("[OK]\r\n");
	else
		Debug_Print("[FAIL]\r\n");

	Debug_Print("HERMES - Test decoding invalid packet (too long)");
	const char testStrInvalidPacket[] = "\fhello world too long before a zero char";
	res = test_hermes_invalid_packet(testStrInvalidPacket, sizeof(testStrInvalidPacket));
	if(res == FAILURE)
		Debug_Print("[OK]\r\n");
	else
		Debug_Print("[FAIL]\r\n");

}

Result_t test_hermes_try_encode_decode(const char* pPayload, size_t payload_len){
	char encoded[256];
	char decode[256];
	size_t decode_len;
	Result_t resCod, resDecod;
	resCod = cobifyData(pPayload, payload_len, encoded);
	resDecod = decobifyData(encoded, strlen(encoded), decode, &decode_len);

	if (resCod &&
		resDecod &&
		decode_len == payload_len &&
		memcmp(pPayload, decode, payload_len) == 0) {
		return MySUCCESS;
	} else {
		return FAILURE;
	}
}

Result_t test_hermes_invalid_packet(const char* pInvalid_packet, size_t packet_len){
	char decode[256];
	size_t decode_len;
	return decobifyData(pInvalid_packet, packet_len, decode, &decode_len);
}



/*
 * Validation of the command
void hermer_handleMessage(const unsigned char * msg, size_t msg_len){
	uint8_t id = msg[0];

  // Not implemented command
	if( id >= cmd_table_len || cmd_table[id].callback == nop){
		char err[255];
		sprintf(err, "Invalid command id : %d", id);
		sendError(err);
		sendNack();
		return;
	}
  // Invalid  table entry
	else if(cmd_table[id].id != id){
		char err[255];
		sprintf(err, "Function table wrong id (cmd_table[id].id != id): %d != %d", cmd_table[id].id, id);
		sendError(err);
		sendNack();
		return;
	}
  else if(cmd_table[id].msg_len != msg_len -1){
    char err[255];
    char hex[140];
    convertBytesToStr(msg, msg_len, hex);
    sprintf(err, "Invalid length expect %d receive %d, %s", cmd_table[id].msg_len, msg_len - 1 , hex);
    sendError(err);
    convertBytesToStr(msg, msg_len, err);
    sendError(err);
    sendNack();
    return;
  }

	sendAck();
	cmd_table[id].callback(*this, msg);
}*/

// TODO extract the uart from the this function
size_t readUntilZero(void * pBuffer, size_t length){
	uint8_t *buf = pBuffer;
	if (length < 1) return 0;
	  size_t index = 0;
	  while (index < length) {
	    uint8_t c;
	    HAL_StatusTypeDef res = HAL_UART_Receive(&huart2, &c, 1, 100000);
	    if(res != HAL_OK)
	    	return 0;
	    *buf++ = c;
	    if (c == '\0') break;
	    index++;
	  }
	  return index;
}


// This is the main task, it is intended to run indefinitely
void hermesTask(void * pvParameters) {
	char packetBuffer[COBS_MAX_PACKET_LEN];
	unsigned char dataBuffer[COBS_MAX_PACKET_LEN + 2];
	packetHeaderStruct_t *currentPacketHeaderPtr;
	size_t payloadLen = 0;
	Result_t res;
	while (1) {
		// Get data from device

		size_t bytesReceived = readUntilZero(packetBuffer, COBS_MAX_PACKET_LEN);

		if(bytesReceived == 0){
			Debug_Print("Timeout on receiving\r\n");
			continue;
		}
		if(bytesReceived < sizeof(packetHeaderStruct_t)){
			Debug_Print("Too small packet\r\n");
			continue;
	    }

		// Extract destination address without decoding the packet
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

		Debug_Print("Success!!!\r\n");
		//Debug_Print(dataBuffer);
		// Call callback that handle the packet

	}
}

Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen) {
	size_t sizeOfTheData;

	sizeOfTheData = g_packetsTable[(size_t) currentPacketHeaderPtr->packetType].len;
	if(sizeOfTheData != payloadLen)
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

