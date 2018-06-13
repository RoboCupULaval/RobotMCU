#include <stdlib.h>

#include "wheels_UT.h"
#include "wheels_config.h"
#include "cmsis_os.h"


const float   BREAK_SPEED           = 0;
const uint32_t     TIME_LEFT_SPINNING_MS = 100;
const uint32_t     TIME_BREAKING_MS      = 700;

const float   NORMAL_SPEED          = 1.0;
const int16_t MIN_TICK_FOR_MOVEMENT = 250;
bool test_startUp(void) {
	initPwmAndQuad();

	bool success = true;
	LOG_INFO("MOTORS - Each motor should remains immobile \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &g_wheels[i];

		int nbTick = abs(test_spinAndStopWheel(pWheel, BREAK_SPEED));
		// Check absolute value
		bool testCaseSuccess = nbTick < MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, pWheel->debugName, nbTick);
		success &= testCaseSuccess;

	}
  	if(!success)
  		return success;

	LOG_INFO("MOTORS - Each motor turns the right encoder \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &g_wheels[i];

		int nbTick = abs(test_spinAndStopWheel(pWheel, NORMAL_SPEED));
		// Check absolute value
		bool testCaseSuccess = nbTick > MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, pWheel->debugName, nbTick);
		success &= testCaseSuccess;

	}
  	if(!success)
  		return success;

	LOG_INFO("MOTORS - Each wheels turns clockwise \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &g_wheels[i];

		int nbTick = test_spinAndStopWheel(pWheel, NORMAL_SPEED);

		bool testCaseSuccess = nbTick > MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, pWheel->debugName, nbTick);
		success &= testCaseSuccess;
	}
  	if(!success)
  		return success;


	LOG_INFO("MOTORS - Each wheels turns anti-clockwise \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &g_wheels[i];

		int nbTick = test_spinAndStopWheel(pWheel, -NORMAL_SPEED);

		bool testCaseSuccess = nbTick < -MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, pWheel->debugName, nbTick);
		success &= testCaseSuccess;
	}

  	return success;
}

void test_logWheelSpining(bool successful, const char *pWheelDebugName, int nbTick) {
	static char logBuffer[128];
	if (successful) {
		snprintf(logBuffer, 128, "%s nbTick:%d [OK]\r\n", pWheelDebugName, nbTick);
		LOG_INFO(logBuffer);
	} else {
		snprintf(logBuffer, 128, "%s nbTick:%d [FAIL]\r\n", pWheelDebugName, nbTick);
		LOG_ERROR(logBuffer);
	}
}

int32_t test_spinAndStopWheel(Wheel_t* pWheel, float speed) {
  	float wheelSpeed[4];
	// Make it spins a little bit
	wheel_setPWM(pWheel, speed);
	osDelay(TIME_LEFT_SPINNING_MS);

	readQuadsSpeed(&wheelSpeed);

	// Stop it
	wheel_brake(pWheel);
	osDelay(TIME_BREAKING_MS);

	// We check the absolute value first
	return (int32_t)wheelSpeed[pWheel->quad];
}
