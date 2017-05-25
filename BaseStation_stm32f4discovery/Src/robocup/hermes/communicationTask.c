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
const uint32_t NB_RETRY = 3;

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
		nrfSend(packetBytesReceived);
		// TODO: Remove this from here
		//if (nrfReceiveReady()) {
		if (packet->packetType < g_packetsTableLen && g_packetsTable[packet->packetType].hasResponse) {
			static int k = 0;
			//Read a packet from nrf
			//nrfSetRobotTX(2);

			int retry = NB_RETRY;
			while (retry > 0) {
				const TickType_t startTime = xTaskGetTickCount();

				while (!nrfReceiveReady() && xTaskGetTickCount()-startTime < NB_TICK_FOR_TIMEOUT);

				if (nrfReceiveReady()) {
					nrfReceive(packetBytesRobotsResponse);

					// Send to response through USB
					SerialWrite(packetBytesRobotsResponse, strlen(packetBytesRobotsResponse)+1); // including the zero byte
					if(xTaskGetTickCount()-startTime >= NB_TICK_FOR_TIMEOUT-3) {
						k++;
					}
					break;
				}
				// Timeout
				nrfSend(packetBytesReceived); // Resending
				retry--;
			}
		}
	}
  }
}
