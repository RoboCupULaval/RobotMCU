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
	float   vz;
} msg_set_speed_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	float   kp;
	float   ki;
	float   kd;
} msg_set_pid_t;



typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	uint8_t value;
} msg_uint8_t;



void nop(const void *msg);
void command_heartbeatRequest(const void *msg);


#endif /* ROBOCUP_COMMANDS_H_ */
