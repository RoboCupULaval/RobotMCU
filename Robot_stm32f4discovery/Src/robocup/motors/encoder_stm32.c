#include "encoder_stm32.h"

EncoderHandle_t encoder_init(TIM_HandleTypeDef* pTimer) {
	EncoderHandle_t encoder;
	encoder.pTimer = pTimer;
	encoder.deltaCount = 0;
	encoder.wheelVelocity = 0.0f;
	// Initialize count to the current timer count
	encoder.previousCount = __HAL_TIM_GetCounter(pTimer);

	return encoder;
}

void encoder_readCounters(EncoderHandle_t *pEncoder) {
	/*const */int16_t currentCount = __HAL_TIM_GetCounter(pEncoder->pTimer);
	//int32_t currentCount = 0;
	int16_t deltaCount = currentCount - pEncoder->previousCount;
	/*if (abs(deltaCount) > 63000) {
		LOG_ERROR("Weird value for counter.\r\n");
		pEncoder->deltaCount = 0;
		currentCount = pEncoder->previousCount;
		deltaCount = pEncoder->deltaCount;
	}*/
	pEncoder->deltaCount = deltaCount;
	pEncoder->previousCount = currentCount;
}

