/*
 * ball_detector.h
 *
 *  Created on: 2017-04-05
 *      Author: Gagnon
 */

#ifndef ROBOCUP_BALL_DETECTOR_H_
#define ROBOCUP_BALL_DETECTOR_H_

#include "adc.h"
#include "led.h"

// With default position
// LED pas fix
#define BALL_MIN_ADC_VAL 700
#define BALL_MAX_ADC_VAL 1300

// Led bouger en diagonal
//#define BALL_MIN_ADC_VAL 900
//#define BALL_MAX_ADC_VAL 1800

// LED fix
//#define BALL_MIN_ADC_VAL 400
//#define BALL_MAX_ADC_VAL 1000


#define BALL_LED_STEP ((BALL_MAX_ADC_VAL - BALL_MIN_ADC_VAL) / LED_NUMBER)

//#define BALL_NB_LED_THAT_WAS_LIGHT_UP 5
//#define BALL_NB_LED_THAT_WAS_LIGHT_UP_DRIBBLE 4

// Note PB-2018-01-14:
// G01 400
// G02 1000-500=500, dibler 1000
// G03 1000-500=500 dibbler 800
// G04 *11/17 sur le sensor2, 1000-500=500 de limite

// G06 1550-500= 1050 et 900 pour dribbleur


typedef enum {
	BALL_NOBALL = 0,
	BALL_READY_TO_DRIBBLE,
	BALL_READY_TO_KICK
} BallState;

void ball_init(void);
void ball_updateADC(void);
BallState ball_getState(void);
uint32_t ball_getSensorValue(uint32_t sensorId);
uint32_t ball_getSensorsMeanValue(void);

uint32_t ball_kicker_threshold(void);
uint32_t ball_dribbling_threshold(void);

#endif /* ROBOCUP_BALL_DETECTOR_H_ */
