#ifndef WHEELS_H
#define WHEELS_H

#include <stdio.h>
#include "tim.h"
#include "../robocup_define.h"
#include "../util.h"
#include "pid.h"

// When the direction pin is on the wheel turn clockwise or anti-clockwise
typedef enum {
	ClockWise,
	AntiClockWise
} WheelDirection_t;

// Each quadrature encoder has two counters 1 and 2. We also have two quaddrature encoders
typedef enum{

	EncoderTim1 = 0,
	EncoderTim2 = 1,
	EncoderTim3 = 2,
	EncoderTim4 = 3
} QuadEncoder_t;

typedef struct {
	char*              debugName;           // Name of the wheel for debuging
	PidWheel_t         pid;                 // Instance of the pid
	QuadEncoder_t      quad;                // Which encoder is connected to the motor
	TIM_HandleTypeDef* pTimer;              // Pointer to the instance of the timer used by the motor
	uint32_t           timerChannel;        // Mask used for selecting the individual channel
	GPIO_TypeDef*      dirGpioPort;         // Pointer to the gpio port for the direction pin
	uint16_t           dirGpioPin;          // Mask used for selecting the individual gpio pin
	WheelDirection_t   direction;           // Reverse the pin direction
	float              angle;               // Angle in rad, normally motor1 is at 45 degree and motor4 at -45 degree, refer to documentation for more information on convention
	float              openLoopAttenuation; // In open loop some wheel require a greater voltage to turn than other, this factor multiply the input command.
	float			   cosTheta;
	float			   sinTheta;
	float			   radius;
	float			   centerDistance;
	float 			   nbTickTurn;
	float 			   lastMagnitude;		//Acceleration limitation
} Wheel_t;

//
#define MOTOR_BRAKE 0.0


float wheel_setCommand(Wheel_t* wheel, const float vx, const float vy, const float vt);
void wheel_brake(const Wheel_t *wheel);
void wheel_setPWM(const Wheel_t *wheel, float speed);

#endif /* WHEELS_H */
