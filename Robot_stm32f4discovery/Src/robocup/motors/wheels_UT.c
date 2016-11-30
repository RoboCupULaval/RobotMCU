#include "wheels_UT.h"
#include "wheels_config.h"
#include "cmsis_os.h"


const float   BREAK_SPEED           = 0;
const int     TIME_LEFT_SPINNING_MS = 100;
const int     TIME_BREAKING_MS      = 700;

#if defined (BETA)
const float   NORMAL_SPEED          = 1.5;
const int16_t MIN_TICK_FOR_MOVEMENT = 800;
#elif defined (GAMMA)
const float   NORMAL_SPEED          = 1.0;
const int16_t MIN_TICK_FOR_MOVEMENT = 800;
#endif
bool test_startUp(void) {
	initPwmAndQuad();

	bool success = true;
	LOG_INFO("MOTORS - Each motor should remains immobile \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &g_wheels[i];

		int16_t nbTick = abs(test_spinAndStopWheel(pWheel, BREAK_SPEED));
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

		int16_t nbTick = abs(test_spinAndStopWheel(pWheel, NORMAL_SPEED));
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

		int16_t nbTick = test_spinAndStopWheel(pWheel, NORMAL_SPEED);

		bool testCaseSuccess = nbTick > MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, pWheel->debugName, nbTick);
		success &= testCaseSuccess;
	}
  	if(!success)
  		return success;


	LOG_INFO("MOTORS - Each wheels turns anti-clockwise \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &g_wheels[i];

		int16_t nbTick = test_spinAndStopWheel(pWheel, -NORMAL_SPEED);

		bool testCaseSuccess = nbTick < -MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, pWheel->debugName, nbTick);
		success &= testCaseSuccess;
	}

  	return success;
}

void test_logWheelSpining(bool successful, const char *pWheelDebugName, int16_t nbTick) {
	static char logBuffer[128];
	if (successful) {
		snprintf(logBuffer, 128, "%s nbTick:%d [OK]\r\n", pWheelDebugName, nbTick);
		LOG_INFO(logBuffer);
	} else {
		snprintf(logBuffer, 128, "%s nbTick:%d [FAIL]\r\n", pWheelDebugName, nbTick);
		LOG_ERROR(logBuffer);
	}
}

int16_t test_spinAndStopWheel(Wheel_t* pWheel, float speed) {
  	int32_t wheelSpeed[4];
	// Make it spins a little bit
	wheel_setPWM(pWheel, speed);
	osDelay(TIME_LEFT_SPINNING_MS);

	readQuadsSpeed(&wheelSpeed);

	// Stop it
	wheel_break(pWheel);
	osDelay(TIME_BREAKING_MS);

	// We check the absolute value first
	return wheelSpeed[pWheel->quad];
}
