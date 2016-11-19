/*
 * led.h
 *
 *  Created on: 2016-11-17
 *      Author: Gagnon
 *            Handles communication with LED driver : IS31FL3199
 */

#ifndef ROBOCUP_LED_H_
#define ROBOCUP_LED_H_

#include "i2c.h"

#define LED_PWM				0xFF //100 %


#define LED_ADDRESS			200

#define LED_REG_SHUTDOWN	0x00
#define LED_REG_CTRL1		0x01 //0 OUT6 OUT5 OUT4 0 OUT3 OUT2 OUT1
#define LED_REG_CTRL2		0x02 //0 0    0    0    0 OUT9 OUT8 OUT7
#define LED_REG_CONFIG1		0x03 //
#define LED_REG_CONFIG2		0x04 // Current setting : D6:D4
#define LED_REG_PWM			0x07
#define LED_REG_LOAD_DATA	0x10

#define LED_CS_20mA			0x00
#define LED_CS_15mA			(0x01 << 4)
#define LED_CS_10mA			(0x02 << 4)
#define LED_CS_5mA			(0x03 << 4)


void led_init(void);
void led_turnOn(uint8_t ledId); // 0 to 8
void led_turnOff(uint8_t ledId);


#endif /* ROBOCUP_LED_H_ */
