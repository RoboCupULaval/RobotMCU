/*
 * hermes.h
 *
 *  Created on: 2016-06-21
 *      Author: Philippe Babin
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../robocup_define.h"
#include "../hermes/com_interfaces/com_interface.h"
#include "../util.h"

#include "../pmu.h"
#include "../dribbler.h"
#include "../kicker.h"
#include "../ball_detector.h"
#include "../nrfDriver/nrfDriver.h"
#include "../motors/wheel.h"
#include "../motors/wheels_config.h"
#include "../motors/ctrl_task.h"
#include "../motors/wheels_UT.h"

#define CONSOLE_MAX_CMD_LEN		256
#define CONSOLE_MAX_NUM_ARG		10
#define CONSOLE_MAX_ARG_LEN		25

typedef char consoleArgs_t[CONSOLE_MAX_NUM_ARG][CONSOLE_MAX_ARG_LEN];
typedef void (*console_callback_t)(consoleArgs_t);
typedef struct {
	const char* commandName;
	console_callback_t callback;
	const uint8_t nbArgs;
} consoleCmd_t;

void console_init(comHandle_t com);
int console_parseCommand(char pCmd[CONSOLE_MAX_CMD_LEN], consoleArgs_t parsedCmd);
consoleCmd_t console_getCommand(char* commandName);

//Console commands
void console_printUnknownCommand(consoleArgs_t args);
void console_printHelp(consoleArgs_t args);
void console_calibStart(consoleArgs_t args);
void console_calibStop(consoleArgs_t args);
void console_calibAddGoodSample(consoleArgs_t args);
void console_calibAddBadSample(consoleArgs_t args);
void console_ping(consoleArgs_t args);
void console_testNRF(consoleArgs_t args);
void console_dribble(consoleArgs_t args);
void console_chargeKicker(consoleArgs_t args);
void console_kick(consoleArgs_t args);
void console_printBallSensors(consoleArgs_t args);
void console_printBattInfo(consoleArgs_t args);
void console_printBattInfoRepeat(consoleArgs_t args);
void console_motorsUnitTest(consoleArgs_t args);
void console_setPWM(consoleArgs_t args);
void console_setSpeed(consoleArgs_t args);
void console_setSpeedVerbose(consoleArgs_t args);
void console_battProtectionOverride(consoleArgs_t args);
void console_battProtectionReset(consoleArgs_t args);
void console_powerOn(consoleArgs_t args);
void console_powerOff(consoleArgs_t args);

static const consoleCmd_t g_consoleTable[] = {
	{"unknown-command", 			&console_printUnknownCommand, 		0},
	{"help", 						&console_printHelp, 				0},
	{"ping", 						&console_ping, 						0},
	{"test-nrf", 					&console_testNRF, 					0},
	{"dribble", 					&console_dribble, 					1},
	{"charge-kicker", 				&console_chargeKicker, 				0},
	{"kick", 						&console_kick,						1},
	{"print-ball-sensors", 			&console_printBallSensors, 			1},
	{"batt-info", 					&console_printBattInfo, 			0},
	{"batt-info-repeat",			&console_printBattInfoRepeat, 		1},
	{"motors-unit-test", 			&console_motorsUnitTest, 			0},
	{"set-pwm", 					&console_setPWM, 					5},
	{"set-speed", 					&console_setSpeed, 					4},
	{"set-speed-verbose", 			&console_setSpeedVerbose, 			4},
	{"batt-protection-override", 	&console_battProtectionOverride, 	0},
	{"batt-protection-reset", 		&console_battProtectionReset, 		0},
	{"power-on", 					&console_powerOff, 					0},
	{"power-off", 					&console_powerOn, 					0},
	{"calib-start", 				&console_calibStart, 				0},
	{"calib-sample-good", 			&console_calibAddGoodSample, 		0},
	{"calib-sample-bad", 			&console_calibAddBadSample, 		0},
	{"calib-stop", 					&console_calibStop, 				0}
};

static const size_t g_consoleTableLen = sizeof(g_consoleTable) / sizeof(consoleCmd_t);

#endif // CONSOLE_H_
