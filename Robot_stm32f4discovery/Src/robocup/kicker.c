#include "kicker.h"

typedef enum  {
	KICKER_IDLE,
	KICKER_CHARGING,
	KICKER_KICKING,
	KICKER_READY_TO_KICK
} KickerState_t;

#define KICKING_TIME_IN_TICK 50

static KickerState_t s_kicker_state = KICKER_IDLE;
static TickType_t s_tickWhenStartKicking = 0;

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

void kicker_kick(void) {
	if (s_kicker_state == KICKER_READY_TO_KICK) {
		s_kicker_state = KICKER_KICKING;
	}
}

void kicker_update(void) {
	switch(s_kicker_state) {
		case KICKER_READY_TO_KICK:
		case KICKER_IDLE:
			kicker_chargeOff();
			kicker_kickOff();
			break;
		case KICKER_CHARGING:
			kicker_chargeOn();
			kicker_kickOff();
			if (kicker_isBankFull()) {
				s_kicker_state = KICKER_READY_TO_KICK;
				s_tickWhenStartKicking = xTaskGetTickCount();
			}
			break;
		case KICKER_KICKING:
			kicker_chargeOff();
			kicker_kickOn();
			if (xTaskGetTickCount() - s_tickWhenStartKicking > KICKING_TIME_IN_TICK) {
				s_kicker_state = KICKER_IDLE;
			}
			break;
	}
}

void kicker_chargeOn(void) {
	HAL_GPIO_WritePin(CHARGE_BANK_GPIO_Port, CHARGE_BANK_Pin, GPIO_PIN_SET);
}

void kicker_chargeOff(void) {
	HAL_GPIO_WritePin(CHARGE_BANK_GPIO_Port, CHARGE_BANK_Pin, GPIO_PIN_RESET);
}

void kicker_kickOn(void) {
	HAL_GPIO_WritePin(KICK_GPIO_Port, KICK_Pin, GPIO_PIN_SET);
}

void kicker_kickOff(void) {
	HAL_GPIO_WritePin(KICK_GPIO_Port, KICK_Pin, GPIO_PIN_RESET);
}

bool kicker_isBankFull(void) {
	return HAL_GPIO_ReadPin(BANK_FULL_GPIO_Port, BANK_FULL_Pin) == GPIO_PIN_SET;
}
