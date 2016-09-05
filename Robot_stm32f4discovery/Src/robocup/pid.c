/*
 * pid.c
 *
 * Author: Alexia, Frederic St-pierre and Anouar Hanafi
 */

#include "pid.h"
#include <math.h>

struct PID_Wheel
{
	// the geometrical variables
	float vectorX; // the X component of the wheel's vector
	float vectorY; // the Y component of the wheel's vector

	// the PID parameters
	float Kp; // the kp parameter
	float Ki; // the ki parameter
	float Kd; // the kd parameter
	float uMax; // the maximal u value for the wheel
	float uMin; // the minimal u value for the wheel

	// the PID variables
	float r; // the command from "the user"
	float fbk; // the feedback value that was measured and set
	float e; // the computed error
	float ePrevious; // the previous computed error for the derivator
	float up; // the proportional term
	float ui; // the integration term, also serves as the accumulator
	float ud; // the differential term
	float u;  // the command before Saturation
	float output; // the command after saturation, this is what we want to send to the wheel

};

// declaration (kinda instanciation) of the wheel structs
static struct PID_Wheel wheels[4]; // the four wheels (clock configuration)

// This function initializes the PID structure for each wheel
// Inputs:
//   pKp: The Kp parameter for the PID
//   pKi: The Ki parameter for the PID
//   pKd: The Kd parameter for the PID
//   pUmax: the maximum value for u (saturation)
//   pUmin: the minimum value for u (saturation)

static quad_Handle quadA;
static quad_Handle quadB;

void initializePID(float pKp, float pKi, float pKd, float pUmax, float pUmin){

    // loop for each wheel
	for (int i=0; i<1; i++)
	{
		float theAngle = 3.141592645/2 * i - 3.141592645/2/4;
		wheels[i].vectorX = cos(theAngle);
		wheels[i].vectorY = sin(theAngle);
		// the parameters
		wheels[i].Kp = pKp;
		wheels[i].Ki = pKi;
		wheels[i].Kd = pKd;
		wheels[i].uMax = pUmax;
		wheels[i].uMin = pUmin;

		// the initial values of the PID variables
		wheels[i].r = 0;
		wheels[i].fbk = 0;
		wheels[i].e = 0;
		wheels[i].ePrevious = 0;
		wheels[i].up = 0;
		wheels[i].ui = 0;
		wheels[i].ud = 0;
		wheels[i].u = 0;
		wheels[i].output = 0;


	}
}

// This function computes the PID value and outputs the value to set the wheel with
// Inputs:
//   pWheel: A pointer to the wheel struct
void updatePID(struct PID_Wheel *pWheel){

	// the errors
	pWheel->ePrevious = pWheel->e;
	pWheel->e = pWheel->r - pWheel->fbk;

	// the proportional component
	pWheel->up = pWheel->Kp * pWheel->e;

	// the integral component, this is a rectangular approximation
	pWheel->ui = pWheel->Ki * pWheel->e + pWheel->ui;
	pWheel->ui = (pWheel->ui > pWheel->uMax) ? pWheel->uMax: pWheel->ui ; // prevent the explosion of the integral term

	// the differential component
	pWheel->ud = pWheel->Kd * (pWheel->e - pWheel->ePrevious);

	// the naive command
	pWheel->u = pWheel->up + pWheel->ui + pWheel->ud;

	// the saturated command
	if (pWheel->u >= pWheel->uMax) {
		pWheel->output = pWheel->uMax;
	}
	else if (pWheel->u <= pWheel->uMin) {
		pWheel->output = pWheel->uMin;
	}
	else {
		pWheel->output = pWheel->u;
	}
}

//TODO
float COMMANDX = -2; // the wireless command
float COMMANDY = 0; // the wireless command
float COMMANDROT = 0; // in rad/s
float RADIUS = 0.5;


// This function sets the appropriate PWM value for each wheel
void setWheelsCommands() {
	for (int i=0; i<4; i++) {
		//wheels[i].r = wheels[i].vectorX * COMMANDX + wheels[i].vectorY * COMMANDY + COMMANDROT * RADIUS;
		wheels[i].r = -370.0;

	}
}

void setWheelsPWM() {
	// Range is 20000 to 28000, the output is in the range -1.0 to 1.0
	int command = ((int) fabs(wheels[0].output))* 8000 + 20000;
	//int command = 21000;
	//__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, command); // moteur 2
	//__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, command); // moteur 2?
  	//__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, command); // moteur 3?
  	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, command); // moteur 4?
  	static char buffer[128];
	snprintf(buffer, 128, "fbk: %d err: %d out: %d ", (int)wheels[0].fbk, (int)wheels[0].e, (int)(wheels[0].output *100.0));
	Debug_Print(buffer);

	HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, wheels[0].output > 0.0 ? 0 : 1);
	HAL_GPIO_WritePin(MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, wheels[0].output > 0.0 ? 0 : 1);
	HAL_GPIO_WritePin(MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, wheels[0].output > 0.0 ? 0 : 1);
	HAL_GPIO_WritePin(MOTOR4_DIR_GPIO_Port, MOTOR4_DIR_Pin, wheels[0].output > 0.0 ? 0 : 1);
	//HAL_GPIO_WritePin(MOTOR3_DIR_GPIO_Port, MOTOR3_DIR_Pin, command > 0 ? 1 : 0);

	//__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 7<<12); // moteur 1
//__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, (int) abs(wheels[0].output));
//__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, (int) abs(wheels[1].output));
//__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, (int) abs(wheels[2].output));
//__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, (int) abs(wheels[3].output));
}
#define MOTOR_FOR_QUAD_A1 2
#define MOTOR_FOR_QUAD_A2 1
#define MOTOR_FOR_QUAD_B1 0
#define MOTOR_FOR_QUAD_B2 3

// This tasks deals with the movements of the robot
void wheelTask(void * pvParameters) {
	Debug_Print("Starting!!!\r\n");
	//initializePID(1, 0.05, 0, 28000, -28000);
	initializePID(0.00001, 0.00001, 0, 1, -1);
  	quadA = quad_Init(CS_1);
  	quadB = quad_Init(CS_2);
	while (1)
	  {

		// Get the command from communication and compute the wheel-wise command
		setWheelsCommands();

		// Get the feedback and set it's value for each wheel
		quad_ReadCounters(&quadA);
		quad_ReadCounters(&quadB);
		Debug_Print("\r\n");

		wheels[MOTOR_FOR_QUAD_A1].fbk = quadA.delta_count0;
		wheels[MOTOR_FOR_QUAD_A2].fbk = quadA.delta_count1;
		wheels[MOTOR_FOR_QUAD_B1].fbk = quadB.delta_count0;
		wheels[MOTOR_FOR_QUAD_B2].fbk = quadB.delta_count1;

		// Compute the PID output for each wheel
		for (int i=0; i<1; i++) {
		    updatePID(&(wheels[i]));
		}

		// set the wheels PWM
		setWheelsPWM();

		osDelay(50); // 4ms ~= 250hz
	  }

}

