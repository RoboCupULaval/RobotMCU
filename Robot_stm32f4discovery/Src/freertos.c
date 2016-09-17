/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId sendMessageTaskHandle;
osThreadId speedTaskHandle;
osThreadId controlLoopHandle;

/* USER CODE BEGIN Variables */
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void sendMessageTaskFunction(void const * argument);
void speedTaskFunction(void const * argument);
void controlLoopTaskFunction(void const * argument);

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of sendMessageTask */
  osThreadDef(sendMessageTask, sendMessageTaskFunction, osPriorityNormal, 0, 128);
  sendMessageTaskHandle = osThreadCreate(osThread(sendMessageTask), NULL);

  /* definition and creation of speedTask */
  osThreadDef(speedTask, speedTaskFunction, osPriorityIdle, 0, 128);
  speedTaskHandle = osThreadCreate(osThread(speedTask), NULL);

  /* definition and creation of controlLoop */
  osThreadDef(controlLoop, controlLoopTaskFunction, osPriorityNormal, 0, 128);
  controlLoopHandle = osThreadCreate(osThread(controlLoop), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* sendMessageTaskFunction function */
void sendMessageTaskFunction(void const * argument)
{
  /* USER CODE BEGIN sendMessageTaskFunction */

	/* Infinite loop */
	for(;;)
	{
		//	osDelay(1900);
		//	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
		//	HAL_UART_Transmit_IT(&huart2,(uint8_t *)"Hello World!",12);
		//	CDC_Transmit_FS(Buf, 18);
		//	//HAL_SPI_Transmit_IT(&hspi2,(uint8_t *)"Hello World!",12);
		//	osDelay(100);
		//	HAL_UART_Transmit_IT(&huart2,(uint8_t *)"\n\r",2);
		//	HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_RESET);
		osDelay(500);
		//	  bool succes = quad_Test(&quadA);
		//	  if (succes==true){
		//	  	   HAL_UART_Transmit_IT(&huart2,(uint8_t *)"Success\r\n",9);
		//	  }else{
		//	  	   HAL_UART_Transmit_IT(&huart2,(uint8_t *)"No\r\n",4);
		//	  }
		////////  quad_ReadCounters(&quadA);
		//	  sprintf(bufferGlobalDebug,"COUNT %x, %x, %i, %i \n\r", quadA.count0, quadA.count1, quadA.count0, quadA.count1);
		//	  HAL_UART_Transmit_IT(&huart2,(uint8_t*)bufferGlobalDebug, strlen(bufferGlobalDebug));
		//
	}
  /* USER CODE END sendMessageTaskFunction */
}

/* speedTaskFunction function */
void speedTaskFunction(void const * argument)
{
  /* USER CODE BEGIN speedTaskFunction */
	/* Infinite loop */
	for(;;)
	{

		//HAL_UART_Transmit_IT(&huart2,(uint8_t *)"cd", 2);
		//test_hermes();
		//hermesTask(NULL);
		osDelay(1000);
	}
  /* USER CODE END speedTaskFunction */
}

/* controlLoopTaskFunction function */
void controlLoopTaskFunction(void const * argument)
{
  /* USER CODE BEGIN controlLoopTaskFunction */
	/* Infinite loop */
	for(;;)
	{
		//	  HAL_SPI_Transmit_IT(&hspi2, a, 1);
		osDelay(100);
	}
  /* USER CODE END controlLoopTaskFunction */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
