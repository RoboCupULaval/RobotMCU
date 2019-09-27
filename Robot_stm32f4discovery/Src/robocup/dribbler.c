
#include "dribbler.h"
#include "tim.h"
#include "FreeRTOS.h"
#include <task.h>

#include "log.h"


#define DEFAULT_SPEED 0.35f
#define DRIBBLER_SPIN_TIME_IN_TICK 2000u
#define DRIBBLER_SPIN_FORCE_ACTIVATE_IN_TICK 2000u

static volatile float s_speed = 0, s_force_speed = 0;
static volatile TickType_t s_time_to_stop = 0;
static volatile TickType_t s_time_to_stop_force_activate = 0;

void dribbler_init(void) {
  	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 0);
  	s_speed = DEFAULT_SPEED;
  	s_force_speed = DEFAULT_SPEED;
  	s_time_to_stop = 0;
  	s_time_to_stop_force_activate = 0;
}

void dibbler_tmp_force_activation(float force_speed) {
	s_time_to_stop_force_activate = xTaskGetTickCount() + DRIBBLER_SPIN_FORCE_ACTIVATE_IN_TICK;
  	s_force_speed = force_speed;
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
	if (!dribbler_hasForceActivationTimeout()) {
		dribbler_setPWM(s_force_speed);
	}
	else if (!dribbler_hasTimeout()) {
		dribbler_setPWM(s_speed);
	}
//	else if (ball_getState() >= BALL_READY_TO_DRIBBLE) {
//		dribbler_setPWM(s_speed);
//		s_time_to_stop = xTaskGetTickCount() + DRIBBLER_SPIN_TIME_IN_TICK;
////		LOG_INFO("It's me ready dribble\r\n");
//	}
	else {
		dribbler_setPWM(0);
	}
}

bool dribbler_hasForceActivationTimeout(void) {
	return s_time_to_stop_force_activate == 0 || xTaskGetTickCount() > s_time_to_stop_force_activate;
}

bool dribbler_hasTimeout(void) {
	return s_time_to_stop == 0 || xTaskGetTickCount() > s_time_to_stop;
}
