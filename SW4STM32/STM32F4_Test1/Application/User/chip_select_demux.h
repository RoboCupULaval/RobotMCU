/*
 * CS_demux.h
 *
 *  Created on: 2014-01-09
 *      Author: Philippe Babin
 */

#ifndef DEMUX_DRIVER_H_
#define DEMUX_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"

typedef enum{
	CS_0,
	CS_1,
	CS_2,
	CS_3,
	CS_4,
	CS_5,
	CS_6,
	CS_7
} chip_select;

typedef struct Demux_Handle {
	GPIO_TypeDef gpio;
	uint16_t a0;
	uint16_t a1;
	uint16_t a2;
	chip_select notConnect_pin;
}Demux_Handle;

/*******************************************************************************
 * User Interface Function
 *******************************************************************************/

void demux_Init(GPIO_TypeDef gpio, uint16_t a0, uint16_t a1, uint16_t a2, chip_select notConnect);
void demux_ConnectTo(chip_select CS);
void demux_Disconnect();


#endif /* DEMUX_DRIVER_H_ */
