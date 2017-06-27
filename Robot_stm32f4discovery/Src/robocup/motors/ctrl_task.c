#include "ctrl_task.h"

#include "wheels_UT.h"
#include "wheels_config.h"
#include "mnrc.h"


typedef struct EncoderTimerAssociation_t{
	QuadEncoder_t identifier;
	TIM_HandleTypeDef* timer;
	EncoderHandle_t encoder;
} EncoderTimerAssociation_t;

static EncoderTimerAssociation_t s_encoders[] = {
	{EncoderTim1, &htim1, {0}},
	{EncoderTim2, &htim2, {0}},
	{EncoderTim3, &htim3, {0}},
	{EncoderTim4, &htim4, {0}}
};
const size_t encodersLen = sizeof(s_encoders) / sizeof(EncoderTimerAssociation_t);

volatile CtrlLoop_t g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
volatile SpeedCommand_t g_speedCommand = {
		.vx = 0.0,
		.vy = 0.0,
		.vtheta = 0,
		.tickSinceLastUpdate = 0
};
volatile SpeedCommandOpen_t g_speedCommandOpen = {
		.cmd1 = 0.0,
		.cmd2 = 0.0,
		.cmd3 = 0.0,
		.cmd4 = 0.0,
		.tickSinceLastUpdate = 0
};




// This tasks deals with the movements of the robot
void ctrl_taskEntryPoint(void) {
	if (robot_isDebug() && robot_isBtnPressed()) {
		while(!test_startUp());
	}
  	LOG_INFO("Starting!!!\r\n");
	initPwmAndQuad();
	MNRC_t mnrc = MNRC_init(MNRC_KP, MNRC_KI, MNRC_GAMMA);

	float wheelSpeed[4];
  	TickType_t lastWakeTime = xTaskGetTickCount();
  	bool speedCommandTimeout = true;
  	bool speedCommandOpenTimeout = true;
	for(;;) {
		// Delay the loop to a fix frequency
		vTaskDelayUntil(&lastWakeTime, CONTROL_LOOP_PERIOD_MS / portTICK_PERIOD_MS);

		static int c = 0;
		if(++c >= 100){
			c = 0; // every seconds
		}

		readQuadsSpeed(wheelSpeed);


		float vx, vy, vt;
		float output[4];

		switch(g_ctrlLoopState) {
			case OPEN_LOOP:
				output[0] = g_speedCommandOpen.cmd1;
				output[1] = g_speedCommandOpen.cmd2;
				output[2] = g_speedCommandOpen.cmd3;
				output[3] = g_speedCommandOpen.cmd4;


				const bool lastSpeedCommandOpenTimeout = speedCommandOpenTimeout;
				speedCommandOpenTimeout = hasSpeedCommandOpenTimeout();
				if (speedCommandOpenTimeout) {
					if (c == 0 || speedCommandOpenTimeout != lastSpeedCommandOpenTimeout)
						LOG_ERROR("Timeout on open loop command\r\n");
					ctrl_emergencyBrake();
					continue;
				}

				for (int i = 0; i < wheelsLen; ++i) {
					Wheel_t* pWheel = &g_wheels[i];
					float feedback = (float)wheelSpeed[pWheel->quad];
					motorDataLog_addWheelData(output[i], feedback);
					wheel_setPWM(pWheel, output[i]);
				}
				break;
			case CLOSE_LOOP_WITHOUT_LOGGING:
			case CLOSE_LOOP_WITH_LOGGING:
				vx = g_speedCommand.vx;
				vy = g_speedCommand.vy;
				vt = g_speedCommand.vtheta;

				const bool lastSpeedCommandTimeout = speedCommandTimeout;
				speedCommandTimeout = hasSpeedCommandTimeout();
				if (speedCommandTimeout) {
					if (c == 0 || speedCommandTimeout != lastSpeedCommandTimeout)
						LOG_ERROR("Timeout on command\r\n");
					ctrl_emergencyBrake();
					continue;
				}


				if(g_ctrlLoopState == CLOSE_LOOP_WITH_LOGGING) {
					motorDataLog_addReceivedSpeed(vx, vy, vt);
				}

				for (int i = 0; i < wheelsLen; ++i) {
					Wheel_t* pWheel = &g_wheels[i];
					float reference = wheel_setCommand(pWheel, vx, vy, vt);
					float measure = wheelSpeed[pWheel->quad];

					mnrc.w[i] = measure;
					mnrc.w_ref[i] = reference;
					if (g_ctrlLoopState == CLOSE_LOOP_WITH_LOGGING) {
						motorDataLog_addWheelData(reference, measure);
					}
				}

				MNRC_update(&mnrc);

				if(fabs(vx) <= SPEED_COMMAND_DEADZONE_VX &&
				   fabs(vy) <= SPEED_COMMAND_DEADZONE_VY &&
				   fabs(vt) <= SPEED_COMMAND_DEADZONE_VT) {
					ctrl_emergencyBrake();
					MNRC_reset(&mnrc);
				} else {
					for (int i = 0; i < wheelsLen; ++i) {
						Wheel_t* pWheel = &g_wheels[i];
						wheel_setPWM(pWheel, mnrc.command[i]);
					}
				}

				break;
			default:
				LOG_ERROR("Unimplemented control loop state.\r\n");
		}
		// Handle logging output for close/open loop test
		if (g_ctrlLoopState == OPEN_LOOP || g_ctrlLoopState == CLOSE_LOOP_WITH_LOGGING) {
			motorDataLog_flushDataLine();
		}

	  }
}

void ctrl_emergencyBrake(void) {
	for(size_t i = 0; i < wheelsLen; ++i) {
		wheel_brake(&g_wheels[i]);
	}
}

void initPwmAndQuad(void) {
	static bool executeOnce = true;
	if(executeOnce) {
		executeOnce = false;

		for(size_t i = 0; i < wheelsLen; ++i) {
		  	HAL_TIM_PWM_Start(g_wheels[i].pTimer, g_wheels[i].timerChannel);
		}

		for(int i = 0; i < encodersLen; ++i) {
			s_encoders[i].encoder = encoder_init(s_encoders[i].timer);
		}
	}
}

void readQuadsSpeed(float *wheelSpeed) {
	for(int i = 0; i < encodersLen; ++i) {
		EncoderTimerAssociation_t* encoderTimerAsso = &s_encoders[i];
		encoder_readCounters(&(encoderTimerAsso->encoder));
		float speed = encoderTimerAsso->encoder.deltaCount * (2.0f * (float)M_PI) * CONTROL_LOOP_FREQ / g_wheels[i].nbTickTurn; //Conversion from tick/loop to rad/s
		wheelSpeed[encoderTimerAsso->identifier] = speed;
	}
}

bool hasSpeedCommandTimeout(void) {
	return xTaskGetTickCount() - g_speedCommand.tickSinceLastUpdate > SPEED_COMMAND_TIMEOUT_TICK / portTICK_PERIOD_MS;
}

bool hasSpeedCommandOpenTimeout(void) {
	return xTaskGetTickCount() - g_speedCommandOpen.tickSinceLastUpdate > SPEED_COMMAND_TIMEOUT_TICK / portTICK_PERIOD_MS;
}
