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

#include "packets_table.h"

#define COBS_MAX_PACKET_LEN 255

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

Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);

Result_t cobifyData(const void *ptr, size_t msg_len,   char *dst);

Result_t decobifyData(const char *ptr, size_t len, void *dst, size_t *dst_len);


#endif // HERMES_TASK_H_
