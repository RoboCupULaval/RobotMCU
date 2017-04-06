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
bool robot_isBtnPressed(void) {
	return HAL_GPIO_ReadPin(SWITCH_INPUT_GPIO_Port, SWITCH_INPUT_Pin) == GPIO_PIN_SET;
}

//Return player ID (rotary switch)
//Two robots *can* have the same player ID
uint8_t robot_getPlayerID(void) {
	uint8_t id = 0;

	id |= HAL_GPIO_ReadPin(ID_0_GPIO_Port, ID_0_Pin);
	id |= (uint8_t)(HAL_GPIO_ReadPin(ID_1_GPIO_Port, ID_1_Pin) << 1);
	id |= (uint8_t)(HAL_GPIO_ReadPin(ID_2_GPIO_Port, ID_2_Pin) << 2);

	return id;
}

//Return unique robot ID (uuid of the stm32 board)
//Only *one* board/robot has that ID
uint8_t robot_getUniqueRobotID(void) {
	const uint32_t* STM32_UUID_ADDR = ((uint32_t *)0x1FFF7A10);
	// The stm32 define a three 32bit integer for uuid
	// only the first 32bit integer change between  board
	uint32_t uniqueId = STM32_UUID_ADDR[0];
	switch (uniqueId) {
		case 0x450030:
			return 1;
		case 0x350030:
			return 2;
		case 0x3b0030:
			return 3;
		case 0x1d002f:
			return 4;
		case 0x1e002f:
			return 5;
		case 0x280030:
			return 6;
		default:
			LOG_ERROR("Invalid unique robot id!!! This should never happen!!");
			return 0;
	}
}


