#include "wheels_task.h"

static quad_Handle quadA;
static quad_Handle quadB;

CtrlLoop_t g_ctrlLoopState = CLOSE_LOOP;

/**
 * Table of wheel configuration. If the motor assignation is wrong, the problem is probably here
	Every tim need to be initialized in the main().
 */
static Wheel_t wheels[] = {
/* wheel == sticker -> pin == cubeMX name + soudure*/
{"wheel 1", {0}, QuadEncoderB1, &htim5, TIM_CHANNEL_1, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, M_PI_4},              /*wheel 1 -> pin_motor4*/
{"wheel 2", {0}, QuadEncoderA2, &htim8, TIM_CHANNEL_3, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, M_PI_2 + M_PI_4}, /*wheel 2 -> pin_motor1*/
{"wheel 3", {0}, QuadEncoderA1, &htim5, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, -M_PI_2 -M_PI_4},     /*wheel 3 -> pin_motor2*/
{"wheel 4", {0}, QuadEncoderB2, &htim5, TIM_CHANNEL_4, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, -M_PI_4}              /*wheel 4 -> pin_motor3*/
};
static const size_t wheelsLen = sizeof(wheels) / sizeof(Wheel_t);

const float   NORMAL_SPEED          = 1.5;
const float   BREAK_SPEED           = 0;
const int     TIME_LEFT_SPINNING_MS = 100;
const int     TIME_BREAKING_MS      = 700;
const int16_t MIN_TICK_FOR_MOVEMENT = 800;

bool test_startUp() {
  	quadA = quad_Init(CS_1);
  	quadB = quad_Init(CS_2);
	for(size_t i = 0; i < wheelsLen; ++i) {
		// Start the pwm
	  	HAL_TIM_PWM_Start(wheels[i].pTimer, wheels[i].timerChannel);
	}

	bool success = true;
	LOG_INFO("MOTORS - Each motor should remains immobile \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &wheels[i];
		LOG_INFO(pWheel->debugName);

		int16_t nbTick = abs(test_spinAndStopWheel(pWheel, BREAK_SPEED));
		// Check absolute value
		bool testCaseSuccess = nbTick < MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, nbTick);
		success &= testCaseSuccess;

	}
  	if(!success)
  		return success;

	LOG_INFO("MOTORS - Each motor turns the right encoder \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &wheels[i];
		LOG_INFO(pWheel->debugName);

		int16_t nbTick = abs(test_spinAndStopWheel(pWheel, NORMAL_SPEED));
		// Check absolute value
		bool testCaseSuccess = nbTick > MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, nbTick);
		success &= testCaseSuccess;

	}
  	if(!success)
  		return success;

	LOG_INFO("MOTORS - Each wheels turns clockwise \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &wheels[i];
		LOG_INFO(pWheel->debugName);

		int16_t nbTick = test_spinAndStopWheel(pWheel, NORMAL_SPEED);

		bool testCaseSuccess = nbTick > MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, nbTick);
		success &= testCaseSuccess;
	}
  	if(!success)
  		return success;


	LOG_INFO("MOTORS - Each wheels turns anti-clockwise \r\n");
  	for (size_t i = 0; i < wheelsLen; ++i) {
		Wheel_t* pWheel = &wheels[i];
		LOG_INFO(pWheel->debugName);

		int16_t nbTick = test_spinAndStopWheel(pWheel, -NORMAL_SPEED);

		bool testCaseSuccess = nbTick < -MIN_TICK_FOR_MOVEMENT;
		test_logWheelSpining(testCaseSuccess, nbTick);
		success &= testCaseSuccess;
	}

  	return success;
}

void test_logWheelSpining(bool successful, int16_t nbTick) {
	static char logBuffer[128];
	if(successful)
		snprintf(logBuffer, 128, " nbTick:%d [OK]\r\n", nbTick);
	else
		snprintf(logBuffer, 128, " nbTick:%d [FAIL]\r\n", nbTick);
	LOG_INFO(logBuffer);
}

int16_t test_spinAndStopWheel(Wheel_t* pWheel, float speed) {
  	int16_t wheelSpeed[4];
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


// This tasks deals with the movements of the robot
void wheelTask() {

  	for(;;){
		LOG_INFO("STOP messaging yourself! \r\n");
		osDelay(1000);
  	}
	test_startUp();
  	for(;;){
  	}
	return;
	LOG_INFO("Starting!!!\r\n");
	for(size_t i = 0; i < wheelsLen; ++i) {
		// Start the pwm
	  	HAL_TIM_PWM_Start(wheels[i].pTimer, wheels[i].timerChannel);
		wheels[i].pid = pid_init(0.00001, 0.00001, 0, 1, -1);
	}
  	quadA = quad_Init(CS_1);
  	quadB = quad_Init(CS_2);

  	int16_t wheelSpeed[4];
	while (1) {

		// Get the command from communication and compute the wheel-wise command
		readQuadsSpeed(&wheelSpeed);
		// Get the feedback and set it's value for each wheel

		float vx, vy, vt = 0;
		vx = 1.2;
		vy = 1.2;

		// Compute the PID output for each wheel
		for (int i = 0; i < wheelsLen; ++i) {
			Wheel_t* pWheel = &wheels[i];
			float reference = wheel_setCommand(pWheel, vx, vy, vt);
			float feedback = wheelSpeed[pWheel->quad];
			float output = 0.0;

			if (g_ctrlLoopState == CLOSE_LOOP) {
				output = reference;

				static char buffer[128];
				snprintf(buffer, 128, "%s ref:%.5f, fbk:%.3f ", pWheel->debugName, reference, feedback);
				LOG_INFO(buffer);
			} else {
				pWheel->pid.r = reference;
				pWheel->pid.fbk = feedback;
				pid_update(&pWheel->pid);

				output = pWheel->pid.output;
			}
		    //wheels[i].pid.output = 0.9;

		    // TODO Add step of convert 100% to pwm tick
			wheel_setPWM(pWheel, output);
		}

		if (g_ctrlLoopState == CLOSE_LOOP)
			LOG_INFO("\r\n");


		osDelay(50); // 4ms ~= 250hz
	  }
}

void readQuadsSpeed(int16_t *wheelSpeed) {
	quad_ReadCounters(&quadA);
	quad_ReadCounters(&quadB);

	wheelSpeed[QuadEncoderA1] = quadA.delta_count0;
	wheelSpeed[QuadEncoderA2] = quadA.delta_count1;
	wheelSpeed[QuadEncoderB1] = quadB.delta_count0;
	wheelSpeed[QuadEncoderB2] = quadB.delta_count1;
}

