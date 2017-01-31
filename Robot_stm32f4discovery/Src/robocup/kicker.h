
#ifndef ROBOCUP_KICKER_H_
#define ROBOCUP_KICKER_H_

#include <stdbool.h>

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

void kicker_init(void);
void kicker_kick(void);
void kicker_charge(void);
void kicker_update(void);

void kicker_chargeOn(void);
void kicker_chargeOff(void);
void kicker_kickOn(void);
void kicker_kickOff(void);
bool kicker_isBankFull(void);

#endif /* ROBOCUP_KICKER_H_ */
