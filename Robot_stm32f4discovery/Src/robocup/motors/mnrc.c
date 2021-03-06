#include "mnrc.h"

const float ROBOT_MODEL_INV_M1[4][4] = {
	{  0.0019200f, -0.000986f,  0.000263f, -0.000818f},
	{ -0.0012300f,  0.002390f, -0.001100f,  0.000539f},
	{ -0.0000703f, -0.000501f,  0.001660f, -0.000439f},
	{ -0.0004900f,  0.000192f, -0.000266f,  0.001710f},
};

const float ROBOT_MODEL_M2[4][4] = {
	{4.5265f,  0.2949f,  1.1064f,  0.3471f},
	{1.0369f,  2.9667f,  0.8380f,  0.1454f},
	{0.1446f,  0.2892f,  2.9959f,  0.2894f},
	{0.7098f,  0.1451f,  0.2896f,  3.3578f}
};

MNRC_t MNRC_init(float Kp, float Ki, float Kd, float lambda){

	MNRC_t mnrc;
	
	mnrc.Kp = Kp;
	mnrc.Ki = Ki;
	mnrc.Kd = Kd;
	mnrc.lambda = lambda;

	mnrc.K1 = (1.0f + CONTROL_LOOP_DELTA_T * lambda);
	mnrc.K2 = lambda * CONTROL_LOOP_DELTA_T;

	mnrc.has_anti_windup = true;

	int i = 0, j = 0;
	for (i = 0; i < 4; i++) {
		mnrc.eI[i] = 0;
		mnrc.eD[i] = 0;
		mnrc.w_m[i] = 0;
		mnrc.head_anti_windup[i] = 0;
		for (j = 0; j < ANTI_WINDUP_CIRCULAR_BUFFER_SIZE; j++) {
			mnrc.anti_windup[i][j] = 0;
		}
	}

	return mnrc;
}


void MNRC_update(MNRC_t *mnrc){

	float PI_action[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float dynamic_diff[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float speed_state[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float mnrc_error[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float e_last_loop[4] = {0.0f, 0.0f, 0.0f, 0.0f};

	// M2 = [M11 M12 M13 M14
	//       M21...]

	for (size_t i = 0; i < 4; ++i) {

		mnrc->w_m[i] = mnrc->K1 * mnrc->w_m[i] - mnrc->K2 * mnrc->w_ref[i];
		e_last_loop[i] = mnrc->e[i];
		mnrc->e[i] = mnrc->w_m[i] - mnrc->w[i];
		mnrc->eD[i] = (e_last_loop[i] - mnrc->e[i]) / CONTROL_LOOP_DELTA_T;


		if (mnrc->has_anti_windup) {
			mnrc->head_anti_windup[i]++;
			mnrc->head_anti_windup[i] %= ANTI_WINDUP_CIRCULAR_BUFFER_SIZE;

			// But current integrated error at the head of the circular buffer
			mnrc->anti_windup[i][mnrc->head_anti_windup[i]] = mnrc->e[i] * CONTROL_LOOP_DELTA_T;

			// Sum content of the circular buffer
			mnrc->eI[i] = 0;
			size_t j = 0;
			for (j = 0; j < ANTI_WINDUP_CIRCULAR_BUFFER_SIZE; j++) {
				mnrc->eI[i] += mnrc->anti_windup[i][j];
			}

		} else {
			mnrc->eI[i] = mnrc->eI[i] + mnrc->e[i] * CONTROL_LOOP_DELTA_T;
		}


		PI_action[i] = mnrc->Kp * mnrc->e[i] + mnrc->Ki * mnrc->eI[i] + mnrc->Kd * mnrc->eD[i];

		dynamic_diff[i] = mnrc->lambda * ( mnrc->w_m[i] - mnrc->w_ref[i] );

		for (size_t j = 0; j < 4; ++j) {
			speed_state[i] += ROBOT_MODEL_M2[i][j] * mnrc->w[j];
		}

		mnrc_error[i] = dynamic_diff[i] + speed_state[i] + PI_action[i];

	}

	for (size_t i = 0; i < 4; ++i) {
		mnrc->command[i] = 0;
		for (size_t j = 0; j < 4; ++j) {
			mnrc->command[i] += ROBOT_MODEL_INV_M1[i][j] * mnrc_error[j];
		}
	}	

}

void MNRC_reset(MNRC_t *mnrc) {
	int i = 0, j = 0;
	for (i = 0; i < 4; i++) {
		mnrc->eI[i] = 0;
		mnrc->eD[i] = 0;
		mnrc->w_m[i] = 0;
		mnrc->head_anti_windup[i] = 0;
		for (j = 0; j < ANTI_WINDUP_CIRCULAR_BUFFER_SIZE; j++) {
			mnrc->anti_windup[i][j] = 0;
		}
	}
}
