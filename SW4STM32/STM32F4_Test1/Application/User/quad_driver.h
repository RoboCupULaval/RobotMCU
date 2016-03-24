/*
 * quad_driver.h
 *
 *  Created on: 2013-11-08
 *      Author: Mathieu Garon
 */

#ifndef QUAD_DRIVER_H_
#define QUAD_DRIVER_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CS_demux.h"
#include "spi_wrapper.h"
#include "stm32f4xx_hal.h"

/****************************************************************************
 *   MD quadrature decoder Register
 *****************************************************************************/
static const uint16_t QUAD_CONFIG0 = 0x00u;
static const uint16_t QUAD_CONFIG1 = 0x01u;
static const uint16_t QUAD_CONFIG2 = 0x02u;
static const uint16_t QUAD_CONFIG3 = 0x03u;
static const uint16_t QUAD_CONFIG4 = 0x04u;
static const uint16_t QUAD_CTRL    = 0x30u;    //mainly used to set counter to zero
static const uint16_t QUAD_COUNTER = 0x08u;
/****************************************************************************
 *   MD quadrature decoder Command
 *****************************************************************************/
static const uint16_t QUAD_RESETCNT0 = 0x01u;  // used with CTRL register to reset counter
static const uint16_t QUAD_RESETCNT1 = 0x02u;
static const uint16_t QUAD_RESETCNT2 = 0x04u;
static const uint16_t QUAD_READ	     = 0x80u;  //these two are probably not used
static const uint16_t QUAD_WRITE     = ~0x80u; //modification needed

typedef struct quad_Handle {
	chip_select structCSNPin;
	int16_t Count0;
	int16_t Count1;
	float wheelVelocity[2];
}quad_Handle;

quad_Handle quad_init(chip_select pCSNPin);
uint16_t quad_readRegister(uint16_t pReg,quad_Handle *pQuad);
void quad_WriteRegister(uint16_t pReg, uint16_t pValue,quad_Handle *pQuad);
void quad_readCounters(quad_Handle *pQuad);
void quad_calculateSpeed(quad_Handle *pQuad);

void quad_displayCounters(quad_Handle *pQuad);
void quad_displayVelocity(quad_Handle *pQuad);

bool quad_test(quad_Handle *pQuad);

#endif /* QUAD_DRIVER_H_ */
