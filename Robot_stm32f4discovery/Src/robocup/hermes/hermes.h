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

#include "../robocup_define.h"
#include "../com_interfaces/com_interface.h"
#include "../util.h"
#include "packets_definitions.h"

#define COBS_MAX_PAYLOAD_LEN 255
#define COBS_MAX_PACKET_LEN (COBS_MAX_PAYLOAD_LEN + 2)

static const uint8_t ADDR_BASE_STATION = 0xFE;
static const uint8_t PROTOCOL_VERSION  = 0x01;

void hermes_init(comHandle_t com);
int hermes_validate_payload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);
packetHeaderStruct_t hermes_create_header(uint8_t packetType);
void hermes_send(uint8_t packetType, char* pData, size_t dataLen);

#endif // HERMES_H_
