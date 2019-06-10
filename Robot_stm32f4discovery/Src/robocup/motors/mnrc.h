/*
 * mnrc.h
 *
 *  Created on: 2017-03-27
 *      Author: Simon Bouchard
 */

#ifndef MNRC_H_
#define MNRC_H_

#include <stdio.h>
#include <stdbool.h>
#include "../robocup_define.h"

#define ANTI_WINDUP_CIRCULAR_BUFFER_SIZE 100

typedef struct {

	// the MNRC parameters
	float Kp;    // proportionnal gain
	float Ki;    // integral gain
	float Kd;	// derivative gain
	float lambda; // desired closed-loop dynamic

	float K1;
	float K2;

	bool has_anti_windup; // activate anti-windup

	// the MNRC variables
	float w[4];      // Wheel speed measurements [rad/s]
	float w_m[4];    // Desired dynamic estimation [rad/s]
	float w_ref[4];  // Wheel reference [rad/s]
	float e[4];      // Error between desired dynamic and measured wheel speed
	float eD[4];	// Derivative of e
	float eI[4];     // Integration of e
	float anti_windup[4][ANTI_WINDUP_CIRCULAR_BUFFER_SIZE]; // Previous e value in a circular buffer
	size_t head_anti_windup[4]; // current e value in circular buffer of anti windup

	float command[4];

} MNRC_t;

MNRC_t MNRC_init(float Kp, float Ki, float Kd, float gamma);
void MNRC_update(MNRC_t *mnrc);
void MNRC_reset(MNRC_t *mnrc);

#endif /* MNRC_H_ */
