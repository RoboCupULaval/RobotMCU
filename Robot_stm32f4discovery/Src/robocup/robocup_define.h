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

#define PID_P 13.0
#define PID_I 0.0
//#define PID_I 0.005
#define PID_D 0.000


#endif /* ROBOCUP_ROBOCUP_DEFINE_H_ */
