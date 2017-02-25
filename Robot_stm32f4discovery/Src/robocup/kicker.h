
#ifndef ROBOCUP_KICKER_H_
#define ROBOCUP_KICKER_H_

#include <stdbool.h>

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

typedef enum  {
	KICKER_FORCE_1 = 1, //time in tick
	KICKER_FORCE_2 = 2,
	KICKER_FORCE_3 = 3,
	KICKER_FORCE_4 = 4
} KickerForce_t;

void kicker_init(void);
void kicker_kick(KickerForce_t time);
void kicker_charge(void);
void kicker_update(void);

void kicker_chargeOn(void);
void kicker_chargeOff(void);
void kicker_kickOn(void);
void kicker_kickOff(void);
bool kicker_isBankFull(void);

#endif /* ROBOCUP_KICKER_H_ */
