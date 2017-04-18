/*
 * hermes.h
 *
 *  Created on: Apr 18, 2017
 *      Author: znuxor
 */

#ifndef ROBOCUP_HERMES_HERMES_H_
#define ROBOCUP_HERMES_HERMES_H_

typedef struct __attribute__((__packed__)) {
	uint8_t protocolVersion;
	uint8_t srcAddress;
	uint8_t destAddress;
	uint8_t packetType;
	uint8_t checksum;
} packetHeaderStruct_t;

#endif /* ROBOCUP_HERMES_HERMES_H_ */
