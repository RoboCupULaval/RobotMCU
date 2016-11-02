/*
 * commands.c
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#include "commands.h"

#include "hermes_task.h"
#include "../motors/wheels_task.h"

void nop(const void *msg){}


void command_heartbeatRequest(const void *msg){
	hermes_sendPayloadLessRespond(HeartbeatResponse);
}

// Extracts the speed commands and puts it into the global speed command
void command_movementCommand(const void *msg){
	// TODO: should add timing information, so if connection lost, we break
    msg_set_speed_t * movementMsg = (msg_set_speed_t *) msg;
    g_speedCommand.vx = movementMsg->vx;
    g_speedCommand.vy = movementMsg->vy;
    g_speedCommand.vtheta = movementMsg->vtheta;
}

void command_setRegister(const void *msg) {
	//hermes_sendAcknowledgment();

	msg_set_register_t * registerMsg = (msg_set_register_t *) msg;
	switch (registerMsg->registe) {
	case CONTROL_LOOP_STATE:
		if (registerMsg->value == 0) {
			g_ctrlLoopState = OPEN_LOOP;
		} else {
			g_ctrlLoopState = CLOSE_LOOP;
		}
		break;
	default:
		LOG_ERROR("Unknown register");
	}
}
