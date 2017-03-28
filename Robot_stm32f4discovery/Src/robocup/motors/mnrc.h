/*
 * mnrc.h
 *
 *  Created on: 2017-03-27
 *      Author: Simon Bouchard
 */

#ifndef APPLICATION_USER_MNRC_H_
#define APPLICATION_USER_MNRC_H_

#include <stdio.h>
#include "../robocup_define.h"

typedef struct {

	// the MNRC parameters
	float Kp;    // proportionnal gain
	float Ki;    // integral gain
	float gamma; // desired closed-loop dynamic

	float K1;
	float K2;
	float[4][4] invM1;
	float[4][4] M2;

	// the MNRC variables
	float w;      // Wheel speed measurements [rad/s]
	float w_m;    // Desired dynamic estimation [rad/s] 
	float w_ref;  // Wheel reference [rad/s]
	float e;      // Error between desired dynamic and measured wheel speed 
	float eI;     // Integration of e

} MNRC_t;

MNRC_t MNRC_init(float Kp, float Ki, float gamma);
float* MNRC_update(MNRC_t *mnrc);

#endif /* APPLICATION_USER_MNRC_H_ */
