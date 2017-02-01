/*
 * pid.h
 *
 *  Created on: 2016-03-25
 *      Author: Alexia
 */

#ifndef APPLICATION_USER_PID_H_
#define APPLICATION_USER_PID_H_

#include <stdio.h>
#include "tim.h"
#include "../robocup_define.h"

typedef struct {
	// the PID parameters
	float Kp; // the kp parameter
	float Ki; // the ki parameter
	float Kd; // the kd parameter
	float uMax; // the maximal u value for the wheel
	float uMin; // the minimal u value for the wheel

	// the PID variables
	float r; // the command from "the user"
	float fbk; // the feedback value that was measured and set
	float e; // the computed error
	float ePrevious; // the previous computed error for the derivator
	float up; // the proportional term
	float ui; // the integration term, also serves as the accumulator
	float ud; // the differential term
	float u;  // the command before Saturation
	float output; // the command after saturation, this is what we want to send to the wheel

} PidWheel_t;

PidWheel_t pid_init(float pKp, float pKi, float pKd, float pUmax, float pUmin);
void       pid_update(PidWheel_t *pWheel);

#endif /* APPLICATION_USER_PID_H_ */
