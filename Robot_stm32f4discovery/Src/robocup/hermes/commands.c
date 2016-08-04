/*
 * commands.c
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#include "commands.h"
#include "hermes.h"

void nop(const void *msg){}

void command_heartbeatRequest(const void *msg){
	hermes_sendPayloadLessRespond(HeartbeatResponse);
}

void command_movementCommand(const void *msg){

}
