/*
 * ball_detector.h
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#ifndef ROBOCUP_BALL_DETECTOR_H_
#define ROBOCUP_BALL_DETECTOR_H_

#include "adc.h"

#define BALL_ADC_THRESHOLD	1200

typedef enum {
	BALL_NOBALL = 0,
	BALL_CENTERED,
	BALL_ON_LEFT,
	BALL_ON_RIGHT
} BallState;

void ball_init(void);
void ball_updateADC(void);
BallState ball_getState(void);

#endif /* ROBOCUP_BALL_DETECTOR_H_ */
