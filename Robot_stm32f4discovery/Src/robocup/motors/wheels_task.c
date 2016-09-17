#include "wheels_task.h"

static quad_Handle quadA;
static quad_Handle quadB;

CtrlLoop_t g_ctrlLoopState = CLOSE_LOOP;

/**
 * Table of wheel configuration. If the motor assignation is wrong, the problem is probably here
 */
static Wheel_t wheels[] = {
/* wheel == sticker -> pin == cubeMX name + soudure*/
/*wheel 1 -> pin_motor4*/ {{0}, QuadEncoderB1, &htim2, TIM_CHANNEL_4, MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, ClockWise, M_PI_4},
///*wheel 2 -> pin_motor1*/ {{0}, QuadEncoderA2, &htim3, TIM_CHANNEL_3, MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, ClockWise, M_PI_2 - M_PI_4},
///*wheel 3 -> pin_motor2 */ {{0}, QuadEncoderA1, &htim2, TIM_CHANNEL_3, MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, ClockWise, M_PI_2 + M_PI_4},
///*wheel 4 -> pin_motor3 */ {{0}, QuadEncoderB2, &htim3, TIM_CHANNEL_4, MOTOR4_DIR_GPIO_Port, MOTOR3_DIR_Pin, ClockWise, -M_PI_4}
};
static const size_t wheelsLen = sizeof(wheels) / sizeof(Wheel_t);



// This tasks deals with the movements of the robot
void wheelTask(void * pvParameters) {

	Debug_Print("Starting!!!\r\n");
	for(int i = 0; i < wheelsLen; ++i) {
		wheels[i].pid = pid_init(0.00001, 0.00001, 0, 1, -1);
	}
  	quadA = quad_Init(CS_1);
  	quadB = quad_Init(CS_2);
  	int16_t wheelSpeed[4];
	while (1) {

		// Get the command from communication and compute the wheel-wise command

		// Get the feedback and set it's value for each wheel
		quad_ReadCounters(&quadA);
		quad_ReadCounters(&quadB);
		//Debug_Print("\r\n");

		wheelSpeed[QuadEncoderA1] = quadA.delta_count0;
		wheelSpeed[QuadEncoderA2] = quadA.delta_count1;
		wheelSpeed[QuadEncoderB1] = quadB.delta_count0;
		wheelSpeed[QuadEncoderB2] = quadB.delta_count1;

		float vx, vy, vt = 0;
		vx = 0.5;
		vy = 0.5;

		// Compute the PID output for each wheel
		for (int i = 0; i < wheelsLen; ++i) {
			float reference = wheel_setCommand(&wheels[i], vx, vy, vt);
			float feedback = wheelSpeed[wheels[i].quad];

			if (g_ctrlLoopState == CLOSE_LOOP) {
				wheels[i].pid.output = reference;

				static char buffer[128];
				// No float printf
				snprintf(buffer, 128, "ref:%f, fbk:%3d.%2d ", reference,
															   (int)feedback,  ((int)feedback*100) % 100);
				Debug_Print(buffer);
			} else {
				wheels[i].pid.r = reference;
				wheels[i].pid.fbk = feedback;
				pid_update(&wheels[i].pid);
			}
		    //wheels[i].pid.output = 0.9;

		    // TODO Add step of convert 100% to pwm tick
			wheel_setPWM(&wheels[i]);
		}
		if (g_ctrlLoopState == CLOSE_LOOP)
			Debug_Print("\r\n");


		osDelay(50); // 4ms ~= 250hz
	  }
}

