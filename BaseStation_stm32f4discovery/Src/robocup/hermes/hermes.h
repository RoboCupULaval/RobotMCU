/*
 * hermes.h
 *
 *  Created on: Apr 18, 2017
 *      Author: znuxor
 */

#ifndef ROBOCUP_HERMES_HERMES_H_
#define ROBOCUP_HERMES_HERMES_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>


typedef struct __attribute__((__packed__)) {
	uint8_t protocolVersion;
	uint8_t srcAddress;
	uint8_t destAddress;
	uint8_t packetType;
	uint8_t checksum;
} packetHeaderStruct_t;

enum packetTypes_t {
	PING_REQUEST = 0,
	PING_RESPONSE,
	SPEED_MOVE,
	SET_REGISTER,
	OPEN_LOOP_COMMAND,
	GET_BATTERIE,
	BATTERIE_RESPONSE,
	GET_NUM_REQUEST,
	NUM_REQUEST_RESPONSE,
	SPEED_MOVE_ADVANCE
};

typedef struct {
	uint8_t packetId;
	bool    hasResponse;
	uint8_t nbRetry
} packet_t;

#define DEFAULT_NB_RETRY 3
#define NO_RETRY 1

static const packet_t g_packetsTable[] = {
		{PING_REQUEST,         true,  DEFAULT_NB_RETRY},
		{PING_RESPONSE,        false, DEFAULT_NB_RETRY},
		{SPEED_MOVE,           false, DEFAULT_NB_RETRY},
		{SET_REGISTER,         false, DEFAULT_NB_RETRY},
		{OPEN_LOOP_COMMAND,    false, DEFAULT_NB_RETRY},
		{GET_BATTERIE,         true,  DEFAULT_NB_RETRY},
		{BATTERIE_RESPONSE,    false, DEFAULT_NB_RETRY},
		{GET_NUM_REQUEST,      true,  NO_RETRY},
		{NUM_REQUEST_RESPONSE, false, DEFAULT_NB_RETRY},
		{SPEED_MOVE_ADVANCE,   false, DEFAULT_NB_RETRY}
};

static const size_t g_packetsTableLen = sizeof(g_packetsTable) / sizeof(packet_t);

#endif /* ROBOCUP_HERMES_HERMES_H_ */
