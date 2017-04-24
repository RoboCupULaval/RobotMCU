/*
 * packets_table.h
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_PACKETS_TABLE_H_
#define ROBOCUP_PACKETS_TABLE_H_

#include <stdint.h>

// This is the protocol packet header
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
	uint8_t registerNumber;
	uint8_t value;
} msg_set_register_t;

typedef struct __attribute__((__packed__)) {
	packetHeaderStruct_t header;
	uint8_t value;
} msg_uint8_t;



// This defines the ID number for each packet.
enum packetTypes_t {
	PING_REQUEST = 0,
	PING_RESPONSE,
	SPEED_MOVE,
	SET_REGISTER,
	OPEN_LOOP_COMMAND
};

#endif /* ROBOCUP_PACKETS_TABLE_H_ */
