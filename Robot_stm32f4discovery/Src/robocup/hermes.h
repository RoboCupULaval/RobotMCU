/*
 * CS_demux.h
 *
 *  Created on: 2014-01-09
 *      Author: Philippe Babin
 */

#ifndef SAMPLE_TASK_H_
#define SAMPLE_TASK_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

/*******************************************************************************
 * User Interface Function
 *******************************************************************************/

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
int dataSizeArray[] = {
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



typedef struct packetHeaderStruct packetHeaderStruct;

void decobifyData(const unsigned char *originalData,
				  unsigned char *decobifiedData,
		          unsigned long numberOfBytes);

void cobifyData(const unsigned char *originalData,
		  		        unsigned char *cobifiedData, unsigned long originalNumberOfBytes);



#endif
