#include "kicker.h"
#include "tim.h"

typedef enum  {
	KICKER_IDLE,
	KICKER_CHARGING,
	KICKER_KICKING,
	KICKER_READY_TO_KICK,
	KICKER_WAIT_FOR_BALL
} KickerState_t;


uint8_t g_kickMsTick = 0;

static KickerState_t s_kicker_state = KICKER_IDLE;
static uint8_t s_kicker_time_in_ms = 0;
static TickType_t s_tickWhenWaitingForBall = 0;

void kicker_init(void) {
	s_kicker_state = KICKER_IDLE;
	kicker_chargeOff();
	kicker_kickOff();
}

void kicker_charge(void) {
	if (s_kicker_state == KICKER_IDLE) {
		s_kicker_state = KICKER_CHARGING;
	}
}

void kicker_kick(KickerForce_t time) {
	if (s_kicker_state == KICKER_READY_TO_KICK) {
		s_kicker_time_in_ms = (uint8_t)time;
		s_tickWhenWaitingForBall = xTaskGetTickCount();
		s_kicker_state = KICKER_WAIT_FOR_BALL;
	}
}

void kicker_update(void) {
	switch(s_kicker_state) {
		case KICKER_READY_TO_KICK:
		case KICKER_IDLE:
			kicker_chargeOff();
			break;
		case KICKER_CHARGING:
			kicker_chargeOn();
			if (kicker_isBankFull()) {
				s_kicker_state = KICKER_READY_TO_KICK;
			}
			break;
		case KICKER_KICKING:
			kicker_chargeOff();
			// Wait for the kick to end
			if (g_kickMsTick == 0) {
				s_kicker_state = KICKER_IDLE;
			}
			break;
		case KICKER_WAIT_FOR_BALL:
			if (ball_getState() == BALL_READY_TO_KICK || true) {
				s_kicker_state = KICKER_KICKING;
				kicker_triggerKick();
			} else if (xTaskGetTickCount() - s_tickWhenWaitingForBall > KICKER_WAIT_BALL_TIME_IN_TICK) {
				s_kicker_state = KICKER_IDLE;
			}
	}
}

void kicker_chargeOn(void) {
	HAL_GPIO_WritePin(CHARGE_BANK_GPIO_Port, CHARGE_BANK_Pin, GPIO_PIN_SET);
}

void kicker_chargeOff(void) {
	HAL_GPIO_WritePin(CHARGE_BANK_GPIO_Port, CHARGE_BANK_Pin, GPIO_PIN_RESET);
}

void kicker_triggerKick(void) {
	g_kickMsTick = s_kicker_time_in_ms + KICKER_SAFETY_WAIT_IN_MS;
	__HAL_TIM_ENABLE_IT(&htim7, TIM_IT_UPDATE);
}
void kicker_kickOff(void) {
	HAL_GPIO_WritePin(KICK_GPIO_Port, KICK_Pin, GPIO_PIN_RESET);
}

bool kicker_isBankFull(void) {
	return HAL_GPIO_ReadPin(BANK_FULL_GPIO_Port, BANK_FULL_Pin) == GPIO_PIN_SET;
}
