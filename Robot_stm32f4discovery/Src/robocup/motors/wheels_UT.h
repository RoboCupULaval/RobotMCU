#ifndef WHEEL_UT_H_
#define WHEEL_UT_H_

#include <stdbool.h>

#include "wheels_task.h"


bool test_startUp(void);
void test_logWheelSpining(bool successful, const char *pWheelDebugName, int16_t nbTick);
int16_t test_spinAndStopWheel(Wheel_t* pWheel, float speed);

#endif /* WHEEL_UT_H_ */
