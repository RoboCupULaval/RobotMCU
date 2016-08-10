/*
 * commands.c
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#include "commands.h"
#include "hermes.h"

//extern order_t robotOrder;

void nop(const void *msg){}

void command_heartbeatRequest(const void *msg){
	hermes_sendPayloadLessRespond(HeartbeatResponse);
}

// this function extracts the speed commands and puts it into the global struct
void command_movementCommand(const void *msg){
    msg_set_speed_t * movementMsg = (msg_set_speed_t *) msg;
    //robotOrder.vx = movementMsg->vx;
    //robotOrder.vy = movementMsg->vy;
    //robotOrder.vtheta = movementMsg->vtheta;
}
