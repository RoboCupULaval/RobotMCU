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
void pid_update(PidWheel_t *pPid){

	// the errors
	pPid->ePrevious = pPid->e;
	pPid->e = pPid->r - pPid->fbk;

	// the proportional component
	pPid->up = pPid->Kp * pPid->e;

	// the integral component, this is a rectangular approximation
	pPid->ui = pPid->Ki * pPid->e + pPid->ui;
	pPid->ui = (pPid->ui > pPid->uMax) ? pPid->uMax: pPid->ui ; // prevent the explosion of the integral term
	pPid->ui = (pPid->uMin > pPid->ui) ? pPid->uMin: pPid->ui ;

	// the differential component
	pPid->ud = pPid->Kd * (pPid->e - pPid->ePrevious);

	// the naive command
	pPid->u = pPid->up + pPid->ui + pPid->ud;

	// the saturated command
	if (pPid->u >= pPid->uMax) {
		pPid->output = pPid->uMax;
	}
	else if (pPid->u <= pPid->uMin) {
		pPid->output = pPid->uMin;
	}
	else {
		pPid->output = pPid->u;
	}
}

