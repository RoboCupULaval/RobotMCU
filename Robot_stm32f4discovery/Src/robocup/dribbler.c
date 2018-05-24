
#include "dribbler.h"
#include "tim.h"
#include "FreeRTOS.h"

#define DRIBBLER_SPIN_TIME_IN_TICK 2000
#define DRIBBLER_SPIN_FORCE_ACTIVATE_IN_TICK 10000

static volatile float s_speed = 0;
static volatile TickType_t s_stopDribblerAt = 0;

void dribbler_init(void) {
  	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 0);
  	s_speed = 0.35f;
  	s_stopDribblerAt = 0;
}

void dibbler_tmp_force_activation(void) {
	s_stopDribblerAt =  xTaskGetTickCount() + DRIBBLER_SPIN_FORCE_ACTIVATE_IN_TICK;
}

void dribbler_setSpeed(const float speed) {
	s_speed = speed;
}

//Speed : PWM = 0 to 1.0
// todo: add check on input
void dribbler_setPWM(float speed) {
	uint32_t pwmTimerValue = (uint32_t)(speed * 6500.0f);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, pwmTimerValue);
}

void dribbler_handleDribbler(void) {
	if (!dribbler_hasChargeTimeout()) {
		dribbler_setPWM(s_speed);
	} else if (ball_getState() >= BALL_READY_TO_DRIBBLE) {
		dribbler_setPWM(s_speed);
		s_stopDribblerAt =  xTaskGetTickCount() + DRIBBLER_SPIN_TIME_IN_TICK;
	} else {
		dribbler_setPWM(0);
	}
}

bool dribbler_hasChargeTimeout(void) {
	return s_stopDribblerAt == 0 || xTaskGetTickCount() > s_stopDribblerAt;
}
