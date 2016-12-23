/*
 * pmu.h
 *
 *  Created on: 2016-11-17
 *      Author: Gagnon
 *      Power Management Unit : Checking batt voltage
 *      + power consumption using INA129 (I2C device)
 *      + disabling/enabling power to motors
 */

#ifndef ROBOCUP_PMU_H_
#define ROBOCUP_PMU_H_

#include "robocup_define.h"
#include "gpio.h"
#include "i2c.h"

#define PMU_CURRENT_CALIBRATION		164 // Look at INA219 datasheet
#define PMU_CURRENT_LSB				0.5 //mA
#define PMU_VOLTAGE_LSB				0.004 //V

//
#define PMU_ADDRESS				0b10000000

#define PMU_REG_CONFIG			0x00
#define PMU_REG_SHUNT_VOLT		0x01
#define PMU_REG_BUS_VOLT		0x02
#define PMU_REG_POWER			0x03
#define PMU_REG_CURRENT			0x04
#define PMU_REG_CALIB			0x05

void pmu_init(void);

double pmu_getBattVoltage(void);
double pmu_getCurrent(void);

uint8_t pmu_enablePower(void);
uint8_t pmu_forceEnablePower(void);
uint8_t pmu_disablePower(void);
uint8_t pmu_isPowerEnabled(void);

powerState pmu_checkBattVoltage(void);
powerState pmu_handleBattProtection(void);//Call this as frequently as possible!

#endif /* ROBOCUP_PMU_H_ */
