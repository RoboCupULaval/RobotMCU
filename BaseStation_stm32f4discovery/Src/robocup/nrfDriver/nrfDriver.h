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

// Initializes the nrf peripheral.
void nrfInit();

// Sets the desired destination.
// Inputs:
//   robotNumber -- The number of the destination robot.
void nrfSetRobotTX(uint8_t robotNumber);

// Sends data using the nrf peripheral.
// Inputs:
//   dataOut -- A pointer to the data to be sent.
// Note: This function is blocking.
int nrfSend(uint8_t * dataOut);

// Receives data from the nrf peripheral.
// Inputs:
//   dataIn -- A pointer to where to store the data.
// Note: You must use nrfReceiveReady to check if there is a packet before.
void nrfReceive(uint8_t * dataIn);

// Fetches the nrf retransmit count.
// Return value: the retransmit count
uint8_t nrfRetransmitCount();

// Fetches the nrf status word.
// Return value: the nrf status word
uint8_t nrfGetStatus();

// Checks if the nrf peripheral has received a packet.
// Returns True if there is a packet waiting.
bool nrfReceiveReady(void);


#endif /* NRFDRIVER_NRFDRIVER_H_ */
