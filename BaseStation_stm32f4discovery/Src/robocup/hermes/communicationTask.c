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
		int res = nrfSend(packetBytesReceived);

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
