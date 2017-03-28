#include <math.h>
#include "mnrc.h"

#define MAX_OUTPUT 1.0
#define MIN_OUTPUT -1.0
#define DELTA_T 0.05

MnrcWheel_t MNRC_init(float Kp, float Ki, float gamma){

	MNRC_t mnrc;
	// the parameters
	mnrc.Kp = Kp;
	mnrc.Ki = Ki;
	mnrc.gamma = gamma;

	mnrc.K1 = 1.0f / (1.0f - mnrc.gamma * mnrc.dt);
	mnrc.K2 = mnrc.gamma * mnrc.dt / (1.0f - mnrc.gamma * mnrc.dt);

	mnrc.uMax = MAX_OUTPUT;
	mnrc.uMin = MIN_OUTPUT;

	return mnrc;
}


void MNRC_update(MNRC_t *pMnrc){

	const float M2[][] = {
		{4.5265f,  0.2949f,  1.1064f,  0.3471f},
		{1.0369f,  2.9667f,  0.8380f,  0.1454f},
		{0.1446f,  0.2892f,  2.9959f,  0.2894f},
		{0.7098f,  0.1451f,  0.2896f,  3.3578f}
	};

	const float invM1[][] = {
		{  0.0019200, -0.000986,  0.000263, -0.000818},
		{ -0.0012300,  0.002390, -0.001100,  0.000539},
		{ -0.0000703, -0.000501,  0.001660, -0.000439},
		{ -0.0004900,  0.000192, -0.000266,  0.001710},
	};

	// M2 = [M11 M12 M13 M14
	//       M21...]

	for (size_t i = 0; i < 4; ++i) {

		w_m[i] = mnrc.K1 * w_m[i] - K2 * w_ref[i];
		err[i] = w_m[i] - w_ref[i];
		errI[i] = errI[i] + err[i]*DELTA_T;

		PI_action[i] = mnrc.Kp * err[i] + mnrc.Ki * errI[i];

		dynamic_diff[i] = mnrc.gamma * ( w_m[i] - w_ref[i] );

		for (size_t j = 0; j < 4; ++j) {
			speed_state[i] += M2[i][j] * w[j];
		}

		steve[i] = dynamic_diff[i] + speed_state[i] + PI_action[i];

	}

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			command[i] += invM1[i][j] * steve[j];
		}
	}	
 	

}