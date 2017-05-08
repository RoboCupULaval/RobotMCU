#include "dribbler.h"

#include "slow_task.h"

powerState slow_handleBattProtection(void);

void slow_taskEntryPoint(void) {
	pmu_init();
	dribbler_init();
	led_init();
	kicker_init();
	ball_init();

	dribbler_setPWM(0.0f);

	if (robot_isDebug()) {
		led_swipingLedTest();
	}

	uint8_t id = robot_getPlayerID();
	for(;;) {
		//Debug modee
		if(robot_isDebug()) {
			led_turnOn(8);

			//ID selection
			led_turnOff(id);
			id = robot_getPlayerID();
			led_turnOn(id);
		}
		ball_updateADC();
		kicker_update();

		log_setBatteryVoltage(pmu_getBattVoltage());
		log_setCurrent(pmu_getCurrent());

		slow_handleBattProtection();

		dribbler_handleDribbler();

		HAL_Delay(20);
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
		led_turnOff(6);
		break;
	case POWER_OK:
		led_turnOn(6);
		led_turnOff(7);
		pmu_forceEnablePower();
		break;
	};

	return state;
}


