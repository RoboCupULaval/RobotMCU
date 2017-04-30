#include "console_task.h"

void console_taskEntryPoint(void) {
	if(!robot_isDebug())
		vTaskSuspend(NULL);

	// We have a small stack, this is why they are static
	static char commandBuffer[255];
	static char parsedCommand[10][25];

	for(;;) {
		// Get data from device
		size_t bytesReceived = g_consoleHandle.readUntilZero(commandBuffer, 255);

		if(bytesReceived == 0){
			// It's more efficient to wait a few ticks before trying again
			osDelay(1);
			continue;
		}

		int nbArgs = console_parseCommand(commandBuffer, parsedCommand);

		if(nbArgs > -1) {
			consoleCmd_t cmd = console_getCommand(parsedCommand[0]);
			if(cmd.nbArgs == nbArgs)
				cmd.callback(parsedCommand);
			else {
				LOG_ERROR("Wrong number of arguments for this command.\r\n");
			}
		} else {
			LOG_ERROR("Error during command parsing.\r\n");
		}

		// This is use to give back control to other task
		taskYIELD();
	}
}
