/*
 * quad_driver.c
 *
 *  Created on: 2013-11-08
 *      Author: Mathieu Garon
 */


#include "quad_driver.h"
#include "chip_select_demux.h"

quad_Handle quad_Init(chip_select pCSNPin){
	quad_Handle lHandle;
	lHandle.structCSNPin = pCSNPin;
	lHandle.count0 = 0;
	lHandle.count1 = 0;
	lHandle.delta_count0 = 0;
	lHandle.delta_count1 = 0;
    quad_WriteRegister(QUAD_CONFIG0, 0x07, &lHandle);  //counter0 = 16 bits and counter1 = 16 bit (no counter2)
    quad_ReadRegister(QUAD_CONFIG0, &lHandle);  // counter TTL
    quad_WriteRegister(QUAD_CONFIG1, 0x80, &lHandle);  // counter TTL
    quad_ReadRegister(QUAD_CONFIG1, &lHandle);  // counter TTL

    // Init count with the value in the encoder register
    quad_ReadCounters(&lHandle);
    return lHandle;
}

uint16_t quad_ReadRegister(uint16_t pReg,quad_Handle *pQuad){
	uint16_t answer = 0;
	demux_ConnectTo(pQuad->structCSNPin);
	SPI_write_8bits(pReg | QUAD_READ); //put a 1 on the first
	answer = SPI_read();
	demux_Disconnect();
	return answer;
}

void quad_WriteRegister(uint8_t pReg, uint8_t pValue,quad_Handle *pQuad){
	demux_ConnectTo(pQuad->structCSNPin);
	SPI_write_8bits(pReg & QUAD_WRITE); //put a 0 on the msb to signify a write
	SPI_write_8bits(pValue);
	demux_Disconnect();
}


void quad_ReadCounters(quad_Handle *pQuad){
	uint8_t cnt2_msb, cnt2_lsb, cnt1_msb, cnt1_lsb, cnt0_msb, cnt0_lsb;

	demux_ConnectTo(pQuad->structCSNPin);
	SPI_write_8bits((QUAD_COUNTER) | QUAD_READ); // For some reason the first 2 bytes are unused
	cnt2_msb = SPI_read();
	cnt2_lsb = SPI_read();
	cnt1_msb = SPI_read();
	cnt1_lsb = SPI_read();
	cnt0_msb = SPI_read();
	cnt0_lsb = SPI_read();
	demux_Disconnect();

	const int16_t old_count0 = pQuad->count0;
	const int16_t old_count1 = pQuad->count1;

	const int16_t count2  = (cnt2_msb << 8) | cnt2_lsb;		 // not used
	pQuad->count0 = (cnt1_msb << 8) | cnt1_lsb;
	pQuad->count1 = (cnt0_msb << 8) | cnt0_lsb;

	pQuad->delta_count0 = pQuad->count0 - old_count0;
	pQuad->delta_count1 = pQuad->count1 - old_count1;

	static char buffer[128];
	//snprintf(buffer, 128, "%6i %6i %6i ", count2, pQuad->count0, pQuad->count1);
	snprintf(buffer, 128, "%+6i %+6i ", pQuad->delta_count0, pQuad->delta_count1);
	//Debug_Print(buffer);

//	quad_WriteRegister( QUAD_CTRL, QUAD_RESETCNT0 | QUAD_RESETCNT1 | QUAD_RESETCNT2,pQuad); //reset counters

//	quad_CalculateSpeed(pQuad);
}

void quad_CalculateSpeed(quad_Handle *pQuad){
//	float lDistance0 = _IQ(pQuad->Count0);
	//float lDistance1 = _IQ(pQuad->Count1);
//	pQuad->wheelVelocity[0] = lDistance0 * HandleRobot.robotParam.speedFactor;
	//pQuad->wheelVelocity[1] = lDistance1 * HandleRobot.robotParam.speedFactor;
}

void quad_DisplayCounters(quad_Handle *pQuad){
	//sprintf(buffer,"count0 =%d count1 =%d\n\r",pQuad->count0,pQuad->count1);
	//HAL_UART_Transmit_IT(&huart2,(uint8_t*)buffer, strlen(buffer));
}

// TODO Change to log
void quad_DisplayVelocity(quad_Handle *pQuad){
	char buffer[128];
	sprintf(buffer,"wheel0 =%f wheel1 =%f cm/10ms\n\r",pQuad->wheelVelocity[0],
			pQuad->wheelVelocity[1]);
}

bool quad_Test(quad_Handle *pQuad){
	uint16_t temp = quad_ReadRegister(QUAD_CONFIG1, pQuad);  // if initialised before!
	return temp == 0x80;
}
