/*
 * nrfDriver.h
 *
 *  Created on: Nov 18, 2016
 *      Author: znuxor
 */

#ifndef NRFDRIVER_NRFDRIVER_H_
#define NRFDRIVER_NRFDRIVER_H_

#include "stm32f4xx.h"
#include <stdbool.h>


#define PACKET_SIZE 23
#define NRF_DEFAULT_RF_CH	100
#define NRF_REG_RF_CH		0x05

void nrfInit(const uint8_t robotId);
void nrfSetRobotTX(uint8_t robotNumber);
void nrfSend(uint8_t * dataOut);
void nrfReceive(uint8_t * dataIn);
uint8_t nrfRetransmitCount(void);
uint8_t nrfGetStatus(void);
bool nrfVerifySPI(void);

#endif /* NRFDRIVER_NRFDRIVER_H_ */
