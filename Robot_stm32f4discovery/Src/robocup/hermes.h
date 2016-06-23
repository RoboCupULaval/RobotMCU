/*
 * hermes.h
 *
 *  Created on: 2016-06-21
 *      Author: Philippe Babin
 */

#ifndef HERMES_TASK_H_
#define HERMES_TASK_H_

#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

/*******************************************************************************
 * User Interface Function
 *******************************************************************************/

typedef struct {
	char protocolVersion;
	char srcAddress;
	char destAddress;
	char packetType;
	char checksum;
} packetHeaderStruct_t;


// an enum for each packet type
enum packetTypes {
	HeartbeatRequest,
	HeartbeatResponse,
	MovementCommand,
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
	WirelessTimeWatchdogValue
};


// the size for each packet type
static size_t dataSizeArray[] = {
0,  // 0x00
0,  // 0x01
16, // 0x02
0,  // 0x03
0,  // 0x04
0,  // 0x05
30, // 0x06
0,  // 0x07
8,  // 0x08
0,  // 0x09
16, // 0x0A
16, // 0x0B
0,  // 0x0C
0,  // 0x0D
0,  // 0x0E
0,  // 0x0F
0,  // 0x10
12, // 0x11
12, // 0x12
0,  // 0x13
12, // 0x14
1,  // 0x15
1,  // 0x16
0,  // 0x17
-1, // 0x18
0,  // 0x19
-1, // 0x1A
0,  // 0x1B
4,  // 0x1C
0,  // 0x1D
1,  // 0x1E
0,  // 0x1F
0,  // 0x20
0,  // 0x21
1,  // 0x22
0,  // 0x23
0,  // 0x24
-1, // 0x25
0,  // 0x26
0,  // 0x27
-1, // 0x28
-1, // 0x29
0,  // 0x2A
1  // 0x2B
};

// TODO: More specific failure than just FAILURE
typedef enum {
	FAILURE,
	MySUCCESS
}Result_t;

typedef struct packetHeaderStruct packetHeaderStruct;


void test_hermes();

Result_t validPayload(packetHeaderStruct_t *currentPacketHeaderPtr, size_t payloadLen);

Result_t cobifyData(const void *ptr, size_t msg_len,   char *dst);

Result_t decobifyData(const char *ptr, size_t len, void *dst, size_t *dst_len);


#endif // HERMES_TASK_H_
