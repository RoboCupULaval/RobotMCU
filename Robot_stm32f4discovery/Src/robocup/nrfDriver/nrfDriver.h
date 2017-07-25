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

#define NRF_DEFAULT_RF_CH	100
#define NRF_REG_RF_CH		0x05

void nrfInit(const size_t packetSize, const uint8_t);
void nrfSend(uint8_t * dataOut);
void nrfReceive(uint8_t * dataIn);
uint8_t nrfRetransmitCount(void);
uint8_t nrfGetStatus(void);
bool nrfVerifySPI(void);

#endif /* NRFDRIVER_NRFDRIVER_H_ */
