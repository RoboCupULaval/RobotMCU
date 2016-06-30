/*
 * two_wheel_ctrl.h
 *
 *  Created on: 2014-01-06
 *      Author: Philippe Babin
 */

#ifndef FOUR_WHEEL_CTRL_H_
#define FOUR_WHEEL_CTRL_H_

#include <stdio.h>
#include "robocup_define.h"
#include <math.h>
// #include "DCMotor_driver.h"

void fourWheelCtrl_Init();
void fourWheelCtrl_Update( float v, float teta, float w);

#endif /* FOUR_WHEEL_CTRL_H_ */
