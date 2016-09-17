/*
 * pid.c
 *
 * Author: Alexia, Frederic St-pierre and Anouar Hanafi
 */

#include <math.h>
#include "pid.h"

// This function initializes the PID structure and return it
// Inputs:
//   pKp: The Kp parameter for the PID
//   pKi: The Ki parameter for the PID
//   pKd: The Kd parameter for the PID
//   pUmax: the maximum value for u (saturation)
//   pUmin: the minimum value for u (saturation)
PidWheel_t pid_init(float pKp, float pKi, float pKd, float pUmax, float pUmin){
	PidWheel_t pid;
	// the parameters
	pid.Kp = pKp;
	pid.Ki = pKi;
	pid.Kd = pKd;
	pid.uMax = pUmax;
	pid.uMin = pUmin;

	// the initial values of the PID variables
	pid.r = 0;
	pid.fbk = 0;
	pid.e = 0;
	pid.ePrevious = 0;
	pid.up = 0;
	pid.ui = 0;
	pid.ud = 0;
	pid.u = 0;
	pid.output = 0;

	return pid;
}

// This function computes the PID value and outputs the value to set the wheel with
// Inputs:
//   pWheel: A pointer to the wheel struct
void pid_update(PidWheel_t *pWheel){

	// the errors
	pWheel->ePrevious = pWheel->e;
	pWheel->e = pWheel->r - pWheel->fbk;

	// the proportional component
	pWheel->up = pWheel->Kp * pWheel->e;

	// the integral component, this is a rectangular approximation
	pWheel->ui = pWheel->Ki * pWheel->e + pWheel->ui;
	pWheel->ui = (pWheel->ui > pWheel->uMax) ? pWheel->uMax: pWheel->ui ; // prevent the explosion of the integral term

	// the differential component
	pWheel->ud = pWheel->Kd * (pWheel->e - pWheel->ePrevious);

	// the naive command
	pWheel->u = pWheel->up + pWheel->ui + pWheel->ud;

	// the saturated command
	if (pWheel->u >= pWheel->uMax) {
		pWheel->output = pWheel->uMax;
	}
	else if (pWheel->u <= pWheel->uMin) {
		pWheel->output = pWheel->uMin;
	}
	else {
		pWheel->output = pWheel->u;
	}
}

