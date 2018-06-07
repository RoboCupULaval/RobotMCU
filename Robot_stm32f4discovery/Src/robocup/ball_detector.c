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
	unsigned nb_led_dribbler;
	unsigned nb_led_kick;
} ball_detector_config_t;

ball_detector_config_t ID_TO_CONFIG[] = {
		[0] = {.nb_led_dribbler = 4, .nb_led_kick = 5}, // default config
		[1] = {.nb_led_dribbler = 4, .nb_led_kick = 6},
		[2] = {.nb_led_dribbler = 5, .nb_led_kick = 6},
		[3] = {.nb_led_dribbler = 4, .nb_led_kick = 5},
		[4] = {.nb_led_dribbler = 6, .nb_led_kick = 7},
		[5] = {.nb_led_dribbler = 5, .nb_led_kick = 7},
		[6] = {.nb_led_dribbler = 4, .nb_led_kick = 6}
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

uint32_t ball_kicker_threshold(void) {
	uint8_t id = robot_getPlayerID();
	if (id >= ID_TO_CONFIG_LEN) {
		id = 0;
	}
	return (ID_TO_CONFIG[id].nb_led_kick     * BALL_LED_STEP + BALL_MIN_ADC_VAL);
}
uint32_t ball_dribbling_threshold(void) {
	uint8_t id = robot_getPlayerID();
	if (id >= ID_TO_CONFIG_LEN) {
		id = 0;
	}
	return (ID_TO_CONFIG[id].nb_led_dribbler * BALL_LED_STEP + BALL_MIN_ADC_VAL);
}

BallState ball_getState(void) {
	uint32_t adcValue1 = ball_getSensorValue(1);
	uint32_t adcValue2 = ball_getSensorValue(2);

	uint32_t mean = (adcValue1 + adcValue2) /2;
	if (mean >= ball_kicker_threshold()) {
		return BALL_READY_TO_KICK;
		//LOG_INFO("Ball detector said Kick is ready\r\n");
	} else if(mean >= ball_dribbling_threshold() || adcValue1 >= ball_kicker_threshold() || adcValue2 >= ball_kicker_threshold()) {
		return BALL_READY_TO_DRIBBLE;
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
