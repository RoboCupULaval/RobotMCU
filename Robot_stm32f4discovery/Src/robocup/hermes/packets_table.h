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
		{HeartbeatResponse,                  NULL, (size_t)0},
		{MovementCommand,                    command_movementCommand,  sizeof(msg_set_speed_t)},
		{SetRegister,                        command_setRegister,      sizeof(msg_set_register_t)},
		{Ack,                                NULL,                      (size_t)0},

		{EmergencyStopRequest,               NULL, (size_t)0},
		{UnitTestCommand,                    NULL, (size_t)0},
		{UnitTestResultRequest,              NULL, (size_t)0},
		{UnitTestResults,                    NULL, (size_t)0},
		{BatteryLevelsRequest,               NULL, (size_t)0},
		{BatteryLevels,                      NULL, (size_t)0},
		{BatteryWatchDogParametersRequest,   NULL, (size_t)0},
		{BatteryWatchDogParameters,          NULL, (size_t)0},
		{BatteryWatchDogParametersCommand,   NULL, (size_t)0},
		{ForceBatteryCommand,                NULL, (size_t)0},
		{ForceKickCommand,                   NULL, (size_t)0},
		{PrepareKickCommmand,                NULL, (size_t)0},
		{KickNotification,                   NULL, (size_t)0},
		{PIDParametersRequest,               NULL, (size_t)0},
		{PIDParameters,                      NULL, (size_t)0},
		{PIDParametersCommand,               NULL, (size_t)0},
		{UIDRequest,                         NULL, (size_t)0},
		{UID,                                NULL, (size_t)0},
		{LedStateCommand,                    NULL, (size_t)0},
		{ResetCommand,                       NULL, (size_t)0},
		{CodeVersionRequest,                 NULL, (size_t)0},
		{CodeVersion,                        NULL, (size_t)0},
		{ThermalSensorValuesRequest,         NULL, (size_t)0},
		{ThermalSensorValues,                NULL, (size_t)0},
		{TimeSinceBootRequest,               NULL, (size_t)0},
		{TimeSinceBoot,                      NULL, (size_t)0},
		{KickCapacitorsChargedNotification,  NULL, (size_t)0},
		{PIDEnableDisable,                   NULL, (size_t)0},
		{ForceDribblerOnCommand,             NULL, (size_t)0},
		{ForceDribblerOffCommand,            NULL, (size_t)0},
		{PrepareDribblerCommand,             NULL, (size_t)0},
		{DataCollectRequest,                 NULL, (size_t)0},
		{StopDataCollectRequest,             NULL, (size_t)0},
		{QuadValuesRequest,                  NULL, (size_t)0},
		{QuadValues,                         NULL, (size_t)0},
		{RobotCrashedNotification,           NULL, (size_t)0},
		{CurrentStateRequest,                NULL, (size_t)0},
		{CurrentState,                       NULL, (size_t)0},
		{NewStateCommand,                    NULL, (size_t)0},
		{WirelessTimeWatchdogValueRequest,   NULL, (size_t)0},
		{WirelessTimeWatchdogValue,          NULL, (size_t)0},
		{MovementCommandOpen,				 command_movementCommandOpen, sizeof(msg_set_speed_open_t)}
};

static const size_t g_packetsTableLen = sizeof(g_packetsTable) / sizeof(packet_t);


#endif /* ROBOCUP_PACKETS_TABLE_H_ */
