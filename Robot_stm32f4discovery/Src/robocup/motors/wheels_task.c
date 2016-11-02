#include "wheels_task.h"
#include "wheels_UT.h"

#include "FreeRTOS.h"
#include "cmsis_os.h"

static quad_Handle quadA;
static quad_Handle quadB;

volatile CtrlLoop_t g_ctrlLoopState = CLOSE_LOOP;
volatile SpeedCommand_t g_speedCommand = {.vx = 0,.vy=0, .vtheta=0};

/**
 * Table of wheel configuration.
 * If the motor assignation is wrong, the problem is probably here.
 * Every tim need to be initialized in the main().
 */
Wheel_t wheels[] = {
/* wheel == sticker -> pin == cubeMX name + soudure*/
{"wheel 1", {0}, QuadEncoderB1, &htim5, TIM_CHANNEL_1, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, M_PI_4},              /*wheel 1 -> pin_motor4*/
{"wheel 2", {0}, QuadEncoderA2, &htim8, TIM_CHANNEL_3, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, M_PI_2 + M_PI_4},     /*wheel 2 -> pin_motor1*/
{"wheel 3", {0}, QuadEncoderA1, &htim5, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, -M_PI_2 -M_PI_4},     /*wheel 3 -> pin_motor2*/
{"wheel 4", {0}, QuadEncoderB2, &htim5, TIM_CHANNEL_4, MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, -M_PI_4}              /*wheel 4 -> pin_motor3*/
};
const size_t wheelsLen = sizeof(wheels) / sizeof(Wheel_t);

static char s_dataLineBuffer[255];
static size_t s_dataLineBufferLen = 0;
void openLoop_addWheelData(float reference, float feedback) {
	snprintf(s_dataLineBuffer + s_dataLineBufferLen, 255 - s_dataLineBufferLen, "%.5f|%.3f|", reference, feedback);
	s_dataLineBufferLen = strlen(s_dataLineBuffer);
}

void openLoop_flushDataLine(){
	// Add line return at the end of buffer
	snprintf(s_dataLineBuffer + s_dataLineBufferLen, 255 - s_dataLineBufferLen, "\r\n");
	LOG_INFO(s_dataLineBuffer);
	// Reset position in buffer
	s_dataLineBufferLen = 0;
}


// This tasks deals with the movements of the robot
void wheelTask(void) {

//  	TickType_t lastWakeTimeTest = xTaskGetTickCount();
//	for(;;) {
//		// Delay the loop to a fix frequency
//		vTaskDelayUntil(&lastWakeTimeTest, CONTROL_LOOP_PERIOD_MS * portTICK_PERIOD_MS);
//		//LOG_INFO("STOP messaging yourself! \r\n");
//  	}
  	//for(;;){
  	//	test_startUp();
  	//}
	LOG_INFO("Starting!!!\r\n");
	initPwmAndQuad();

  	int16_t wheelSpeed[4];
  	TickType_t lastWakeTime = xTaskGetTickCount();
	for(;;) {
		// Delay the loop to a fix frequency
		vTaskDelayUntil(&lastWakeTime, CONTROL_LOOP_PERIOD_MS * portTICK_PERIOD_MS);
		static int c = 0;
		if(++c >= 100){
			c =0;
			LOG_INFO("ctrl\r\n");
		}

		// Get the command from communication and compute the wheel-wise command

		readQuadsSpeed(&wheelSpeed);

		// Get the feedback and set it's value for each wheel

		const float vx = g_speedCommand.vx;
		const float vy = g_speedCommand.vy;
		const float vt = g_speedCommand.vtheta;

		// Compute the PID output for each wheel

		for (int i = 0; i < wheelsLen; ++i) {
			Wheel_t* pWheel = &wheels[i];
			float reference = wheel_setCommand(pWheel, vx, vy, vt);
			float feedback = wheelSpeed[pWheel->quad];
			float output = 0.0;

			switch(g_ctrlLoopState) {
				case OPEN_LOOP:
					output = reference;

					openLoop_addWheelData(reference, feedback);
					break;
				case CLOSE_LOOP:
					pWheel->pid.r = reference;
					pWheel->pid.fbk = feedback;
					pid_update(&pWheel->pid);

					output = pWheel->pid.output;
					break;
				default:
					LOG_ERROR("Implemented control loop state.");
			}
		    //wheels[i].pid.output = 0.9;

		    // TODO Add step of convert 100% to pwm tick
			wheel_setPWM(pWheel, output);
		}

		if (g_ctrlLoopState == OPEN_LOOP)
			openLoop_flushDataLine();

		//LOG_INFO("STOP\r\n");
	  }
}

void initPwmAndQuad(void) {
	for(size_t i = 0; i < wheelsLen; ++i) {
	  	HAL_TIM_PWM_Start(wheels[i].pTimer, wheels[i].timerChannel);
		wheels[i].pid = pid_init(PID_P, PID_I, PID_D, 1.0, -1.0);
	}
  	quadA = quad_Init(CS_1);
  	quadB = quad_Init(CS_2);
}

void readQuadsSpeed(int16_t *wheelSpeed) {
	quad_ReadCounters(&quadA);
	quad_ReadCounters(&quadB);

	wheelSpeed[QuadEncoderA1] = quadA.delta_count0;
	wheelSpeed[QuadEncoderA2] = quadA.delta_count1;
	wheelSpeed[QuadEncoderB1] = quadB.delta_count0;
	wheelSpeed[QuadEncoderB2] = quadB.delta_count1;
}

