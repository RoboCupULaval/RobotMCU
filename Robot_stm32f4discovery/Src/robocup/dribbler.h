/*
 * dribbler.h
 *
 *  Created on: Feb 15, 2017
 *      Author: philippe
 */

#ifndef ROBOCUP_DRIBBLER_H_
#define ROBOCUP_DRIBBLER_H_

#include <stdbool.h>

#include "ball_detector.h"

void dribbler_init(void);
void dribbler_handleDribbler(void);
void dribbler_setPWM(float speed);
void dibbler_tmp_force_activation(float force_speed);
bool dribbler_hasForceActivationTimeout(void);
bool dribbler_hasTimeout(void);


#endif /* ROBOCUP_DRIBBLER_H_ */
