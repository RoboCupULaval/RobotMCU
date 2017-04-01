#include "mnrc.h"

const float ROBOT_MODEL_INV_M1[4][4] = {
	{  0.00497f   ,  -0.00448f   ,   0.00334f   ,   -0.0041f},
	{ -0.00499f   ,   0.00681f   ,  -0.00484f   ,   0.00441f},
	{  0.00085f   ,  -0.00151f   ,   0.00269f   ,  -0.00143f},
	{ -0.00287f   ,   0.00278f   ,  -0.00311f   ,   0.00416f},
};

const float ROBOT_MODEL_M2[4][4] = {
	{4.5265f,  0.2949f,  1.1064f,  0.3471f},
	{1.0369f,  2.9667f,  0.8380f,  0.1454f},
	{0.1446f,  0.2892f,  2.9959f,  0.2894f},
	{0.7098f,  0.1451f,  0.2896f,  3.3578f}
};

MNRC_t MNRC_init(float Kp, float Ki, float gamma){

	MNRC_t mnrc;
	mnrc.Kp = Kp;
	mnrc.Ki = Ki;
	mnrc.gamma = gamma;

	mnrc.eIMax =  3.14f;
	mnrc.eIMin = -3.14f;

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
