/*
 * robocup_define.h
 *
 *  Created on: 2016-05-28
 *      Author: Gagnon
 */

#ifndef ROBOCUP_ROBOCUP_DEFINE_H_
#define ROBOCUP_ROBOCUP_DEFINE_H_

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


#define MNRC_KP					7.0f
#define MNRC_KI					25.0f
#define MNRC_GAMMA				-3.0f

#define CONTROL_LOOP_PERIOD_MS 	50
#define CONTROL_LOOP_DELTA_T	0.05f
#define CONTROL_LOOP_FREQ		20.0f

#define MOTOR_DEADZONE 			0.21f //Min PWM duty-cycle to compensate deadzone


//PMU
#define PMU_BATT_SHUTDOWN_TRESHOLD		12.6//V : Power is automatically turned off if Voltage is under this value
#define PMU_BATT_WARNING_TRESHOLD		14//V : Power stays on if already turned on, but impossible to enable it if disabled



#endif /* ROBOCUP_ROBOCUP_DEFINE_H_ */
