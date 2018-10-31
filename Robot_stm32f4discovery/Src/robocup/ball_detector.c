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
	float w[3];
} ball_detector_config_t;


ball_detector_config_t* ball_getConfig(void);

ball_detector_config_t ID_TO_CONFIG[] = {
		// Each weight define a plane:  w0*x + w1*y + w2 = 0
		[0] = {{0.0011031474051232133, 0.0014773524076650336, -1.9204511700337792}},
		[1] = {{0.001189210826883996, 0.003935258921327135, -2.7765883240904325}},
		[2] = {{0.0030485983978196067, 0.004396843408970122, -3.0116618821155265}},
		[3] = {{0.0040166481811887466, 0.0033559144913297275, -3.380442072608057}},
		[4] = {{0.0011031474051232133, 0.0014773524076650336, -1.9204511700337792}},
		[5] = {{0.003186475511974835, 0.005631115176566155, -4.060872735588114}}
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

ball_detector_config_t* ball_getConfig(void) {
	uint8_t id = robot_getPlayerID();
	if (id >= ID_TO_CONFIG_LEN) {
		id = 0;
	}
	return &ID_TO_CONFIG[id];
}

BallState ball_getState(void) {
	float adcValueLeft = (float)ball_getSensorValue(1);
	float adcValueRight = (float)ball_getSensorValue(2);

	ball_detector_config_t* config = ball_getConfig();

	if (adcValueLeft * config->w[0] + adcValueRight * config->w[1] + config->w[2] >= 0.0) {
		return BALL_READY_TO_KICK;
	} else {
		return BALL_NOBALL;
	}
}
