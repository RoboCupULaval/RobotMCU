

#include "exampleTask.h"

// This is an example task for freertos
void exampleTaskBlinkRed(void * pvParameters) {
	while (1)
	  {
	      static int ledval = 0;

	      // toggle LED
	      HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, (ledval) ? GPIO_PIN_SET: GPIO_PIN_RESET);
	      ledval = 1 - ledval;
	      vTaskDelay(200);
	  }

}

void exampleTaskBlinkBlue(void * pvParameters) {
	while (1)
	  {
	      static int ledval = 0;

	      // toggle LED
	      HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, (ledval) ? GPIO_PIN_SET: GPIO_PIN_RESET);
	      ledval = 1 - ledval;
	      vTaskDelay(100);
	  }

}

