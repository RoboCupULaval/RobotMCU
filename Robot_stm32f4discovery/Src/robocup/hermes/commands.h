/*
 * commands.h
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_COMMANDS_H_
#define ROBOCUP_COMMANDS_H_

#include "stdint.h"

enum registerTypes_t {
	CONTROL_LOOP_STATE = 0,
	KICK_COMMAND = 1,
	CHARGE_KICKER_COMMAND = 2,
	SET_DRIBBLER_SPEED_COMMAND = 3
};

void command_heartbeatRequest(const void *msg);
void command_movementCommand(const void *msg);
void command_movementCommandOpen(const void *msg);
void command_setRegister(const void *msg);


#endif /* ROBOCUP_COMMANDS_H_ */
