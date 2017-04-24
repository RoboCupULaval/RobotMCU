/*
 * commands.h
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_COMMANDS_H_
#define ROBOCUP_COMMANDS_H_

#include "stdint.h"

typedef struct __attribute__((__packed__)) {
	uint8_t protocolVersion;
	uint8_t srcAddress;
	uint8_t destAddress;
	uint8_t packetType;
	uint8_t checksum;
} packetHeaderStruct_t;


/**** DEFINITION OF COMMAND MESSAGE STRUCT ****/

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
} msg_no_arg_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	float   vx;
	float   vy;
	float   vtheta;
} msg_set_speed_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	float   cmd1; //pwm to wheel 1 between 0.0 and 1.0
	float   cmd2;
	float   cmd3;
	float	cmd4;
} msg_set_speed_open_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	float   kp;
	float   ki;
	float   kd;
} msg_set_pid_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	uint8_t registe;
	uint8_t value;
} msg_set_register_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	uint8_t value;
} msg_uint8_t;

enum registerTypes_t {
	CONTROL_LOOP_STATE = 0,
	KICK_COMMAND = 1,
	CHARGE_KICKER_COMMAND = 2,
	SET_DRIBBLER_SPEED_COMMAND = 3
};

void command_heartbeatRequest(const void *msg);
void command_movementCommand(const void *msg);
void command_movementCommandOpen(const void *msg);
void command_setRegister(const void *msg);


#endif /* ROBOCUP_COMMANDS_H_ */
