/*
 * robocup_define.h
 *
 *  Created on: 2016-05-28
 *      Author: Gagnon
 */

#ifndef ROBOCUP_ROBOCUP_DEFINE_H_
#define ROBOCUP_ROBOCUP_DEFINE_H_

#include "chip_select_demux.h"
#include "quad_driver.h"
#include "com_interfaces/com_interface.h"



// TODO find a way more elegant way to share interface and global variable
/***
 *  Global Variable
 */
typedef struct {
	comHandle_t com;
} hermesHandle_t;
extern hermesHandle_t g_hermesHandle;
extern comHandle_t g_logHandle;

/***
 * Global constants
 */


static const uint8_t ADDR_ROBOT = 0x01; // Make it configurable with a switch

//#define BETA
#define GAMMA

#ifdef BETA
#define USE_QUAD
#endif

#define CONTROL_LOOP_PERIOD_MS 10

#define PID_P 5.9f //0.001102f
#define PID_I (0.07416f/100.0f) //0.000009f
#define PID_D 0.0f


#endif /* ROBOCUP_ROBOCUP_DEFINE_H_ */
