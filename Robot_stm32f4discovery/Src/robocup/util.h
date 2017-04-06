/*
 * util.h
 *
 *  Created on: Jun 26, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_UTIL_H_
#define ROBOCUP_UTIL_H_
#include <stdint.h>
#include <stdbool.h>

#include "log.h"
#include "robocup_define.h"


uint8_t robot_isDebug(void);
uint8_t robot_getPlayerID(void);
uint8_t robot_getUniqueRobotID(void);
bool robot_isBtnPressed(void);


#endif /* ROBOCUP_UTIL_H_ */
