/*
 * ball_detector.h
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#ifndef ROBOCUP_BALL_DETECTOR_H_
#define ROBOCUP_BALL_DETECTOR_H_

#include "adc.h"

#define BALL_DRIBBLING_THRESHOLD	1000
#define BALL_KICKING_THRESHOLD		(1000u * 1000u) // Circle Radius


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
