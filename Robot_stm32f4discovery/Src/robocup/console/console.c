#include "console.h"

comHandle_t g_consoleHandle;

void console_init(comHandle_t com){
	g_consoleHandle = com;
}


void console_parseCommand(char pCmd[255], char parsedCmd[10][25]){
	uint8_t charId = 0;
	uint8_t argId = 0; //id 0 being the command name
	uint8_t argCharId = 0;
	for(charId = 0; charId <= 255; charId++) {
		if(pCmd[charId] == ' ') {
			parsedCmd[argId][argCharId] = '\0';
			argId++;
			argCharId = 0;
		} else if(pCmd[charId] == '\r' || pCmd[charId] == '\0') {
			parsedCmd[argId][argCharId] = '\0';
			break;
		} else {
			parsedCmd[argId][argCharId++] = pCmd[charId];
		}
	}
}
