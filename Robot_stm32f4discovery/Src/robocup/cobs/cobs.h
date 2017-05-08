/*
 * hermes.h
 *
 *  Created on: 2016-06-21
 *      Author: Philippe Babin
 */

#ifndef COBS_H_
#define COBS_H_

#include <stdio.h>
#include <string.h>

#define COBS_MAX_PAYLOAD_LEN 255
#define COBS_MAX_PACKET_LEN (COBS_MAX_PAYLOAD_LEN + 2)

int cobifyData(uint8_t *data, uint8_t *dstOut, size_t msg_len);
int decobifyData(uint8_t *msg, uint8_t *dstOut, size_t *dst_len);
//
#endif // COBS_H_
