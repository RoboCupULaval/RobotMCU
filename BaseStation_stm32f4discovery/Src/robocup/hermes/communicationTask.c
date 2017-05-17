/*
 * communicationTask.c
 *
 *  Created on: Apr 19, 2017
 *      Author: znuxor
 */

#include "communicationTask.h"
#include "../../../Src/robocup/nrfDriver/nrfDriver.h"
#include "usbd_cdc_if.h"

#include "../cobs/cobs.h"
#include "../hermes/hermes.h"
#include "../usb/serialUsb.h"
#include "FreeRTOS.h"
#include "stm32f4xx.h"
#include "usb_device.h"

/* communicationTask function */
void communicationTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  nrfInit();
  /* Infinite loop */
  uint8_t packetBytesReceived[260] = {0};
  uint8_t decobifiedPacketBytes[260] = {0};
  uint8_t packetBytesToSend[260];// = {0};
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
		cobifyData(decobifiedPacketBytes, packetBytesToSend, decobifiedLen);

		// Send to Destination through NRF if necessary
		packetHeaderStruct_t* packet = (packetHeaderStruct_t*)decobifiedPacketBytes;

		if (lastDestAddress != packet->destAddress) {
			lastDestAddress = packet->destAddress;
			nrfSetRobotTX(packet->destAddress);
		}
		nrfSend(packetBytesReceived);

		// TODO: Remove this from here
		enum packetTypes_t {
			PING_REQUEST = 0,
			PING_RESPONSE,
			SPEED_MOVE,
			SET_REGISTER,
			OPEN_LOOP_COMMAND
		};
		//if (nrfReceiveReady()) {
		if (packet->packetType == PING_REQUEST) {
			//Read a packet from nrf
			nrfSetRobotTX(2);
			nrfReceive(packetBytesToSend);

			// Send to response through USB, including the zero byte
			SerialWrite(packetBytesToSend, strlen(packetBytesToSend)+1);
		}
	}
  }
}
