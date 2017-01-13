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


//PMU
typedef enum {
	POWER_OK, //Possible to enable power
	POWER_WARNING, //Power stays enable if already enabled, but can't enable it otherwise
	POWER_CRITICAL, //Disabled automatically
} powerState;



/***
 * Global constants
 */


static const uint8_t ADDR_ROBOT = 0x01; // Make it configurable with a switch

//#define BETA
#define GAMMA
//#define GAMMA2

#ifdef BETA
#define USE_QUAD
#endif

#define CONTROL_LOOP_PERIOD_MS 10

#define PID_P 5.9f //0.001102f
#define PID_I (0.07416f/100.0f) //0.000009f
#define PID_D 0.0f


//PMU
#define PMU_BATT_SHUTDOWN_TRESHOLD		13.2//V : Power is automatically turned off if Voltage is under this value
#define PMU_BATT_WARNING_TRESHOLD		14//V : Power stays on if already turned on, but impossible to enable it if disabled


//PMU
#define PMU_BATT_SHUTDOWN_TRESHOLD		13.2//V : Power is automatically turned off if Voltage is under this value
#define PMU_BATT_WARNING_TRESHOLD		14//V : Power stays on if already turned on, but impossible to enable it if disabled


#endif /* ROBOCUP_ROBOCUP_DEFINE_H_ */
