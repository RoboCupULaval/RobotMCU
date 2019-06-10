#include "kicker.h"
#include "tim.h"
#include "log.h"

typedef enum  {
	KICKER_IDLE,
	KICKER_CHARGING,
	KICKER_KICKING,
	KICKER_CHARGED,
	KICKER_WAIT_FOR_BALL
} KickerState_t;


volatile uint8_t g_kickMsTick = 0;

static KickerState_t s_kickerState = KICKER_IDLE;
static uint8_t s_kickerTimeInMs = 0;
static TickType_t s_tickWhenWithKickerArmed = 0;
static TickType_t s_tickWhenStartCharging = 0;
static TickType_t s_tickWhenReceivedCharge = 0;
static bool s_forceKick = false;

void kicker_init(void) {
	s_kickerState = KICKER_IDLE;
	kicker_chargeOff();
	kicker_kickOff();
	s_forceKick = false;
}

void kicker_charge(void) {
	s_tickWhenReceivedCharge = xTaskGetTickCount();
}

void kicker_kick(uint8_t time) {
	kicker_charge();

	s_tickWhenWithKickerArmed = xTaskGetTickCount();
	s_kickerTimeInMs = (uint8_t)time;
}

void kicker_force_kick(uint8_t time) {
	kicker_kick(time);
	s_forceKick = true;
}


void kicker_update(void) {
	switch(s_kickerState) {
		case KICKER_IDLE:
			kicker_chargeOff();
			kicker_kickOff();

			//if (!kicker_hasAutoRechargeTimeout()) {
			if (true) {
				s_kickerState = KICKER_CHARGING;
				kicker_resetChargeTimer();
			}
			break;
		case KICKER_CHARGING:
			if (!kicker_hasAutoRechargeTimeout()) {
				kicker_chargeOn();
				kicker_kickOff();
				if (kicker_hasChargeTimeout()) {
					s_kickerState = KICKER_CHARGED;
				}
			} else {
				//s_kickerState = KICKER_IDLE;
			}
			break;
		case KICKER_CHARGED:
			if (kicker_hasAutoRechargeTimeout()) {
				s_kickerState = KICKER_IDLE;
			}
			if (kicker_isArmed()) {
				s_kickerState = KICKER_WAIT_FOR_BALL;
			}
		break;
		case KICKER_WAIT_FOR_BALL:
			if (ball_getState() == BALL_READY_TO_KICK || s_forceKick) {
				kicker_chargeOff();
				s_kickerState = KICKER_KICKING;
				kicker_triggerKick();
				s_forceKick = false;
				//LOG_INFO("Kick triggered \r\n");
				// If the ball is not detected after a while, we give up
			} else if (!kicker_isArmed()) {
				s_kickerState = KICKER_IDLE;
			}
			break;
		case KICKER_KICKING:
			// Wait for the kick pulse to end
			if (g_kickMsTick == 0) {
				s_kickerState = KICKER_IDLE;
				s_tickWhenWithKickerArmed = 0;
			}
			break;
		default:
			LOG_ERROR("Invalid Kick state \r\n");
	}
}

void kicker_chargeOn(void) {
	HAL_GPIO_WritePin(CHARGE_BANK_GPIO_Port, CHARGE_BANK_Pin, GPIO_PIN_SET);
}

void kicker_chargeOff(void) {
	HAL_GPIO_WritePin(CHARGE_BANK_GPIO_Port, CHARGE_BANK_Pin, GPIO_PIN_RESET);
}

void kicker_triggerKick(void) {
	g_kickMsTick = s_kickerTimeInMs;
	__HAL_TIM_ENABLE_IT(&htim7, TIM_IT_UPDATE);
}

void kicker_kickOff(void) {
	HAL_GPIO_WritePin(KICK_GPIO_Port, KICK_Pin, GPIO_PIN_RESET);
}

bool kicker_hasAutoRechargeTimeout(void) {
	return s_tickWhenReceivedCharge == 0 || xTaskGetTickCount() - s_tickWhenReceivedCharge > TIMEOUT_ON_AUTO_RECHARGE_IN_TICK;
}

void kicker_resetChargeTimer(void) {
	s_tickWhenStartCharging = xTaskGetTickCount();
}

bool kicker_hasChargeTimeout(void) {
	return s_tickWhenStartCharging == 0 || xTaskGetTickCount() - s_tickWhenStartCharging > DURATION_CHARGE_IN_TICK;
}

bool kicker_isArmed(void) {
	return s_tickWhenWithKickerArmed != 0 && xTaskGetTickCount() - s_tickWhenWithKickerArmed < KICKER_ARMED_TIME_IN_TICK;
}

bool kicker_isBankFull(void) {
	return HAL_GPIO_ReadPin(BANK_FULL_GPIO_Port, BANK_FULL_Pin) == GPIO_PIN_SET;
}
