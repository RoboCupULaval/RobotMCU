#include "console.h"

comHandle_t g_consoleHandle;
static char buffer[255];

void console_init(comHandle_t com){
	g_consoleHandle = com;
}

//Returns the number of args (without the command name)
int console_parseCommand(char pCmd[CONSOLE_MAX_CMD_LEN], consoleArgs_t parsedCmd){
	uint8_t charId = 0;
	uint8_t argId = 0; //id 0 being the command name
	uint8_t argCharId = 0;
	int sizeToReturn = -1; //-1 is an error
	for(charId = 0; charId <= 255; charId++) {
		if(argId >= CONSOLE_MAX_NUM_ARG || argCharId >= CONSOLE_MAX_ARG_LEN) {
			break; //Too much arguments or too long arg => fail
		}
		if(pCmd[charId] == ' ') {
			parsedCmd[argId][argCharId] = '\0';
			argId++;
			argCharId = 0;
		} else if(pCmd[charId] == '\r' || pCmd[charId] == '\0') {
			parsedCmd[argId][argCharId] = '\0';
			sizeToReturn = argId;
			break;
		} else {
			parsedCmd[argId][argCharId++] = pCmd[charId];
		}
	}
	return sizeToReturn;
}

consoleCmd_t console_getCommand(char* commandName) {
	size_t i = 0;
	for(i = 0; i < g_consoleTableLen; i++) {
		if(!strcmp(g_consoleTable[i].commandName, commandName)) {
			return g_consoleTable[i];
		}
	}

	return g_consoleTable[0]; //Unknown command
}

void console_printUnknownCommand(consoleArgs_t args) {
	sprintf(buffer, "Unknown command : %s\r\n", args[0]);
	LOG_INFO(buffer);
}

void console_printHelp(consoleArgs_t args) {
	LOG_INFO("\r\n"
			"\r\n"
			"-------------------------------\r\n"
			"-- Help menu -- \r\n"
			"-------------------------------\r\n"
			"-- Util --\r\n"
			"ping\r\n"
			"test-nrf\r\n"
			"-- Ball --\r\n"
			"dribble                     speed\r\n"
			"charge-kicker\r\n"
			"kick                        force\r\n"
			"print-ball-sensors          time\r\n"
			"-- Motors --\r\n"
			"motors-unit-test\r\n"
			"set-pwm                     pwm1 pwm2 pwm3 pwm4 time\r\n"
			"set-speed                   vx vy vtheta time\r\n"
			"set-speed-verbose           vx vy vtheta time\r\n"
			"-- Power management --\r\n"
			"batt-info\r\n"
			"batt-info-repeat            time\r\n"
			"power-off\r\n"
			"power-on\r\n"
			"batt-protection-override\r\n"
			"batt-protection-reset\r\n"
			"-------------------------------\r\n"
			"\r\n");
}
void console_ping(consoleArgs_t args) {
	sprintf(buffer, "Hello from Robot %d :)\r\n", robot_getPlayerID());
	LOG_INFO(buffer);
}

void console_testNRF(consoleArgs_t args) {
	if(nrfVerifySPI())
		LOG_INFO("NRF SPI BUS is ok!\r\n");
	else
		LOG_ERROR("NRF SPI BUS is NOT ok!\r\n");
}

void console_dribble(consoleArgs_t args) {
	LOG_INFO("Setting dribbler speed.\r\n");
	dribbler_setSpeed((float)atof(args[1]));
}

void console_chargeKicker(consoleArgs_t args) {
	LOG_INFO("Charging kicker.\r\n");
	kicker_charge();
}

void console_kick(consoleArgs_t args) {
	LOG_INFO("Kicking.\r\n");
	kicker_kick(atoi(args[1]));
}

void console_printBallSensors(consoleArgs_t args) {
	TickType_t start = xTaskGetTickCount();
	while(xTaskGetTickCount() - start < atoi(args[1])) {
		sprintf(buffer, "Sensors : %lu and %lu, moy : %lu\r\n",
				ball_getSensorValue(1), ball_getSensorValue(2), ball_getSensorsMeanValue());
		LOG_INFO(buffer);
		osDelay(50);
	}
}

void console_printBattInfo(consoleArgs_t args) {
	log_metadata();
}

void console_printBattInfoRepeat(consoleArgs_t args) {
	TickType_t start = xTaskGetTickCount();
	while(xTaskGetTickCount() - start < atoi(args[1])) {
		log_metadata();
		osDelay(50);
	}
}

void console_motorsUnitTest(consoleArgs_t args) {
	test_startUp();
}

void console_setPWM(consoleArgs_t args) {
	LOG_INFO("Setting motors PWM.\r\n");
	g_ctrlLoopState = OPEN_LOOP;
	TickType_t start = xTaskGetTickCount();
	while(xTaskGetTickCount() - start < atoi(args[5])) {
		g_speedCommandOpen.cmd1 = (float)atof(args[1]);
		g_speedCommandOpen.cmd2 = (float)atof(args[2]);
		g_speedCommandOpen.cmd3 = (float)atof(args[3]);
		g_speedCommandOpen.cmd4 = (float)atof(args[4]);
		g_speedCommandOpen.tickSinceLastUpdate = xTaskGetTickCount();
	}
	g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
}

void console_setSpeed(consoleArgs_t args) {
	LOG_INFO("Setting robot speed.\r\n");
	g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
	TickType_t start = xTaskGetTickCount();
	while(xTaskGetTickCount() - start < atoi(args[4])) {
		g_speedCommand.vx = (float)atof(args[1]);
		g_speedCommand.vy = (float)atof(args[2]);
		g_speedCommand.vtheta = (float)atof(args[3]);
		g_speedCommand.tickSinceLastUpdate = xTaskGetTickCount();
	}
}

void console_setSpeedVerbose(consoleArgs_t args) {
	g_ctrlLoopState = CLOSE_LOOP_WITH_LOGGING;
	TickType_t start = xTaskGetTickCount();
	while(xTaskGetTickCount() - start < atoi(args[4])) {
		g_speedCommand.vx = (float)atof(args[1]);
		g_speedCommand.vy = (float)atof(args[2]);
		g_speedCommand.vtheta = (float)atof(args[3]);
		g_speedCommand.tickSinceLastUpdate = xTaskGetTickCount();
	}
	g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
}

void console_battProtectionOverride(consoleArgs_t args) {
	LOG_INFO("Overriding batt protection.\r\n");
	pmu_overrideProtection();
}

void console_battProtectionReset(consoleArgs_t args){
	LOG_INFO("Resetting batt protection.\r\n");
	pmu_resetProtection();
}

void console_powerOn(consoleArgs_t args) {
	LOG_INFO("Power on.\r\n");
	pmu_overrideProtection();
	pmu_forceEnablePower();
}

void console_powerOff(consoleArgs_t args) {
	LOG_INFO("Power off.\r\n");
	pmu_overrideProtection();
	pmu_disablePower();
}
