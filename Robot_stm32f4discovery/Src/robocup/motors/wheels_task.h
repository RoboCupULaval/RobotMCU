#ifndef WHEEL_TASK_H_
#define WHEEL_TASK_H_

#include <stdio.h>
#include <math.h>

#include "../util.h"
#include "wheels.h"

typedef enum {
	OPEN_LOOP,
	CLOSE_LOOP
} CtrlLoop_t;


extern CtrlLoop_t g_ctrlLoopState;

void wheelTask(void * pvParameters);

#endif /* WHEEL_TASK_H_ */
