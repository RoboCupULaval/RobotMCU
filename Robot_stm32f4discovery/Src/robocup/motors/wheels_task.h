#ifndef WHEEL_TASK_H_
#define WHEEL_TASK_H_

#include <stdio.h>
#include <math.h>

#include "FreeRTOS.h"
#include "cmsis_os.h"

#include "../util.h"
#include "motor_data_log.h"
#include "encoder_stm32.h"
#include "wheel.h"

typedef enum {
	OPEN_LOOP,
	CLOSE_LOOP_WITH_LOGGING,
	CLOSE_LOOP_WITHOUT_LOGGING
} CtrlLoop_t;

typedef struct {
	float vx, vy, vtheta;
	TickType_t tickSinceLastUpdate;
} SpeedCommand_t;


extern volatile CtrlLoop_t g_ctrlLoopState;
extern volatile SpeedCommand_t g_speedCommand;

// These variables are public for the unit test
extern Wheel_t wheels[];
extern const size_t wheelsLen;

void wheelTask(void);
void initPwmAndQuad(void);
void readQuadsSpeed(int16_t *wheelSpeed);
bool hasSpeedCommandTimeout();

#endif /* WHEEL_TASK_H_ */
