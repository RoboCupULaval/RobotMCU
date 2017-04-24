/*
 * packets_table.h
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_PACKETS_TABLE_H_
#define ROBOCUP_PACKETS_TABLE_H_

#include <stdint.h>

#include "commands.h"

typedef struct __attribute__((__packed__)) {
	uint8_t protocolVersion;
	uint8_t srcAddress;
	uint8_t destAddress;
	uint8_t packetType;
	uint8_t checksum;
} packetHeaderStruct_t;

// This defines the ID number for each packet.
enum packetTypes_t {
	PING_REQUEST = 0,
	PING_RESPONSE,
	SPEED_MOVE,
	SET_REGISTER,
	OPEN_LOOP_COMMAND
};

typedef void (*cmd_func_t)(const void *msg);

typedef struct {
	int        id;
	cmd_func_t callback;
	size_t     len;
} packet_t;

static const packet_t g_packetsTable[] = {
		{PING_REQUEST,                   command_heartbeatRequest, sizeof(msg_no_arg_t)},
		{PING_RESPONSE,                  NULL, (size_t)0},
		{SPEED_MOVE,                    command_movementCommand,  sizeof(msg_set_speed_t)},
		{SET_REGISTER,                        command_setRegister,      sizeof(msg_set_register_t)},
		{OPEN_LOOP_COMMAND,				 command_movementCommandOpen, sizeof(msg_set_speed_open_t)}
};

static const size_t g_packetsTableLen = sizeof(g_packetsTable) / sizeof(packet_t);

#endif /* ROBOCUP_PACKETS_TABLE_H_ */
