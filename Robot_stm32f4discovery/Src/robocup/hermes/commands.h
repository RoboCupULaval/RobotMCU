/*
 * commands.h
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_COMMANDS_H_
#define ROBOCUP_COMMANDS_H_

#include "stdint.h"
#include <stdlib.h>
#include "packets_definitions.h"

enum registerTypes_t {
	CONTROL_LOOP_STATE = 0,
	KICK_COMMAND = 1,
	CHARGE_KICKER_COMMAND = 2,
	SET_DRIBBLER_SPEED_COMMAND = 3
};


typedef void (*cmd_func_t)(uint8_t origin_id, uint8_t* msg);

typedef struct {
	int        id;
	cmd_func_t callback;
	size_t     len;
} packet_t;

void command_heartbeatRequest(uint8_t origin_id, uint8_t* msg);
void command_movementCommand(uint8_t origin_id, uint8_t* msg);
void command_movementCommandOpen(uint8_t origin_id, uint8_t* msg);
void command_setRegister(uint8_t origin_id, uint8_t* msg);
void command_getBatterie(uint8_t origin_id, uint8_t* msg);
void command_getNumRequest(uint8_t origin_id, uint8_t* msg);

static const packet_t g_packetsTable[] = {
		{PING_REQUEST,        command_heartbeatRequest,    sizeof(msg_no_arg_t)},
		{PING_RESPONSE,       NULL,                        sizeof(msg_no_arg_t)},
		{SPEED_MOVE,          command_movementCommand,     sizeof(msg_set_speed_t)},
		{SET_REGISTER,        command_setRegister,         sizeof(msg_set_register_t)},
		{OPEN_LOOP_COMMAND,   command_movementCommandOpen, sizeof(msg_set_speed_open_t)},
		{GET_BATTERIE,        command_getBatterie,         sizeof(msg_no_arg_t)},
		{BATTERIE_RESPONSE,   NULL,                        sizeof(msg_uint8_t)},
		{GET_NUM_REQUEST,     command_getNumRequest,       sizeof(msg_no_arg_t)},
		{NUM_REQUEST_RESPONSE,NULL,                        sizeof(msg_uint32_t)},
};

static const size_t g_packetsTableLen = sizeof(g_packetsTable) / sizeof(packet_t);

#endif /* ROBOCUP_COMMANDS_H_ */
