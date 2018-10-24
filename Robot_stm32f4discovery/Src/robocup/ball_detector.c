/*
 * ball_detector.c
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#include "util.h"
#include "ball_detector.h"
#include "log.h"

typedef struct {
	unsigned adc_lvl_left;
	unsigned adc_lvl_right;
	unsigned adc_lvl_avg;
} ball_detector_config_t;


ball_detector_config_t ball_getConfig(void);

ball_detector_config_t ID_TO_CONFIG[] = {
		[0] = {.adc_lvl_left = 600, .adc_lvl_right = 600, .adc_lvl_avg = 600},
		[1] = {.adc_lvl_left = 900, .adc_lvl_right = 650, .adc_lvl_avg = 740},
		[6] = {.adc_lvl_left = 1050, .adc_lvl_right = 1000, .adc_lvl_avg = 750}
};
const size_t ID_TO_CONFIG_LEN = sizeof(ID_TO_CONFIG) / sizeof(ball_detector_config_t);

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

ball_detector_config_t ball_getConfig(void) {
	uint8_t id = robot_getPlayerID();
	if (id >= ID_TO_CONFIG_LEN) {
		id = 0;
	}
	return ID_TO_CONFIG[id];
}

BallState ball_getState(void) {
	uint32_t adcValueLeft = ball_getSensorValue(1);
	uint32_t adcValueRight = ball_getSensorValue(2);

	uint32_t mean = (adcValueLeft + adcValueRight) /2;

	ball_detector_config_t config = ball_getConfig();
	if (mean >= config.adc_lvl_avg || adcValueLeft >= config.adc_lvl_left || adcValueRight >= config.adc_lvl_right) {
		return BALL_READY_TO_KICK;
		//LOG_INFO("Ball detector said Kick is ready\r\n");
	} else {
		return BALL_NOBALL;
	}
//	// The best threshold for a kick is the first quadrant of a circle centered at 500,500
//	uint32_t distCenterX = adcValue1 - 500;
//	uint32_t distCenterY = adcValue2 - 500;
//	// If first quadrant of a circle
//	if (distCenterX > 0 && distCenterY > 0 &&
//		(distCenterX * distCenterX + distCenterY * distCenterY) > BALL_KICKING_THRESHOLD) {
//		ballState = BALL_READY_TO_KICK;
//	}
//	else if(adcValue1 >= BALL_DRIBBLING_THRESHOLD || adcValue2 >= BALL_DRIBBLING_THRESHOLD) {
//		ballState = BALL_READY_TO_DRIBBLE;
//	}
	//snprintf(buf, 50, "a%03d b:%03d kicking:%d\r\n", adcValue1, adcValue2, ballState == BALL_READY_TO_KICK);
	//LOG_INFO(buf);
}
