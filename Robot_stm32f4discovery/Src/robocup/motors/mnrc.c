#include "mnrc.h"

const float ROBOT_MODEL_INV_M1[4][4] = {
	{  0.00497f   ,  -0.00448f   ,   0.00334f   ,   -0.0041f},
	{ -0.00499f   ,   0.00681f   ,  -0.00484f   ,   0.00441f},
	{  0.00085f   ,  -0.00151f   ,   0.00269f   ,  -0.00143f},
	{ -0.00287f   ,   0.00278f   ,  -0.00311f   ,   0.00416f},
};

const float ROBOT_MODEL_M2[4][4] = {
	{5.3852f , 1.445f  , 1.7472f , 1.486f  },
	{2.0639f , 4.1145f , 1.445f  , 0.93816f},
	{0.7225f , 1.5075f , 3.8738f , 1.445f  },
	{1.445f  , 0.7225f , 1.6605f , 4.1654f }
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
