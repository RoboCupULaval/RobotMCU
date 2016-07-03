/*
 * hermes.h
 *
 *  Created on: 2016-06-21
 *      Author: Philippe Babin
 */

#ifndef HERMES_TASK_H_
#define HERMES_TASK_H_

#include <stdio.h>
#include <string.h>

#include "../robocup_define.h"
#include "com_interface.h"
#include "../util.h"
#include "packets_table.h"

#define COBS_MAX_PACKET_LEN 255

static const uint8_t ADDR_BROADCAST    = 0xFF;
static const uint8_t ADDR_BASE_STATION = 0x00;
static const uint8_t ADDR_ROBOT        = 0x01; //Make it configurable (switch?)

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

void hermes_init(comHandle_t com);
void hermesTask(void * pvParameters);
Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);
void hermes_sendError(char * pStr);
packetHeaderStruct_t hermes_createHeader(uint8_t packetType);
void hermes_sendPayloadLessRespond(uint8_t packetType);
void hermes_sendRespond(uint8_t packetType, char* pData, size_t dataLen);
Result_t cobifyData(const void *ptr, size_t msg_len,   char *dst);
Result_t decobifyData(const char *ptr, size_t len, void *dst, size_t *dst_len);

#endif // HERMES_TASK_H_
