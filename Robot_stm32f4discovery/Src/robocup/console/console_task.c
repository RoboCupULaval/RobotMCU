#include "console_task.h"

void console_taskEntryPoint(void) {
	if(!robot_isDebug())
		vTaskSuspend(NULL);

	// We have a small stack, this is why they are static
	static char commandBuffer[255];
	static char parsedCommand[10][25];

	for(;;) {
		// Get data from device
		char buffer[255];
		size_t bytesReceived = g_consoleHandle.readUntilZero(commandBuffer, 255);

		if(bytesReceived == 0){
			// It's more efficient to wait a few ticks before trying again
			osDelay(1);
			continue;
		}

		console_parseCommand(commandBuffer, parsedCommand);

		if(!strcmp("help", parsedCommand[0])) {
			LOG_INFO("\r\n"
					"\r\n"
					"-------------------------------\r\n"
					"-- Help menu -- \r\n"
					"-------------------------------\r\n"
					"-- Util --\r\n"
					"ping\r\n"
					"test-nrf\r\n"
					"-- Ball --\r\n"
					"dribble                    speed\r\n"
					"charge-kicker\r\n"
					"kick                       force\r\n"
					"print-ball-sensors           time\r\n"
					"-- Motors --\r\n"
					"motors-unit-test\r\n"
					"set-pwm                     pwm1 pwm2 pwm3 pwm4 time\r\n"
					"set-speed                   vx vy vtheta time\r\n"
					"set-speed-verbose            vx vy vtheta time\r\n"
					"-- Power management --\r\n"
					"batt-info\r\n"
					"batt-info-repeat             time\r\n"
					"power-off\r\n"
					"power-on\r\n"
					"batt-protection-override\r\n"
					"batt-protection-reset\r\n"
					"-------------------------------\r\n"
					"\r\n");
		}
		else if(!strcmp("ping", parsedCommand[0])) {
			sprintf(buffer, "Hello from Robot %d :)\r\n", robot_getPlayerID());
			LOG_INFO(buffer);
		}
		else if(!strcmp("test-nrf", parsedCommand[0])) {
			if(nrfVerifySPI())
				LOG_INFO("NRF SPI BUS is ok!\r\n");
			else
				LOG_ERROR("NRF SPI BUS is NOT ok!\r\n");
		}
		else if(!strcmp("dribble", parsedCommand[0])) {
			dribbler_startDribbler((float)atof(parsedCommand[1]));
		}
		else if(!strcmp("charge-kicker", parsedCommand[0])) {
			kicker_charge();
		}
		else if(!strcmp("kick", parsedCommand[0])) {
			kicker_kick(atoi(parsedCommand[1]));
		}
		else if(!strcmp("print-ball-sensors", parsedCommand[0])) {
			TickType_t start = xTaskGetTickCount();
			while(xTaskGetTickCount() - start < atoi(parsedCommand[1])) {
				sprintf(buffer, "Sensors : %d and %d, moy : %d\r\n",
						ball_getSensorValue(1), ball_getSensorValue(2), ball_getSensorsMeanValue());
				LOG_INFO(buffer);
				osDelay(50);
			}
		}
		else if(!strcmp("batt-info", parsedCommand[0])) {
			log_metadata();
		}
		else if(!strcmp("batt-info-repeat", parsedCommand[0])) {
			TickType_t start = xTaskGetTickCount();
			while(xTaskGetTickCount() - start < atoi(parsedCommand[1])) {
				log_metadata();
				osDelay(50);
			}
		}
		else if(!strcmp("motors-unit-test", parsedCommand[0])) {
			test_startUp();
		}
		else if(!strcmp("set-pwm", parsedCommand[0])) {
			g_ctrlLoopState = OPEN_LOOP;
			TickType_t start = xTaskGetTickCount();
			while(xTaskGetTickCount() - start < atoi(parsedCommand[5])) {
				g_speedCommandOpen.cmd1 = (float)atof(parsedCommand[1]);
				g_speedCommandOpen.cmd2 = (float)atof(parsedCommand[2]);
				g_speedCommandOpen.cmd3 = (float)atof(parsedCommand[3]);
				g_speedCommandOpen.cmd4 = (float)atof(parsedCommand[4]);
			    g_speedCommandOpen.tickSinceLastUpdate = xTaskGetTickCount();
			}
			g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
		}
		else if(!strcmp("set-speed", parsedCommand[0])) {
			g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
			TickType_t start = xTaskGetTickCount();
			while(xTaskGetTickCount() - start < atoi(parsedCommand[4])) {
				g_speedCommand.vx = (float)atof(parsedCommand[1]);
				g_speedCommand.vy = (float)atof(parsedCommand[2]);
				g_speedCommand.vtheta = (float)atof(parsedCommand[3]);
				g_speedCommand.tickSinceLastUpdate = xTaskGetTickCount();
			}
		}
		else if(!strcmp("set-speed-verbose", parsedCommand[0])) {
			g_ctrlLoopState = CLOSE_LOOP_WITH_LOGGING;
			TickType_t start = xTaskGetTickCount();
			while(xTaskGetTickCount() - start < atoi(parsedCommand[4])) {
				g_speedCommand.vx = (float)atof(parsedCommand[1]);
				g_speedCommand.vy = (float)atof(parsedCommand[2]);
				g_speedCommand.vtheta = (float)atof(parsedCommand[3]);
				g_speedCommand.tickSinceLastUpdate = xTaskGetTickCount();
			}
			g_ctrlLoopState = CLOSE_LOOP_WITHOUT_LOGGING;
		}
		else if(!strcmp("batt-protection-override", parsedCommand[0])) {
			pmu_overrideProtection();
		}
		else if(!strcmp("batt-protection-reset", parsedCommand[0])) {
			pmu_resetProtection();
		}
		else if(!strcmp("power-on", parsedCommand[0])) {
			pmu_overrideProtection();
			pmu_forceEnablePower();
		}
		else if(!strcmp("power-off", parsedCommand[0])) {
			pmu_overrideProtection();
			pmu_disablePower();
		}
		else {
			sprintf(buffer, "Unknown command : %s\r\n", parsedCommand[0]);
			LOG_INFO(buffer);
		}

		// This is use to give back control to other task
		osDelay(1);
	}
}