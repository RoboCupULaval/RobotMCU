#ifndef WHEEL_TASK_H_
#define WHEEL_TASK_H_

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "../util.h"
#include "wheels.h"

typedef enum {
	OPEN_LOOP,
	CLOSE_LOOP
} CtrlLoop_t;


extern CtrlLoop_t g_ctrlLoopState;

bool test_startUp();
void test_logWheelSpining(bool successful, int16_t nbTick);
int16_t test_spinAndStopWheel(Wheel_t* pWheel, float speed);
void wheelTask();
void readQuadsSpeed(int16_t *wheelSpeed);

#endif /* WHEEL_TASK_H_ */
