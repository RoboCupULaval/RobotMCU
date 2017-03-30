/*
 * motor_data_log.h
 *
 *  Created on: Nov 12, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_MOTORS_MOTOR_DATA_LOG_H_
#define ROBOCUP_MOTORS_MOTOR_DATA_LOG_H_

#include "../util.h"
#include "pid.h"

void motorDataLog_addWheelData(float reference, float feedback);
void motorDataLog_addReceivedSpeed(float vx, float vy, float vt) ;
void motorDataLog_addCloseLoopData(PidWheel_t* pPid);
void motorDataLog_flushDataLine(void);

#endif /* ROBOCUP_MOTORS_MOTOR_DATA_LOG_H_ */
