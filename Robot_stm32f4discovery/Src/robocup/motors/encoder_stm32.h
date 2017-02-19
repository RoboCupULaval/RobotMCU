
#ifndef ROBOCUP_ENCODER_STM32_H_
#define ROBOCUP_ENCODER_STM32_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "tim.h"

typedef struct EncoderHandle_t {
	TIM_HandleTypeDef* pTimer;
	int16_t previousCount;
	int16_t deltaCount;
	float wheelVelocity;
}EncoderHandle_t;


EncoderHandle_t encoder_init(TIM_HandleTypeDef* pTimer);
void            encoder_readCounters(EncoderHandle_t *pEncoder);

#endif /* ROBOCUP_ENCODER_STM32_H_ */
