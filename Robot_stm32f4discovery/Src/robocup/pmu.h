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

#include <stdbool.h>

#include "robocup_define.h"
#include "gpio.h"
#include "i2c.h"


#define SHUNT_RESISTANCE 0.06
#define PMU_VOLTAGE_LSB				0.004 // V
// The following comment are true, but we don't use it for fetching the current
// we use the shunt voltage instead
// See p.12 of the datasheet of INA219
// Max experted current = 10A (fuse limit)
// Rshunt = 0.06 ohm
// cal = 0.04096*2^(15) / (Maximum experted current x Rshunt)   <-- equation 1
#define PMU_CURRENT_CALIBRATION		2236
// CURRENT_LSB = max expected / (2^15)                          <-- equation 2
// We multiply it by 100 to have mA. Why 100 and not 1000?
// For an unknown reason, the register divide by 10 internally
#define PMU_CURRENT_LSB				0.030517 // mA/bit

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

void pmu_overrideProtection(void);
void pmu_resetProtection(void);

#endif /* ROBOCUP_PMU_H_ */
