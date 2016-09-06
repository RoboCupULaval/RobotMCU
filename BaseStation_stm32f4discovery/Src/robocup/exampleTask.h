/*
 * CS_demux.h
 *
 *  Created on: 2014-01-09
 *      Author: Philippe Babin
 */

#ifndef SAMPLE_TASK_H_
#define SAMPLE_TASK_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

/*******************************************************************************
 * User Interface Function
 *******************************************************************************/

void exampleTaskBlinkRed(void * pvParameters);
void exampleTaskBlinkBlue(void * pvParameters);


#endif /* DEMUX_DRIVER_H_ */
