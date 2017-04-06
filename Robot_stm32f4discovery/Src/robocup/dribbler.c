#include "dribbler.h"
#include "tim.h"
#include "FreeRTOS.h"

#define DRIBBLER_SPIN_TIME_IN_TICK 10000

static volatile float s_speed = 0;
static volatile TickType_t s_timeSinceLastDribbler = 0;

void dribbler_init(void) {
  	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 0);
  	s_speed = 0;
  	s_timeSinceLastDribbler = 0;
}

void dribbler_setSpeed(const float speed) {
	s_speed = speed;
}


void dribbler_startDribbler(const float speed) {
	dribbler_setSpeed(speed);
	s_timeSinceLastDribbler = (TickType_t) xTaskGetTickCount();
}

//Speed : PWM = 0 to 1.0
// todo: add check on input
void dribbler_setPWM(float speed) {
	uint32_t pwmTimerValue = (uint32_t)(speed * 6500.0f);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, pwmTimerValue);
}


void dribbler_handleDribbler(void) {
	if(ball_getState() == BALL_CENTERED) {
		dribbler_setPWM(0.5f);
	} else {
		if (xTaskGetTickCount() - s_timeSinceLastDribbler > DRIBBLER_SPIN_TIME_IN_TICK) {
			s_speed = 0;
		}
		dribbler_setPWM(s_speed);
	}
}
