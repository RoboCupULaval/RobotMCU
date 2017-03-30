/*
 * hermes_UT.c
 *
 *  Created on: Jul 2, 2016
 *      Author: philippe
 */

#include "hermes_UT.h"

// TODO Implement a routine to execute N numbers of UnitTest base on callback (or use a library)
void test_hermes() {
	Result_t res;

	LOG_INFO("HERMES - Test encoding and decoding of normal string... ");
	const char testStr[] = "hello world";
	res = test_hermes_try_encode_decode(testStr, strlen(testStr));
	if(res)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");

	LOG_INFO("HERMES - Test encoding and decoding of string with escape character... ");
	const char testStrWithZeroChar[] = "hello\0world";
	res = test_hermes_try_encode_decode(testStrWithZeroChar, strlen(testStr));
	if(res)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");

	LOG_INFO("HERMES - Test encoding and decoding of empty string");
	res = test_hermes_try_encode_decode('\0', (size_t)0);
	if(res)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");

	/*LOG_INFO("HERMES - Test encoding and decoding of a packet of more than 255 characters");
	char buffer[300];
	memset(buffer, 'a', 300);
	buffer[299] = '\0';
	res = test_hermes_try_encode_decode(buffer, strlen(buffer));
	if(res == RESULT_FAILURE)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");
	 */

	LOG_INFO("HERMES - Test decoding invalid packet (too long)");
	const char testStrInvalidPacket[] = "\fhello world too long before a zero char";
	res = test_hermes_invalid_packet(testStrInvalidPacket, sizeof(testStrInvalidPacket));
	if(res == RESULT_FAILURE)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");

	packetHeaderStruct_t header = hermes_createHeader(HeartbeatRequest);
	header.srcAddress = 42; // src address change base on Robot_ID, we set it up for a set value

	LOG_INFO("HERMES - Test validating a packet with a wrong checksum");
	res = validatePayload(&header, sizeof(packetHeaderStruct_t));
	if(res == RESULT_FAILURE)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");

	LOG_INFO("HERMES - Test validating a packet with a valid checksum");
	header.checksum = header.srcAddress - 1; // The expected checksum in our case is always one less then the srcAddress
	res = validatePayload(&header, sizeof(packetHeaderStruct_t));
	if(res == RESULT_SUCCESS)
		LOG_INFO("[OK]\r\n");
	else
		LOG_ERROR("[FAIL]\r\n");

}

Result_t test_hermes_try_encode_decode(const char* pPayload, size_t payload_len){
	char encoded[256];
	char decode[256];
	size_t decode_len;
	Result_t resCod, resDecod;
	resCod = cobifyData(pPayload, payload_len, encoded);
	resDecod = decobifyData(encoded, strlen(encoded), decode, &decode_len);

	if (resCod && resDecod
			&& decode_len == payload_len
			&& memcmp(pPayload, decode, payload_len) == 0) {
		return RESULT_SUCCESS;
	} else {
		return RESULT_FAILURE;
	}
}

Result_t test_hermes_invalid_packet(const char* pInvalid_packet, size_t packet_len){
	char decode[256];
	size_t decode_len;
	return decobifyData(pInvalid_packet, packet_len, decode, &decode_len);
}
