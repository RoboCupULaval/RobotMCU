/*
 * ball_detector.c
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#include "ball_detector.h"
#include "log.h"

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


static char buf[50];

BallState ball_getState(void) {
	uint32_t adcValue1 = ball_getSensorValue(1);
	uint32_t adcValue2 = ball_getSensorValue(2);
	//uint32_t adcMean = ball_getSensorsMeanValue();

	BallState ballState = BALL_NOBALL;



	// The best threshold for a kick is the first quadrant of a circle centered at 500,500
	uint32_t distCenterX = adcValue1 - 500;
	uint32_t distCenterY = adcValue2 - 500;
	// If first quadrant of a circle
	if (distCenterX > 0 && distCenterY > 0 &&
		(distCenterX * distCenterX + distCenterY * distCenterY) > BALL_KICKING_THRESHOLD) {
		ballState = BALL_READY_TO_KICK;
	}
	else if(adcValue1 >= BALL_DRIBBLING_THRESHOLD || adcValue2 >= BALL_DRIBBLING_THRESHOLD) {
		ballState = BALL_READY_TO_DRIBBLE;
	}
	//snprintf(buf, 50, "a%03d b:%03d kicking:%d\r\n", adcValue1, adcValue2, ballState == BALL_READY_TO_KICK);
	//LOG_INFO(buf);

	return ballState;
}
