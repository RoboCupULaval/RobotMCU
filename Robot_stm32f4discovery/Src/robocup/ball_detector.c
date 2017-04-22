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

uint32_t ball_getSensorValue(uint32_t sensorId) {
	return HAL_ADCEx_InjectedGetValue(&hadc1, sensorId);
}

uint32_t ball_getSensorsMeanValue(void) {
	return (ball_getSensorValue(1) + ball_getSensorValue(2))/2;
}

BallState ball_getState(void) {
	uint32_t adcValue1 = ball_getSensorValue(1);
	uint32_t adcValue2 = ball_getSensorValue(2);
	uint32_t adcMean = (adcValue1 + adcValue2) / 2;

	BallState ballState = BALL_NOBALL;

	if(adcMean >= BALL_KICKING_THRESHOLD) {
		ballState = BALL_READY_TO_KICK;
	}
	else if(adcValue1 >= BALL_DRIBBLING_THRESHOLD || adcValue2 >= BALL_DRIBBLING_THRESHOLD) {
		ballState = BALL_READY_TO_DRIBBLE;
	}

	return ballState;
}
