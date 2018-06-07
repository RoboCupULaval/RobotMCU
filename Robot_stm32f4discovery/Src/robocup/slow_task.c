#include "dribbler.h"

#include "slow_task.h"

#define NB_TICK_TO_ENABLE_SENSOR_CALIBRATION 5000

void slow_handleSensorCalibLed(void);
powerState slow_handleBattProtection(void);
void slow_updatePowerIndicators(void);
void slow_updatePowerWarning(uint16_t number_of_iterations);
void slow_turnOnLeds(uint8_t number_of_leds_on);
void slow_turnOffLeds(uint8_t first_led_off);
void slow_secret_force_kick(void);

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

	uint32_t time_of_last_button_low = xTaskGetTickCount();
	bool sensor_calib_enable = false;
	uint8_t id = robot_getPlayerID();

	unsigned loop_cnt = 0;
	for(;;) {
		//Debug mode
		if(robot_isDebug()) {
			led_turnOn(8);

			//ID selection
			led_turnOff(id);
			id = robot_getPlayerID();
			led_turnOn(id);
		} else {
			if (robot_isBtnPressed()) {
				if (xTaskGetTickCount() - time_of_last_button_low > NB_TICK_TO_ENABLE_SENSOR_CALIBRATION) {
					sensor_calib_enable = true;
				}
			} else {
				time_of_last_button_low = xTaskGetTickCount();
			}
		}

		slow_secret_force_kick();

		ball_updateADC();
		kicker_update();

		log_setBatteryVoltage(pmu_getBattVoltage());
		log_setCurrent(pmu_getCurrent());

		slow_handleBattProtection();

		//LOG_INFO("Enter dribler test \r\n");
		dribbler_handleDribbler();
		//LOG_INFO("Leave dribler test \r\n");
		//if (loop_cnt > 1000)
		//LOG_INFO("Enter calib test \r\n");
		if (loop_cnt % 2 == 0 && sensor_calib_enable) {
			//LOG_INFO("in cnt \r\n");
			slow_handleSensorCalibLed();
		}
		//if (loop_cnt > 1000)
		//		LOG_INFO("Leave calib test \r\n");

		HAL_Delay(20);
		loop_cnt++;
	}
}


//Automatically reads batt voltage and decides if the power should be disable
//Returns the power state
powerState slow_handleBattProtection(void) {
	powerState state = pmu_checkBattVoltage();

	switch(state) {
	case POWER_CRITICAL:
		pmu_disablePower();
		slow_updatePowerWarning(SLOW_CRITICAL_LED_FLASH);
		break;
	case POWER_WARNING:
		slow_updatePowerWarning(SLOW_WARNING_LED_FLASH);
		break;
	case POWER_OK:
		slow_updatePowerIndicators();
		pmu_forceEnablePower();
		break;
	case POWER_OVERRIDE:
	default:
		while(1);
	};

	return state;
}

void slow_updatePowerIndicators(void) {
	static uint8_t last_nb_leds_on     = 100;
	static uint16_t nb_iterations_hyst = 0;
	double batt_voltage 			   = pmu_getBattVoltage();
	double batt_voltage_max_no_offset  = SLOW_BATT_MAX - PMU_BATT_WARNING_TRESHOLD;
	double batt_voltage_no_offset      = batt_voltage - PMU_BATT_WARNING_TRESHOLD;
	double batt_increment 		   	   = batt_voltage_max_no_offset / LED_NUMBER;

	uint8_t nb_leds_on   			   = (uint8_t)(batt_voltage_no_offset / batt_increment);
	uint8_t first_led_off          	   = (uint8_t)(nb_leds_on + 1);
	if (nb_leds_on == 0)
		slow_updatePowerWarning(SLOW_ZERO_LED_FLASH);
	else if (last_nb_leds_on != nb_leds_on) {
		if ((nb_iterations_hyst < SLOW_HYSTERESIS_ITERATIONS) && last_nb_leds_on != 100) {
			++nb_iterations_hyst;
		} else {
			slow_turnOnLeds(nb_leds_on);
			slow_turnOffLeds(first_led_off);
			nb_iterations_hyst = 0;
		}
	}
	last_nb_leds_on = nb_leds_on;
}

void slow_updatePowerWarning(uint16_t number_of_iterations) {
	static uint32_t iterations_count = 0;
	static bool led_is_open = false;
	if (iterations_count < number_of_iterations)
		++iterations_count;
	else {
		if (led_is_open) {
			led_turnOff(0);
			led_is_open = false;
		} else {
			led_turnOn(0);
			led_is_open = true;
		}
		iterations_count = 0;
	}
}

void slow_turnOnLeds(uint8_t number_of_leds_on) {
	for (uint8_t i = 0; i <= number_of_leds_on; ++i) {
		led_turnOn(i);
	}
}


// first_led_off: the first led that is off
void slow_turnOffLeds(uint8_t first_led_off) {
	for (uint8_t i = first_led_off; i <= LED_NUMBER; ++i) {
		led_turnOff(i);
	}
}

void slow_handleSensorCalibLed(void) {
	uint32_t val = ball_getSensorsMeanValue();

	val = val > BALL_MAX_ADC_VAL ? BALL_MAX_ADC_VAL : val;
	val = val < BALL_MIN_ADC_VAL ? BALL_MIN_ADC_VAL : val;
	uint32_t nb_led = (val - BALL_MIN_ADC_VAL) / BALL_LED_STEP;

	for (unsigned i = 0; i < LED_NUMBER; ++i) {
		if (i < nb_led) {
			led_turnOn(i > 4 ? i+1 : i);
		} else {
			led_turnOff(i > 4 ? i+1 : i);
		}
	}
}

void slow_secret_force_kick(void) {
	static bool previous_value = false;

	if (robot_getPlayerID() == 0 && previous_value && !robot_isBtnPressed() && robot_isDebug()) {
		kicker_force_kick(10);
	}
	previous_value = robot_isBtnPressed();
}
