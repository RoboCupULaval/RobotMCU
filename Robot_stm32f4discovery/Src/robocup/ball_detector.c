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
	float w_a[3];
	float w_b[3];
} ball_detector_config_t;


ball_detector_config_t* ball_getConfig(void);

ball_detector_config_t ID_TO_CONFIG[] = {
		// Each weight define a plane:  w0*x + w1*y + w2 = 0
		[0] = {{0.0011031474051232133, 0.0014773524076650336, -1.9204511700337792}, {0.0011031474051232133, 0.0014773524076650336, -1.9204511700337792}},
		[1] = {{0.6219987684566657, 1, -1036.919135431913}, {0.6219987684566657, 1, -1036.919135431913}},
		[2] = {{0.651431636200172, 1, -759.583743294228}, {0.651431636200172, 1, -759.583743294228}},
		[3] = {{0.8146000642262786, 1, -2092.9839388965}, {0.8146000642262786, 1, -2092.9839388965}}, // Actually robot 7, but it is in robot 3's tactic
		[4] = {{1.0966176108427819, 1, -2889.212766588539}, {1.0966176108427819, 1, -2889.212766588539}},
		[5] = {{1.0740060550333093, 1, -980.2164819285152}, {1.0740060550333093, 1, -980.2164819285152}},
		[6] = {{0.22124966030510002, 1, -690.7252221777143}, {0.22124966030510002, 1, -690.7252221777143}},
		[7] = {{-0.21673214791103368, 1, -983.663221668164}, {3.5655081406339626, 1, -5796.75941785768}}
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

	if (adcValueLeft * config->w_a[0] + adcValueRight * config->w_a[1] + config->w_a[2] >= 0.0 ||
		adcValueLeft * config->w_b[0] + adcValueRight * config->w_b[1] + config->w_b[2] >= 0.0) {
		return BALL_READY_TO_KICK;
	} else {
		return BALL_NOBALL;
	}
}
