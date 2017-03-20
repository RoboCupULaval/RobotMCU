/*
 * nrfDriver.h
 *
 *  Created on: Nov 18, 2016
 *      Author: znuxor
 */

#ifndef NRFDRIVER_NRFDRIVER_H_
#define NRFDRIVER_NRFDRIVER_H_

#include <stm32f4xx.h>
#include <stdbool.h>

void nrfInit();
void nrfSend(uint8_t * dataOut);//, bool forceRetryBool);
void nrfReceive(uint8_t * dataIn);
uint8_t nrfRetransmitCount();
uint8_t nrfGetStatus();
bool nrfReceiveReady(void);

#endif /* NRFDRIVER_NRFDRIVER_H_ */
