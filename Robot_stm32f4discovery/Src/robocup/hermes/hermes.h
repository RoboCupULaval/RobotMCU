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
#include "packets_table.h"

#define COBS_MAX_PAYLOAD_LEN 255
// Packet = Offset(1 byte) + Payload + \0(1 byte)
#define COBS_MAX_PACKET_LEN 257

static const uint8_t ADDR_BROADCAST    = 0xFF;
static const uint8_t ADDR_BASE_STATION = 0xFE;

static const uint8_t PROTOCOL_VERSION  = 0x01;

/*******************************************************************************
 * User Interface Function
 *******************************************************************************/


// TODO: More specific failure than just FAILURE, Also ERROR/SUCCESS already defined elsewhere
typedef enum {
	FAILURE = 0,
	MySUCCESS
}Result_t;

typedef struct packetHeaderStruct packetHeaderStruct;

void                 hermes_init(comHandle_t com);
Result_t             validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);
void                 hermes_sendError(char * pStr);
packetHeaderStruct_t hermes_createHeader(uint8_t packetType);
void                 hermes_sendPayloadLessRespond(uint8_t packetType);
void                 hermes_sendRespond(uint8_t packetType, char* pData, size_t dataLen);
Result_t             cobifyData(const void *ptr, size_t msg_len,   char *dst);
Result_t             decobifyData(const char *ptr, size_t len, void *dst, size_t *dst_len);

#endif // HERMES_H_
