#include "wheel.h"

#include <math.h>

// TODO No rotation
#define RADIUS 0

//Acceleration limitation
const float MAX_LIN_ACC	= 1.0f / CONTROL_LOOP_FREQ; //1m/s^2 * control_loop_period s

// Calculate speed for that motor base on velocity command
float wheel_setCommand(Wheel_t* wheel, const float vx, const float vy, const float vt) {

	float limitVx = vx;
	float limitVy = vy;

	const float magnitude = sqrtf(vx*vx + vy*vy);

	if((magnitude - wheel->lastMagnitude) > MAX_LIN_ACC) {
		wheel->lastMagnitude = wheel->lastMagnitude + MAX_LIN_ACC;
		const float magnitudeFactor = wheel->lastMagnitude / magnitude;
		limitVx *= magnitudeFactor;
		limitVy *= magnitudeFactor;
	} else {
		wheel->lastMagnitude = magnitude;
	}

	float omega = (limitVx * wheel->cosTheta + limitVy * wheel->sinTheta + vt * wheel->centerDistance);
	omega = (omega / wheel->radius);

	float result = (omega * wheel->nbTickTurn) / (2.0f * (float)M_PI) / CONTROL_LOOP_FREQ; //Conversion from rad/s to ticks/

	return result;
}

void wheel_break(const Wheel_t *wheel) {
	wheel_setPWM(wheel, MOTOR_BREAK);
}

void wheel_setPWM(const Wheel_t *wheel, float speed) {
	// TODO put in own function
	float speedInverted = 1.0f - (float)fabs(speed);
	int command = ((int) ((float)fabs(speedInverted) * 6500.0f));

	// Less then 4% of power we break
	if((float)fabs(speed) < 0.05){
		command = 6500;
	}

	uint32_t timerValue = (uint32_t)command;
  	__HAL_TIM_SetCompare(wheel->pTimer, wheel->timerChannel, timerValue);


	// A clockwise/anticlockwise refer to rotation of the wheel when looking from the front.
	// A clockwise turn clockwise when the direction pin is set to high
	// Please note this is the WHEEL rotation not the MOTOR rotation
	GPIO_PinState dirPinState = GPIO_PIN_RESET;
	switch (wheel->direction) {
		case ClockWise:
			dirPinState = speed >= 0.0 ? GPIO_PIN_SET : GPIO_PIN_RESET; // use wheel->pid->r ?
			break;
		case AntiClockWise:
		default:
			dirPinState = speed < 0.0 ? GPIO_PIN_SET : GPIO_PIN_RESET;
	}

	// Change the GPIO state
	HAL_GPIO_WritePin(wheel->dirGpioPort, wheel->dirGpioPin, dirPinState);
}


