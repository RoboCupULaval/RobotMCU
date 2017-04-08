
#ifndef CONSOLE_TASK_H_
#define CONSOLE_TASK_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "console.h"
#include "../pmu.h"
#include "../dribbler.h"
#include "../kicker.h"
#include "../ball_detector.h"
#include "../nrfDriver/nrfDriver.h"
#include "../motors/wheel.h"
#include "../motors/wheels_config.h"
#include "../motors/ctrl_task.h"
#include "../motors/wheels_UT.h"


void console_taskEntryPoint(void);

#endif // CONSOLE_TASK_H_
