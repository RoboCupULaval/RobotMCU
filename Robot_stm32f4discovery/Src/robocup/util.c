/*
 * util.c
*/

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

#include "util.h"

// TODO this fix a linking error, please remove when CubeMX fix there shit
const uint8_t  APBPrescTable[] = {0, 0, 0, 0, 1, 2, 3, 4};


//Return 1 when in debug mode (switch), else no
uint8_t robot_isDebug(void) {
	return HAL_GPIO_ReadPin(DEBUG_SWITCH_GPIO_Port, DEBUG_SWITCH_Pin);
}

//Return 1 when btn is pressed
uint8_t robot_isBtnPressed(void) {
	return HAL_GPIO_ReadPin(SWITCH_INPUT_GPIO_Port, SWITCH_INPUT_Pin);
}

//Return robot ID (rotary switch)
uint8_t robot_getID(void) {
	uint8_t id = 0;

	id |= HAL_GPIO_ReadPin(ID_0_GPIO_Port, ID_0_Pin);
	id |= (uint8_t)(HAL_GPIO_ReadPin(ID_1_GPIO_Port, ID_1_Pin) << 1);
	id |= (uint8_t)(HAL_GPIO_ReadPin(ID_2_GPIO_Port, ID_2_Pin) << 2);

	return id;
}


