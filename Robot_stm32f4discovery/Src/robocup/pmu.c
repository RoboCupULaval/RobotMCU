/*
 * pmu.c
 *
 *  Created on: 2016-11-17
 *      Author: Gagnon
 *
 *      Power Management Unit : Checking batt voltage
 *      + power consumption using INA129 (I2C device)
 *      + disabling/enabling power to motors
 */

#include "pmu.h"

static bool s_protectionOverrided = false;

//Init I2C device + enable power if batt voltage OK
void pmu_init(void) {
	pmu_disablePower();

	//Init I2C device...
	uint8_t data[2]; //16 bits registers
	data[0] = 0b11001111; //Shunt and bus continuous + shunt 12 bits average on 2 samples
	data[1] = 0b00111100; //bus voltage 12 bits average on 2 samples
	I2C_write(PMU_ADDRESS, PMU_REG_CONFIG, data, 2);

	data[1] = ((PMU_CURRENT_CALIBRATION >> 8) & 0xFF);
	data[0] = (PMU_CURRENT_CALIBRATION & 0xFF);
	I2C_write(PMU_ADDRESS, PMU_REG_CALIB, data, 2);

	pmu_enablePower(); //Enables if POWER_OK
	pmu_enablePower(); //Repeat because first measure from INA is always 0
}

//Returns voltage in V
double pmu_getBattVoltage(void) {
	uint8_t data[2];
	I2C_read(PMU_ADDRESS, PMU_REG_BUS_VOLT, data, 2);

	double value = (double)(((data[0] << 8) + data[1]) >> 3) * PMU_VOLTAGE_LSB;

	return value;
}

//Returns current consumption in mA
double pmu_getCurrent(void) {
	uint8_t data[2];
	I2C_read(PMU_ADDRESS, PMU_REG_CURRENT, data, 2);

	double value = (double)((data[0] << 8) + data[1]) * PMU_CURRENT_LSB;

	return value;
}

//Manually enables motors power if PowerStatus is OK
//Returns 1 if power enabled
uint8_t pmu_enablePower(void) {
	if (pmu_checkBattVoltage() == POWER_OK) {
		HAL_GPIO_WritePin(EN_POWER_GPIO_Port, EN_POWER_Pin, GPIO_PIN_SET);
	}
	return pmu_isPowerEnabled();
}

//FORCE enables motors power w/o checking batt voltage
//USE WITH CAUTION
//Returns 1 if power enabled
uint8_t pmu_forceEnablePower(void) {
	HAL_GPIO_WritePin(EN_POWER_GPIO_Port, EN_POWER_Pin, GPIO_PIN_SET);
	return pmu_isPowerEnabled();
}

//Manually disables motors power
//Returns 0 if power disabled
uint8_t pmu_disablePower(void) {
	HAL_GPIO_WritePin(EN_POWER_GPIO_Port, EN_POWER_Pin, GPIO_PIN_RESET);
	return pmu_isPowerEnabled();
}

//Returns 1 if power is enable, else 0
uint8_t pmu_isPowerEnabled(void) {
	return HAL_GPIO_ReadPin(EN_POWER_GPIO_Port, EN_POWER_Pin);
}

//Automatically reads batt voltage and deduces the power state
//Returns the power state
powerState pmu_checkBattVoltage(void) {
	if(s_protectionOverrided)
		return POWER_OVERRIDE;
	double battVoltage = pmu_getBattVoltage();
	if (battVoltage < PMU_BATT_SHUTDOWN_TRESHOLD) {
		return POWER_CRITICAL;
	}
	else if (battVoltage < PMU_BATT_WARNING_TRESHOLD) {
		return POWER_WARNING;
	}
	else {
		return POWER_OK;
	}
}

void pmu_overrideProtection(void){
	s_protectionOverrided = true;
}

void pmu_resetProtection(void){
	s_protectionOverrided = false;
}

