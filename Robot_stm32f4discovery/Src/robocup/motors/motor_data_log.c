/*
 * motor_data_log.c
 *
 *  Created on: Nov 12, 2016
 *      Author: philippe
 */

#include "motor_data_log.h"

static char s_dataLineBuffer[400];
static size_t s_dataLineBufferLen = 0;

void motorDataLog_addWheelData(float reference, float feedback) {
	snprintf(s_dataLineBuffer + s_dataLineBufferLen, 255 - s_dataLineBufferLen, "%.5f|%.3f|", reference, feedback);
	s_dataLineBufferLen = strlen(s_dataLineBuffer);
}

void motorDataLog_addCloseLoopData(PidWheel_t* pPid) {
	snprintf(s_dataLineBuffer + s_dataLineBufferLen, 255 - s_dataLineBufferLen, "%.3f|%.3f|%.3f|%.3f|", pPid->e, pPid->r, pPid->fbk, pPid->output);
	s_dataLineBufferLen = strlen(s_dataLineBuffer);
}

void motorDataLog_flushDataLine(void){
	// Add line return at the end of buffer
	snprintf(s_dataLineBuffer + s_dataLineBufferLen, 255 - s_dataLineBufferLen, "\r\n");
	LOG_DATA(s_dataLineBuffer);
	// Reset position in buffer
	s_dataLineBufferLen = 0;
}
