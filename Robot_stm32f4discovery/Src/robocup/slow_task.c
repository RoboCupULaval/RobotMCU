#include "dribbler.h"

#include "slow_task.h"

#define NB_TICK_TO_ENABLE_SENSOR_CALIBRATION 5000

void slow_handleSensorCalibLed(void);
powerState slow_handleBattProtection(void);
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
		//Debug modee
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
		break;
	case POWER_WARNING:
		//led_turnOff(6);
		//led_turnOn(7);
		break;
	case POWER_OK:
	case POWER_OVERRIDE:
		//led_turnOn(6);
		//led_turnOff(7);
		pmu_forceEnablePower();
		break;
	};

	return state;
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
		dibbler_tmp_force_activation(0.35f);
	}
	previous_value = robot_isBtnPressed();
}

