/*
 * mnrc.h
 *
 *  Created on: 2017-03-27
 *      Author: Simon Bouchard
 */

#ifndef MNRC_H_
#define MNRC_H_

#include <stdio.h>
#include "../robocup_define.h"

typedef struct {

	// the MNRC parameters
	float Kp;    // proportionnal gain
	float Ki;    // integral gain
	float lambda; // desired closed-loop dynamic

	float K1;
	float K2;

	// the MNRC variables
	float w[4];      // Wheel speed measurements [rad/s]
	float w_m[4];    // Desired dynamic estimation [rad/s]
	float w_ref[4];  // Wheel reference [rad/s]
	float e[4];      // Error between desired dynamic and measured wheel speed
	float eI[4];     // Integration of e

	float command[4];

} MNRC_t;

MNRC_t MNRC_init(float Kp, float Ki, float gamma);
void MNRC_update(MNRC_t *mnrc);
void MNRC_reset(MNRC_t *mnrc);

#endif /* MNRC_H_ */
