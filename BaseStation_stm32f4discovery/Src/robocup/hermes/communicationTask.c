/*
 * communicationTask.c
 *
 *  Created on: Apr 19, 2017
 *      Author: znuxor
 */

#include "communicationTask.h"
#include "hermes.h"

#include "../../../Src/robocup/nrfDriver/nrfDriver.h"
#include "usbd_cdc_if.h"

#include "../cobs/cobs.h"
#include "../hermes/hermes.h"
#include "../usb/serialUsb.h"
#include "FreeRTOS.h"
#include "stm32f4xx.h"
#include "usb_device.h"

const uint32_t NB_TICK_FOR_TIMEOUT = 5;

static int ptr = 0;
#define CIRC_LEN  10
static int circ_buffer[CIRC_LEN] = {-1};

const size_t dist_without_transmition = 3;

void circ_init(void) {
	for (int i = 0; i < CIRC_LEN; ++i) {
		circ_buffer[i] = -1;
	}
}

void circ_push(int add) {
	ptr = (ptr + 1) % CIRC_LEN;
	circ_buffer[ptr] = add;
}

bool circ_is_resend_needed(int add) {
	// Example of the bug:
	// 21112111
	//     ^------- Packer is lost
	// 11231123
    //       ^^---- Packer is lost
	// The same address must be not publish to a robot 3 times.
	for (int i = 0; i < dist_without_transmition; ++i) {
		// This is pointer magic to get the index i element behind
		int prev_add = circ_buffer[(ptr + CIRC_LEN - i) % CIRC_LEN];
		// The address must be different then current address
		if (prev_add == add)
			return false;

	}

	int prev_add = circ_buffer[(ptr + CIRC_LEN - dist_without_transmition) % CIRC_LEN];
	// The address from 3 send ago, must be same
	return prev_add == add;
}

/* communicationTask function */
void communicationTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  nrfInit();
  /* Infinite loop */
  uint8_t packetBytesReceived[260] = {0};
  uint8_t decobifiedPacketBytes[260] = {0};
  uint8_t packetBytesToSend[260] = {0};
  uint8_t packetBytesRobotsResponse[260] = {0};
  //int receivedLen;

  uint8_t lastDestAddress = 0xF0;
  //TickType_t lastWakeTime = xTaskGetTickCount();

  uint32_t packetCounterPerRobot[12] = {0};
  uint32_t packetFailCounterPerRobot[12] = {0};

  circ_init();
  for (;;) {
	//Read a packet from usb
	if (SerialRead(packetBytesReceived) >= 0) {
		// Decobify
		size_t decobifiedLen = 0;
		int result = decobifyData(packetBytesReceived, decobifiedPacketBytes, &decobifiedLen);

		// Check if decobification was successful
		if (result == -1 || decobifiedLen < sizeof(packetHeaderStruct_t)) {
			HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
			continue;
		}
		// Extract useful info

		// Recob it if necessary
		//cobifyData(decobifiedPacketBytes, packetBytesToSend, decobifiedLen);

		// Send to Destination through NRF if necessary
		packetHeaderStruct_t* packet = (packetHeaderStruct_t*)decobifiedPacketBytes;

		if (lastDestAddress != packet->destAddress) {
			lastDestAddress = packet->destAddress;
			nrfSetRobotTX(packet->destAddress);
		}

		bool need_resend = circ_is_resend_needed(packet->destAddress);

		int nb_tries = need_resend ? 2 : 1;
		//int nb_tries = 1;

		int res = 0;
		for (int i = 0; i < nb_tries; ++i) {
			circ_push(packet->destAddress);
			res = nrfSend(packetBytesReceived);
		}

		// Debug stuff check for not bidirectional packet
		if (packet->destAddress <= 6 && !g_packetsTable[packet->packetType].hasResponse) {
			volatile int foo = 0;
			packetCounterPerRobot[packet->destAddress]++;
			packetFailCounterPerRobot[packet->destAddress] += res < 0 ? 1 : 0;
			foo++;
		}

		if (packet->packetType < g_packetsTableLen && g_packetsTable[packet->packetType].hasResponse) {

			int retry = g_packetsTable[packet->packetType].nbRetry;
			while (retry-- > 0) {
				const TickType_t startTime = xTaskGetTickCount();

				while (!nrfReceiveReady() && xTaskGetTickCount()-startTime < NB_TICK_FOR_TIMEOUT);

				if (nrfReceiveReady()) {
					nrfReceive(packetBytesRobotsResponse);

					// Send to response through USB
					SerialWrite(packetBytesRobotsResponse, strlen(packetBytesRobotsResponse)+1); // including the zero byte
					break;
				}
				// Timeout, if there are retry left
				if (retry > 0)
					nrfSend(packetBytesReceived); // Resending
			}
		}
	}
  }
}
