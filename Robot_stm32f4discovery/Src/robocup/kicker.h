
#ifndef ROBOCUP_KICKER_H_
#define ROBOCUP_KICKER_H_

#include <stdbool.h>

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

#include "ball_detector.h"


extern volatile uint8_t g_kickMsTick;

#define KICKER_ARMED_TIME_IN_TICK 10000    // 15 secondes
#define TIMEOUT_ON_CHARGE_IN_TICK (60 * 1000) // 1 minute


#define	KICKER_FORCE_1   1 //time in tick
#define	KICKER_FORCE_2   2
#define	KICKER_FORCE_3   3
#define	KICKER_FORCE_4   5
#define	KICKER_FORCE_5  10

void kicker_init(void);
void kicker_kick(uint8_t time);
void kicker_charge(void);
void kicker_update(void);

void kicker_chargeOn(void);
void kicker_chargeOff(void);
void kicker_triggerKick(void);
void kicker_kickOff(void);
bool kicker_hasChargeTimeout(void);
bool kicker_isArmed(void);
bool kicker_isBankFull(void);

#endif /* ROBOCUP_KICKER_H_ */
