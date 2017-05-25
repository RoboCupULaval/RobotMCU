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
	NUM_REQUEST_RESPONSE
};

typedef struct {
	uint8_t packet_id;
	bool    hasResponse;
} packet_t;

static const packet_t g_packetsTable[] = {
		{PING_REQUEST,         true},
		{PING_RESPONSE,        false},
		{SPEED_MOVE,           false},
		{SET_REGISTER,         false},
		{OPEN_LOOP_COMMAND,    false},
		{GET_BATTERIE,         true},
		{BATTERIE_RESPONSE,    false},
		{GET_NUM_REQUEST,      true},
		{NUM_REQUEST_RESPONSE, false}
};

static const size_t g_packetsTableLen = sizeof(g_packetsTable) / sizeof(packet_t);

#endif /* ROBOCUP_HERMES_HERMES_H_ */
