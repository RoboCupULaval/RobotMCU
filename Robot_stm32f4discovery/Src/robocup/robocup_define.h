/*
 * robocup_define.h
 *
 *  Created on: 2016-05-28
 *      Author: Gagnon
 */

#ifndef ROBOCUP_ROBOCUP_DEFINE_H_
#define ROBOCUP_ROBOCUP_DEFINE_H_

#include "mxconstants.h"
#include "chip_select_demux.h"
#include "quad_driver.h"
#include "hermes/com_interface.h"

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;


// TODO find a way more elegant way to share interface and global variable
/***
 *  Global Variable
 */
typedef struct {
	comHandle_t com;
} hermesHandle_t;
extern hermesHandle_t g_hermesHandle;

//extern quad_Handle quadA;




#endif /* ROBOCUP_ROBOCUP_DEFINE_H_ */
