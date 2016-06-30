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

#include "usart.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

#include "util.h"
#include "packets_table.h"

#define COBS_MAX_PACKET_LEN 255

static const uint8_t ADDR_BROADCAST    = 0xFF;
static const uint8_t ADDR_BASE_STATION = 0x00;
static const uint8_t ADDR_ROBOT        = 0x01; //Make it configurable (switch?)

/*******************************************************************************
 * User Interface Function
 *******************************************************************************/


// TODO: More specific failure than just FAILURE
typedef enum {
	FAILURE = 0,
	MySUCCESS
}Result_t;

typedef struct packetHeaderStruct packetHeaderStruct;


void test_hermes();
Result_t test_hermes_try_encode_decode(const char* payload, size_t payload_len);
Result_t test_hermes_invalid_packet(const char* pInvalid_packet, size_t packet_len);

void hermesTask(void * pvParameters);
size_t readUntilZero(void * pBuffer, size_t length);
Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);
Result_t cobifyData(const void *ptr, size_t msg_len,   char *dst);
Result_t decobifyData(const char *ptr, size_t len, void *dst, size_t *dst_len);


#endif // HERMES_TASK_H_
