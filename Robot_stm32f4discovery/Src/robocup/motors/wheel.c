#include "wheel.h"

#include <math.h>

// TODO No rotation
#define RADIUS 0

//Acceleration limitation
const float MAX_LIN_ACC	= 1.0f / CONTROL_LOOP_FREQ; //1m/s^2 * control_loop_period s

// Calculate speed for that motor base on velocity command
float wheel_setCommand(Wheel_t* wheel, const float vx, const float vy, const float vt) {

	float omega = (vx * wheel->cosTheta + vy * wheel->sinTheta + vt * wheel->centerDistance);
	omega = (omega / wheel->radius);

	return omega;
}

void wheel_break(const Wheel_t *wheel) {
	wheel_setPWM(wheel, MOTOR_BREAK);
}

void wheel_setPWM(const Wheel_t *wheel, float speed) {
	// Deadzone compensation + 100% pwm saturation
	float compensatedSpeed = (float)fabs(speed) + MOTOR_DEADZONE;
	compensatedSpeed = (compensatedSpeed > 1.0f ? 1.0f : compensatedSpeed);

	// TODO put in own function
	float invertedSpeed = 1.0f - compensatedSpeed;
	int pwm = (int) ((float)invertedSpeed * 6500.0f);

	// Less than BREAKING_DEADZONE of power we break
	if((float)fabs(speed) < BRAKING_THRESHOLD){
		pwm = 6500;
	}

	uint32_t timerValue = (uint32_t)pwm;
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


