/*
 * packets_table.h
 *
 *  Created on: Jun 25, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_PACKETS_TABLE_H_
#define ROBOCUP_PACKETS_TABLE_H_

#include <stdint.h>

#include "commands.h"
// commands.c ->
//			hermes.h(send_respond),
//          packet_Table(enum)
// hermes.h ->
//          commands.h(struct),
//          packet_table(everything)
// commands.h
// packet_table ->
//          commands.h(functions)


// an enum for each packet type
enum packetTypes_t {
	HeartbeatRequest = 0,
	HeartbeatResponse,
	MovementCommand,
	SetRegister,
	Ack,

	EmergencyStopRequest,
	UnitTestCommand,
	UnitTestResultRequest,
	UnitTestResults,
	BatteryLevelsRequest,
	BatteryLevels,
	BatteryWatchDogParametersRequest,
	BatteryWatchDogParameters,
	BatteryWatchDogParametersCommand,
	ForceBatteryCommand,
	ForceKickCommand,
	PrepareKickCommmand,
	KickNotification,
	PIDParametersRequest,
	PIDParameters,
	PIDParametersCommand,
	UIDRequest,
	UID,
	LedStateCommand,
	ResetCommand,
	CodeVersionRequest,
	CodeVersion,
	ThermalSensorValuesRequest,
	ThermalSensorValues,
	TimeSinceBootRequest,
	TimeSinceBoot,
	KickCapacitorsChargedNotification,
	PIDEnableDisable,
	ForceDribblerOnCommand,
	ForceDribblerOffCommand,
	PrepareDribblerCommand,
	DataCollectRequest,
	StopDataCollectRequest,
	QuadValuesRequest,
	QuadValues,
	RobotCrashedNotification,
	CurrentStateRequest,
	CurrentState,
	NewStateCommand,
	WirelessTimeWatchdogValueRequest,
	WirelessTimeWatchdogValue,
	MovementCommandOpen //46
};



typedef void (*cmd_func_t)(const void *msg);
typedef struct {
	int        id;
	cmd_func_t callback;
	size_t     len;
} packet_t;

// TODO implement most of the command :)
static const packet_t g_packetsTable[] = {
		{HeartbeatRequest,                   command_heartbeatRequest, sizeof(msg_no_arg_t)},
		{HeartbeatResponse,                  nop, (size_t)0},
		{MovementCommand,                    command_movementCommand,  sizeof(msg_set_speed_t)},
		{SetRegister,                        command_setRegister,      sizeof(msg_set_register_t)},
		{Ack,                                nop,                      (size_t)0},

		{EmergencyStopRequest,               nop, (size_t)0},
		{UnitTestCommand,                    nop, (size_t)0},
		{UnitTestResultRequest,              nop, (size_t)0},
		{UnitTestResults,                    nop, (size_t)0},
		{BatteryLevelsRequest,               nop, (size_t)0},
		{BatteryLevels,                      nop, (size_t)0},
		{BatteryWatchDogParametersRequest,   nop, (size_t)0},
		{BatteryWatchDogParameters,          nop, (size_t)0},
		{BatteryWatchDogParametersCommand,   nop, (size_t)0},
		{ForceBatteryCommand,                nop, (size_t)0},
		{ForceKickCommand,                   nop, (size_t)0},
		{PrepareKickCommmand,                nop, (size_t)0},
		{KickNotification,                   nop, (size_t)0},
		{PIDParametersRequest,               nop, (size_t)0},
		{PIDParameters,                      nop, (size_t)0},
		{PIDParametersCommand,               nop, (size_t)0},
		{UIDRequest,                         nop, (size_t)0},
		{UID,                                nop, (size_t)0},
		{LedStateCommand,                    nop, (size_t)0},
		{ResetCommand,                       nop, (size_t)0},
		{CodeVersionRequest,                 nop, (size_t)0},
		{CodeVersion,                        nop, (size_t)0},
		{ThermalSensorValuesRequest,         nop, (size_t)0},
		{ThermalSensorValues,                nop, (size_t)0},
		{TimeSinceBootRequest,               nop, (size_t)0},
		{TimeSinceBoot,                      nop, (size_t)0},
		{KickCapacitorsChargedNotification,  nop, (size_t)0},
		{PIDEnableDisable,                   nop, (size_t)0},
		{ForceDribblerOnCommand,             nop, (size_t)0},
		{ForceDribblerOffCommand,            nop, (size_t)0},
		{PrepareDribblerCommand,             nop, (size_t)0},
		{DataCollectRequest,                 nop, (size_t)0},
		{StopDataCollectRequest,             nop, (size_t)0},
		{QuadValuesRequest,                  nop, (size_t)0},
		{QuadValues,                         nop, (size_t)0},
		{RobotCrashedNotification,           nop, (size_t)0},
		{CurrentStateRequest,                nop, (size_t)0},
		{CurrentState,                       nop, (size_t)0},
		{NewStateCommand,                    nop, (size_t)0},
		{WirelessTimeWatchdogValueRequest,   nop, (size_t)0},
		{WirelessTimeWatchdogValue,          nop, (size_t)0},
		{MovementCommandOpen,				 command_movementCommandOpen, sizeof(msg_set_speed_open_t)}
};

static const size_t g_packetsTableLen = sizeof(g_packetsTable) / sizeof(packet_t);


#endif /* ROBOCUP_PACKETS_TABLE_H_ */
