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

#include "com_interfaces/com_interface.h"
#include "packets_definitions.h"

static const uint8_t ADDR_BASE_STATION = 0x00;
static const uint8_t PROTOCOL_VERSION  = 0x01;

extern uint32_t g_numReceivedRequest;

void   hermes_init(comHandle_t com);
int    hermes_validate_payload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);
size_t hermes_read(uint8_t* packetBuffer, int maxBytes);
void   hermes_send(uint8_t packetType, uint8_t* pData, size_t dataLen);

#endif // HERMES_H_
