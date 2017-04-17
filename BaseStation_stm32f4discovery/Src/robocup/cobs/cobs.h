/*
 * hermes.h
 *
 *  Created on: 2016-06-21
 *      Author: Philippe Babin
 */

#ifndef HERMES_H_
#define HERMES_H_

#include <stdio.h>
#include <string.h>

#define COBS_MAX_PAYLOAD_LEN 255
// Packet = Offset(1 byte) + Payload + \0(1 byte)
#define COBS_MAX_PACKET_LEN 257

typedef struct __attribute__((__packed__)) {
	uint8_t protocolVersion;
	uint8_t srcAddress;
	uint8_t destAddress;
	uint8_t packetType;
	uint8_t checksum;
} packetHeaderStruct_t;


int cobifyData(const void *ptr, size_t msg_len,   char *dst);
int decobifyData(uint8_t *msg, uint8_t *dstOut, size_t *dst_len);

#endif // HERMES_H_
