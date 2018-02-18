/*
 * ball_detector.h
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#ifndef ROBOCUP_BALL_DETECTOR_H_
#define ROBOCUP_BALL_DETECTOR_H_

#include "adc.h"

#define BALL_DRIBBLING_THRESHOLD	800
#define BALL_KICKING_THRESHOLD		(500 * 500) // Circle Radius
// Note PB-2018-01-14:
// G01 400
// G02 1000-500=500, dibler 1000
// G03 1000-500=500 dibbler 800
// G04 *11/17 sur le sensor2, 1000-500=500 de limite

// G06 1550-500= 1050 et 900 pour dribbleur


typedef enum {
	BALL_NOBALL = 0,
	BALL_READY_TO_DRIBBLE,
	BALL_READY_TO_KICK
} BallState;

void ball_init(void);
void ball_updateADC(void);
BallState ball_getState(void);
uint32_t ball_getSensorValue(uint32_t sensorId);
uint32_t ball_getSensorsMeanValue(void);

#endif /* ROBOCUP_BALL_DETECTOR_H_ */
