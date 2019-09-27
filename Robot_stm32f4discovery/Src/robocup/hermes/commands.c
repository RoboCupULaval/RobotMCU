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
#include "../dribbler.h"

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

void command_movementAdvanceCommand(uint8_t origin_id, uint8_t* msg){
    volatile msg_set_speed_advance_t * moveAdvMsg = (msg_set_speed_advance_t *) msg;
	command_movementCommand(origin_id, (uint8_t*)&moveAdvMsg->speed);

	if (moveAdvMsg->kick_force > 0) {
		LOG_INFO("Kicking!!\r\n");
		kicker_kick(moveAdvMsg->kick_force);
	}


	// Charge flag
	if (moveAdvMsg->dribbler_speed & 0x80) {
		kicker_charge();
	}

	uint8_t dribbler_speed = moveAdvMsg->dribbler_speed;
	dribbler_speed &= ~0x80u; // Remove the MSB
	float newSpeed = 0.0f;
	switch (moveAdvMsg->dribbler_speed) {
		case 1:
			newSpeed = 0.1f;
			break;
		case 2:
			newSpeed = 0.2f;
			break;
		case 3:
			newSpeed = 0.35f;
			break;
		default:
			newSpeed = 0.0f;
	}
	dibbler_tmp_force_activation(newSpeed);
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
			// Kick time is now in increment of 0.1ms, instead of 1ms. We need to stay retrocompatible
			kicker_kick(registerMsg->value * 10);
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
			float newSpeed = 0.0f;
			switch (registerMsg->value) {
				case 1:
					newSpeed = 0.1f;
					break;
				case 2:
					newSpeed = 0.2f;
					break;
				case 3:
					newSpeed = 0.35f;
					break;
				default:
					newSpeed = 0.0f;
			}
			dibbler_tmp_force_activation(newSpeed);
			break;
		default:
			LOG_ERROR("Unknown register");
	}
}

void command_getBatterie(uint8_t origin_id, uint8_t* msg) {
	uint8_t batterieLvl = (uint8_t)(log_getBatteryVoltage()*10.0);
	hermes_send(BATTERIE_RESPONSE, &batterieLvl, sizeof(uint8_t));
}

void command_getNumRequest(uint8_t origin_id, uint8_t* msg) {
	uint32_t numRequest = g_numReceivedRequest;
	hermes_send(NUM_REQUEST_RESPONSE, (uint8_t*)&numRequest, sizeof(uint32_t));

}

