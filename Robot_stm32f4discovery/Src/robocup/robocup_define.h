/*
 * robocup_define.h
 *
 *  Created on: 2016-05-28
 *      Author: Gagnon
 */

#ifndef ROBOCUP_ROBOCUP_DEFINE_H_
#define ROBOCUP_ROBOCUP_DEFINE_H_

#include "mxconstants.h"
#include "chip_select_demux.h"
#include "quad_driver.h"
#include "hermes/com_interface.h"

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;


// TODO find a way more elegant way to share interface and global variable
/***
 *  Global Variable
 */
typedef struct {
	comHandle_t com;
} hermesHandle_t;
extern hermesHandle_t g_hermesHandle;

//extern quad_Handle quadA;

#define PID_P 13.0
#define PID_I 0.0
//#define PID_I 0.005
#define PID_D 0.000

typedef struct {
		float Ref; // Input: reference set-point
		float Fbk; // Input: feedback
		float Out; // Output: controller output
		float c1; // Internal: derivative filter coefficient
		float c2; // Internal: derivative filter coefficient
} PID_GRANDO_TERMINALS;

typedef struct {
		float Kr; // Parameter: proportional reference weighting
		float Kp; // Parameter: proportional loop gain
		float Ki; // Parameter: integral gain
		float Kd; // Parameter: derivative gain
		float Km; // Parameter: derivative reference weighting
		float Umax; // Parameter: upper saturation limit
		float Umin; // Parameter: lower saturation limit
} PID_GRANDO_PARAMETERS;

typedef struct {
			float up; // Data: propotional term
			float ui; // Data: intefral term
			float ud; // Data: derivative term
			float v1; // Data: pre-saturated controller output
			float i1; // Data: integrator storage: ui(k-1)
			float d1; // Data: differentiator storage: ud (k-1)
			float d2; // Data: differentiator storage: d2(k-1)
			float w1; // Data: saturation record: [u(k-1) - v(k-1)]
} PID_GRANDO_DATA;

typedef struct {
				PID_GRANDO_TERMINALS term;
				PID_GRANDO_PARAMETERS param;
				PID_GRANDO_DATA data;
} PID_Handle;


//typedef struct Robot_Handle {
//
//	SCI_Handle HandleSCI;
//	CLK_Handle HandleCLK;
//	GPIO_Handle HandleGPIO;
//	SPI_Handle HandleSPI;
//	FLASH_Handle HandleFlash;
//    CPU_Handle HandleCpu;
//    PLL_Handle HandlePll;
//    WDOG_Handle HandleWDog;
//
//    // Robot
//    Demux_Handle HandleDemux;
//    nRF24L01_Handle HandleRF;
//    quad_Handle HandleQuad[2];
//    robot_param robotParam;
//    L3GD20_Handle HandleGyro;
//    arduino_Handle HandleArduino;
//    PWM_Handle HandlePwm1;
//    PWM_Handle HandlePwm2;
//    PWM_Handle HandlePwm3;
//    DCMotor_Handle HandleMotor[4];
//    PID_Handle HandlePid[4];
//} Robot_Handle;

//extern Robot_Handle HandleRobot;



#endif /* ROBOCUP_ROBOCUP_DEFINE_H_ */
