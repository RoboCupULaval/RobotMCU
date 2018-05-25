#include "dribbler.h"

#include "slow_task.h"

powerState slow_handleBattProtection(void);
void slow_updatePowerIndicators(void);
slow_turnOnLeds(uint8_t number_of_leds_on);
void slow_turnOffLeds(uint8_t first_led_off);

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
		slow_turnOnLeds(1);
		slow_turnOffLeds(2);
		break;
	case POWER_OK:
		slow_updatePowerIndicators();
		pmu_forceEnablePower();
		break;
	};

	return state;
}

void slow_updatePowerIndicators(void) {
	double battery_voltage 			   = pmu_getBattVoltage();
	double battery_voltage_no_offset   = battery_voltage - PMU_BATT_WARNING_TRESHOLD;
	double battery_increment 		   = battery_voltage_no_offset / SLOW_TOTAL_NUMBER_OF_LEDS;

	uint8_t first_led_off 		       = battery_voltage_no_offset / battery_increment;
	uint8_t number_of_leds_on          = first_led_off - 1;

	slow_turnOnLeds(number_of_leds_on);
	slow_turnOffLeds(first_led_off);
}

void slow_turnOnLeds(uint8_t number_of_leds_on) {
	for (int i = 1; i <= number_of_leds; ++i) {
		led_turnOn(i);
	}
}

// first_led_off: the first led that is off
void slow_turnOffLeds(uint8_t first_led_off) {
	for (int i = first_led_off; i <= SLOW_TOTAL_NUMBER_OF_LEDS; ++i) {
		led_turnOff(i);
	}
}
