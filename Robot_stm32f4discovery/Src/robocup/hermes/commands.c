/*
 * commands.c
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#include "commands.h"

#include "../motors/ctrl_task.h"
#include "hermes_task.h"
#include "../kicker.h"

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
    g_speedCommand.tickSinceLastUpdate = xTaskGetTickCount();
}

void command_setRegister(const void *msg) {

	msg_set_register_t * registerMsg = (msg_set_register_t *) msg;
	switch (registerMsg->registe) {
		case CHARGE_KICKER_COMMAND:
			LOG_INFO("Charging!!\r\n");
			kicker_charge();
			break;
		case KICK_COMMAND:
			LOG_INFO("Kicking!!\r\n");
			kicker_kick();
			break;
		case CONTROL_LOOP_STATE:
			switch (registerMsg->value) {
				case 0 :
					g_ctrlLoopState = OPEN_LOOP;
					break;
				case 1:
					g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
					break;
				case 2:
					g_ctrlLoopState = CLOSE_LOOP_WITH_LOGGING;
					break;
			}
			break;
		default:
			LOG_ERROR("Unknown register");
	}

	// TODO: Uncomment when bidirectional implemented
	//hermes_sendAcknowledgment();
}
