/*
 * dribbler.h
 *
 *  Created on: Feb 15, 2017
 *      Author: philippe
 */

#ifndef ROBOCUP_DRIBBLER_H_
#define ROBOCUP_DRIBBLER_H_

#include "ball_detector.h"

void dribbler_init(void);
void dribbler_handleDribbler(void);
void dribbler_startDribbler(const float speed);
void dribbler_setPWM(float speed);


#endif /* ROBOCUP_DRIBBLER_H_ */
