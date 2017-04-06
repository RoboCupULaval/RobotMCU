/*
 * ball_detector.c
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#include "ball_detector.h"

void ball_init(void) {
	HAL_ADCEx_InjectedStart(&hadc1);
}

void ball_updateADC(void) {
	HAL_ADCEx_InjectedStart(&hadc1);
}

BallState ball_getState(void) {
	uint16_t adcValue1 = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1);
	uint16_t adcValue2 = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_2);

	BallState ballState = BALL_NOBALL;

	if(adcValue1 >= BALL_ADC_THRESHOLD || adcValue2 >= BALL_ADC_THRESHOLD) {
		ballState = BALL_CENTERED;
	}

	return ballState;
}
