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

int cobifyData(uint8_t *data, uint8_t *dstOut, size_t msg_len);
int decobifyData(uint8_t *msg, uint8_t *dstOut, size_t *dst_len);

#endif // HERMES_H_
