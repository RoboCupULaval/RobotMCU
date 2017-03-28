
#include "mnrc.h"

MNRC_t MNRC_init(float Kp, float Ki, float gamma){

	MNRC_t mnrc;
	// the parameters
	mnrc.Kp = Kp;
	mnrc.Ki = Ki;
	mnrc.gamma = gamma;

	mnrc.K1 = 1.0f / (1.0f - gamma * CONTROL_LOOP_DELTA_T);
	mnrc.K2 = gamma * CONTROL_LOOP_DELTA_T / (1.0f - gamma * CONTROL_LOOP_DELTA_T);

	return mnrc;
}


float* MNRC_update(MNRC_t *mnrc){

	float command[4] = {0.0f, 0.0f, 0.0f, 0.0f};

	const float M2[4][4] = {
		{4.5265f,  0.2949f,  1.1064f,  0.3471f},
		{1.0369f,  2.9667f,  0.8380f,  0.1454f},
		{0.1446f,  0.2892f,  2.9959f,  0.2894f},
		{0.7098f,  0.1451f,  0.2896f,  3.3578f}
	};

	const float invM1[4][4] = {
		{  0.0019200, -0.000986,  0.000263, -0.000818},
		{ -0.0012300,  0.002390, -0.001100,  0.000539},
		{ -0.0000703, -0.000501,  0.001660, -0.000439},
		{ -0.0004900,  0.000192, -0.000266,  0.001710},
	};

	// M2 = [M11 M12 M13 M14
	//       M21...]

	for (size_t i = 0; i < 4; ++i) {

		mnrc->w_m[i] = mnrc->K1 * mnrc->w_m[i] - mnrc->K2 * mnrc->w_ref[i];
		mnrc->e[i] = mnrc->w_m[i] - mnrc->w_ref[i];
		mnrc->eI[i] = mnrc->eI[i] + mnrc->e[i] * CONTROL_LOOP_DELTA_T;

		PI_action[i] = mnrc->Kp * mnrc->e[i] + mnrc->Ki * mnrc->eI[i];

		dynamic_diff[i] = mnrc->gamma * ( mnrc->w_m[i] - mnrc->w_ref[i] );

		for (size_t j = 0; j < 4; ++j) {
			speed_state[i] += mnrc->M2[i][j] * mnrc->w[j];
		}

		mnrc_error[i] = dynamic_diff[i] + speed_state[i] + PI_action[i];

	}

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			command[i] += mnrc->invM1[i][j] * mnrc_error[j];
		}
	}	

	return command;

}