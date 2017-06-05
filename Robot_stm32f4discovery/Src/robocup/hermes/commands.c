/*
 * commands.c
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#include "../dribbler.h"

#include "commands.h"

#include "../motors/ctrl_task.h"
#include "hermes_task.h"
#include "../kicker.h"

void command_heartbeatRequest(uint8_t origin_id, uint8_t* msg){
	hermes_send(PING_RESPONSE, NULL, 0);
}

// Extracts the speed commands and puts it into the global speed command
void command_movementCommand(uint8_t origin_id, uint8_t* msg){
    msg_set_speed_t * movementMsg = (msg_set_speed_t *) msg;
    g_speedCommand.vx = movementMsg->vx;
    g_speedCommand.vy = movementMsg->vy;
    g_speedCommand.vtheta = movementMsg->vtheta;

    g_speedCommand.tickSinceLastUpdate = xTaskGetTickCount();
}

void command_movementCommandOpen(uint8_t origin_id, uint8_t* msg){
	// TODO: should add timing information, so if connection lost, we break
    msg_set_speed_open_t * movementMsg = (msg_set_speed_open_t *) msg;
    g_speedCommandOpen.cmd1 = movementMsg->cmd1;
    g_speedCommandOpen.cmd2 = movementMsg->cmd2;
    g_speedCommandOpen.cmd3 = movementMsg->cmd3;
    g_speedCommandOpen.cmd4 = movementMsg->cmd4;
    g_speedCommandOpen.tickSinceLastUpdate = xTaskGetTickCount();
}

void command_setRegister(uint8_t origin_id, uint8_t* msg){

	msg_set_register_t * registerMsg = (msg_set_register_t *) msg;
	switch (registerMsg->registerNumber) {
		case CHARGE_KICKER_COMMAND:
			LOG_INFO("Charging!!\r\n");
			kicker_charge();
			break;
		case KICK_COMMAND:
			LOG_INFO("Kicking!!\r\n");
			kicker_kick(registerMsg->value);
//			switch (registerMsg->value) {
//				case 1:
//					LOG_INFO("KICKER_FORCE_1\r\n");
//					kicker_kick(KICKER_FORCE_1);
//					break;
//				case 2:
//					LOG_INFO("KICKER_FORCE_2\r\n");
//					kicker_kick(KICKER_FORCE_2);
//					break;
//				case 3:
//					LOG_INFO("KICKER_FORCE_3\r\n");
//					kicker_kick(KICKER_FORCE_3);
//					break;
//				case 4:
//					LOG_INFO("KICKER_FORCE_4\r\n");
//					kicker_kick(KICKER_FORCE_4);
//					break;
//				default:
//					LOG_ERROR("Kicker error\r\n");
//					break;
//			}
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
		case SET_DRIBBLER_SPEED_COMMAND:
			LOG_INFO("New dribbleur speed\r\n");
			float newSpeed = 0.0;
			switch (registerMsg->value) {
				case 1:
					newSpeed = 0.3f;
					break;
				case 2:
					newSpeed = 0.5f;
					break;
				case 3:
					newSpeed = 0.7f;
					break;
				default:
					newSpeed = 0.0f;
			}
			dribbler_startDribbler(newSpeed);
			break;
		default:
			LOG_ERROR("Unknown register");
	}
}
