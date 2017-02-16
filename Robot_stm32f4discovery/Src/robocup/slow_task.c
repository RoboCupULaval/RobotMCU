#include "dribbler.h"

#include "slow_task.h"

powerState slow_handleBattProtection(void);
void       slow_handleDribbler(void);

void slow_taskEntryPoint(void) {
	pmu_init();
	dribbler_init();
	led_init();
	kicker_init();

	dribbler_setPWM(0.0f);

	if (robot_isDebug()) {
		led_swipingLedTest();
	}

	uint8_t dribblerState = 0;
	uint8_t id = robot_getID();
	for(;;) {
		//Debug modee
		if(robot_isDebug()) {
			led_turnOn(8);

			//ID selection
			led_turnOff(id);
			id = robot_getID();
			led_turnOn(id);
		}

		kicker_update();

		log_setBatteryVoltage(pmu_getBattVoltage());

		slow_handleBattProtection();

		dribbler_handleDribbler();

		HAL_Delay(30);
	}
}


//Automatically reads batt voltage and decides if the power should be disable
//Returns the power state
powerState slow_handleBattProtection(void) {
	powerState state = pmu_checkBattVoltage();

	switch(state) {
	case POWER_CRITICAL:
		pmu_disablePower();
		break;
	case POWER_WARNING:
		led_turnOn(7);
		break;
	case POWER_OK:
		led_turnOn(6);
		pmu_forceEnablePower();
		break;
	};

	return state;
}


