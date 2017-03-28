#ifndef WHEEL_TASK_H_
#define WHEEL_TASK_H_

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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

typedef struct {
	float cmd1, cmd2, cmd3, cmd4; //pwm to wheel i between 0.0 and 1.0
	TickType_t tickSinceLastUpdate;
} SpeedCommandOpen_t;


extern volatile CtrlLoop_t g_ctrlLoopState;
extern volatile SpeedCommand_t g_speedCommand;
extern volatile SpeedCommandOpen_t g_speedCommandOpen;

// These variables are public for the unit test
extern Wheel_t wheels[];
extern const size_t wheelsLen;

void ctrl_taskEntryPoint(void);
void ctrl_emergencyBreak(void);
void initPwmAndQuad(void);
void readQuadsSpeed(float *wheelSpeed);
bool hasSpeedCommandTimeout(void);
bool hasSpeedCommandOpenTimeout(void);

#endif /* WHEEL_TASK_H_ */
