/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "../../../Src/robocup/nrfDriver/nrfDriver.h"
#include "../../../Src/robocup/hermes/hermes.h"
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId communicationTaHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void communicationTask(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of communicationTa */
  osThreadDef(communicationTa, communicationTask, osPriorityNormal, 0, 1024);
  communicationTaHandle = osThreadCreate(osThread(communicationTa), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

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
  unsigned int REMOVETHISVARIABLEITSUSELESS = 0;
  int receivedLen;

//  while (1) {
//	uint8_t dataOut[15] = {0x04, 0x01, 0xfe, 0xff, 0x01, 0x01, 0x00};
//	nrfSend(dataOut);
//  }

  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  if (xTaskGetTickCount() - lastWakeTime > 1000) {
		  USBD_CDC_ReceivePacket(&hUsbDeviceFS);
		  lastWakeTime = xTaskGetTickCount();
		  SerialWrite("hello", strlen("hello"));
	  }

//	    while (1) {
//	  	uint8_t dataOut[15] = {0x04, 0x01, 0xfe, 0xff, 0x01, 0x01, 0x00};
//	  	nrfSend(dataOut);
//	    }

	  //Read a packet from usb
	  if (SerialRead(packetBytesReceived) >= 0) {
		  // Uncobs the packet
		  size_t receivedLen = strlen(packetBytesReceived);
		  if (receivedLen == 0) {
			  continue;
		  }

		  int result = decobifyData(packetBytesReceived, receivedLen +1, decobifiedPacketBytes, &REMOVETHISVARIABLEITSUSELESS);

		  // Check if decobification was successful
		  if (result == -1) {
			  continue;
		  }
		  // Extract useful info

		  // Recob it if necessary
		  cobifyData(decobifiedPacketBytes, receivedLen-1, packetBytesToSend);

		  // Send to Destination through NRF if necessary

		  nrfSend(packetBytesToSend);
	  }
	  /*
	  if (nrfReceiveReady()) {
		  //Read a packet from nrf
		  nrfReceive(packetBytesToSend);

		  /
		  // Uncobs the packet
		  receivedLen = strlen(packetBytesReceived);
		  decobifyData(packetBytesReceived, 260, decobifiedPacketBytes, &REMOVETHISVARIABLEITSUSELESS);

		  // Extract useful info
cobifyData
		  // Recob it if necessary
		  cobifyData(decobifiedPacketBytes, receivedLen-1, packetBytesToSend);


		  // Send to Destination through USB if necessary
		  SerialWrite(packetBytesToSend, strlen(packetBytesToSend));
	  }*/

  }
  /* USER CODE END communicationTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
