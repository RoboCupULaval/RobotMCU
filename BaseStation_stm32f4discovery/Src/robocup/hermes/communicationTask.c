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

  /* USER CODE BEGIN communicationTask */
  nrfInit();
  /* Infinite loop */
  uint8_t packetBytesReceived[260] = {0};
  uint8_t decobifiedPacketBytes[260] = {0};
  uint8_t packetBytesToSend[260] = {0};
  //int receivedLen;

  uint8_t lastDestAddress = 0xF0;
  //TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {


	  //Read a packet from usb
	  if (SerialRead(packetBytesReceived) >= 0) {
		  // Decobify
		  size_t decobifiedLen = 0;
          int result = decobifyData(packetBytesReceived, decobifiedPacketBytes, &decobifiedLen);

		  // Check if decobification was successful
		  if (result == -1) {
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
		  //uint8_t volatile someStatus = nrfGetStatus();
		  //uint8_t volatile someCount = nrfRetransmitCount();
	  }

	  /* if (nrfReceiveReady()) {
		  //Read a packet from nrf
		  nrfReceive(packetBytesToSend);

		  // Send to Destination through USB if necessary
		  SerialWrite(packetBytesToSend, strlen(packetBytesToSend));
	  }*/

  }
  /* USER CODE END communicationTask */
}
