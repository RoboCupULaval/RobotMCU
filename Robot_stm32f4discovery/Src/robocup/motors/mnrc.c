#include "mnrc.h"

const float ROBOT_MODEL_INV_M1[4][4] = {
    { 0.002860586158919f,  -0.000165075427834f,  -0.001898888194323f,   0.000474637884336f},
    {-0.000165075427834f,   0.002070894016180f,   0.000810972859772f,  -0.001898888194323f},
    {-0.001898888194323f,   0.000810972859772f,   0.002070894016180f,  -0.000165075427834f},
    { 0.000474637884336f,  -0.001898888194323f,  -0.000165075427834f,   0.002860586158919f}

};


const float ROBOT_MODEL_M2[4][4] = {
   {2.991627738461538f,   2.150416387262941f,   1.063443458976431f,   1.495813869230769f},
   {2.150416387262941f,   2.991627738461538f,   2.201749952774640f,   1.063443458976431f},
   {1.063443458976431f,   2.201749952774640f,   2.991627738461538f,   2.150416387262941f},
   {1.495813869230769f,   1.063443458976431f,   2.150416387262941f,   2.991627738461538f}
};



MNRC_t MNRC_init(float Kp, float Ki, float lambda){

	MNRC_t mnrc;
	
	mnrc.Kp = Kp;
	mnrc.Ki = Ki;
	mnrc.lambda = lambda;

	mnrc.K1 = (1.0f + CONTROL_LOOP_DELTA_T * lambda);
	mnrc.K2 = lambda * CONTROL_LOOP_DELTA_T;

	mnrc.has_anti_windup = true;

	int i = 0, j = 0;
	for (i = 0; i < 4; i++) {
		mnrc.eI[i] = 0;
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

	// M2 = [M11 M12 M13 M14
	//       M21...]

	for (size_t i = 0; i < 4; ++i) {

		mnrc->w_m[i] = mnrc->K1 * mnrc->w_m[i] - mnrc->K2 * mnrc->w_ref[i];
		mnrc->e[i] = mnrc->w_m[i] - mnrc->w[i];

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


		PI_action[i] = mnrc->Kp * mnrc->e[i] + mnrc->Ki * mnrc->eI[i];

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
	int i = 0;
	for (i = 0; i < 4; i++) {
		mnrc->eI[i] = 0;
		mnrc->w_m[i] = 0;
	}
}
