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
		[1] = {{0.00047861425656803037, 0.0023389258707335017, -1.6240812273989507}},
		[2] = {{0.0024023513922085526, 0.005243629316001025, -3.2574078130207793}},
		[3] = {{0.0010426855682264845, 0.001081787588980121, -1.721583825401281}}, // Actually robot 7, but it is in robot 3's tactic
		[4] = {{0.0007585814419338309, 0.002133379010571018, -3.2027926974590066}},
		[5] = {{0.0023088016216038015, 0.0034865587736785564, -3.0121339983209503}},
		[6] = {{0.0013232020443287701, 0.0013894326092294825, -1.603319808233}}
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
