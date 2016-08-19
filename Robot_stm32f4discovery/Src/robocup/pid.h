/*
 * pid.h
 *
 *  Created on: 2016-03-25
 *      Author: Alexia
 */

#ifndef APPLICATION_USER_PID_H_
#define APPLICATION_USER_PID_H_

#include <stdio.h>
#include "robocup_define.h"

typedef struct {
	float Ref; // Input: reference set-point
	float Fbk; // Input: feedback
	float Out; // Output: controller output
} PID_TERMINALS;

typedef struct {
	float Kp; // Parameter: proportional loop gain
	float Ki; // Parameter: integral gain
	float Kd; // Parameter: derivative gain (unused)
	float Umax; // Parameter: upper saturation limit
	float Umin; // Parameter: lower saturation limit
} PID_PARAMETERS;

typedef struct {
	float up; // Data: proportional term
	float ui; // Data: integral term
	float ud; // Data: derivative term
	float v1; // Data: pre-saturated controller output
	float w1; // Data: saturation record: [u(n-1) - v(n-1)]
	float e1; // Data: error term storage e(n)
	float e2; // Data: error term storage e(n-1)
} PID_DATA;

//typedef struct {
//		PID_TERMINALS term;
//		PID_PARAMETERS param;
//		PID_DATA data;
//} PID_Handle;

void initializePID(float pKp, float pKi, float pKd, float pUmax, float pUmin);
float pid_Update(PID_Handle *pPid, float pFbk);
void pid_Set(PID_Handle *pPid, float pKp, float pKi, float pKd);
void wheelTask(void * pvParameters);

#endif /* APPLICATION_USER_PID_H_ */
