
#ifndef ROBOCUP_SLOW_TASK_H_
#define ROBOCUP_SLOW_TASK_H_

#include "pmu.h"
#include "led.h"
#include "util.h"
#include "kicker.h"
#include "ball_detector.h"

#define 	SLOW_BATT_MAX					16//V
#define		SLOW_TOTAL_NUMBER_OF_LEDS		9
#define		SLOW_WARNING_LED_FLASH			20
#define		SLOW_CRITICAL_LED_FLASH			10
#define		SLOW_ZERO_LED_FLASH				40
#define 	SLOW_HYSTERESIS_ITERATIONS		40

void slow_taskEntryPoint(void);

#endif /* ROBOCUP_SLOW_TASK_H_ */
