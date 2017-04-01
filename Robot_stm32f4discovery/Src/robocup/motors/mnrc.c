#include "mnrc.h"

const float ROBOT_MODEL_INV_M1[4][4] = {
	{  0.0245f  , -0.0256f  ,  0.0243f  , -0.0252f},
	{ -0.0285f  ,  0.0320f  , -0.0301f  ,  0.0297f},
	{  0.0068f  , -0.0077f  ,  0.0091f  , -0.0077f},
	{ -0.0161f  ,  0.0170f  , -0.0174f  ,  0.0185f},
};

const float ROBOT_MODEL_M2[4][4] = {
	{3.8070f  ,  3.7146f  ,  0.1447f  ,  3.7732f},
	{2.9175f  ,  3.3330f  ,  2.3487f  ,  0.1446f},
	{0.7678f  ,  0.2891f  ,  3.9195f  ,  0.3566f},
	{1.0844f  ,  0.7216f  ,  1.4127f  ,  4.0745f}
};

MNRC_t MNRC_init(float Kp, float Ki, float gamma){

	MNRC_t mnrc;
	mnrc.Kp = Kp;
	mnrc.Ki = Ki;
	mnrc.gamma = gamma;

	mnrc.eIMax =  1.0f;
	mnrc.eIMin = -1.0f;

	int i = 0;
	for (i = 0; i < 4; i++) {
		mnrc.eI[i] = 0;
		mnrc.w_m[i] = 0;
	}

	return mnrc;
}


void MNRC_update(MNRC_t *mnrc){

	float PI_action[4]    = {0.0f, 0.0f, 0.0f, 0.0f};
	float dynamic_diff[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float speed_state[4]  = {0.0f, 0.0f, 0.0f, 0.0f};
	float mnrc_error[4]   = {0.0f, 0.0f, 0.0f, 0.0f};

	// M2 = [M11 M12 M13 M14
	//       M21...]

	for (size_t i = 0; i < 4; ++i) {

		float GT = mnrc->gamma * CONTROL_LOOP_DELTA_T;
		mnrc->w_m[i] = (1 + GT) * mnrc->w_m[i] - GT * mnrc->w_ref[i];

		mnrc->e[i] = mnrc->w_m[i] - mnrc->w[i];
		mnrc->eI[i] = mnrc->eI[i] + mnrc->e[i] * CONTROL_LOOP_DELTA_T;

		// Anti wind-up (Saturation)
		mnrc->eI[i] = (mnrc->eI[i] > mnrc->eIMax) ? mnrc->eIMax : mnrc->eI[i] ;
		mnrc->eI[i] = (mnrc->eIMin > mnrc->eI[i]) ? mnrc->eIMin : mnrc->eI[i] ;

		PI_action[i] = mnrc->Kp * mnrc->e[i] + mnrc->Ki * mnrc->eI[i];

		dynamic_diff[i] = mnrc->gamma * ( mnrc->w[i] - mnrc->w_ref[i] );

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
