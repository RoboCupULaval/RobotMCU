/*
 * log.h
 *
 *  Created on: Mar 20, 2017
 *      Author: philippe
 */

#ifndef ROBOCUP_LOG_H_
#define ROBOCUP_LOG_H_

#include "hermes/com_interfaces/com_interface.h"

#define MAX_METADATA_LEN 128

void log_init(comHandle_t comInterface);
void log_setBatteryVoltage(const double batteryVoltage);
void log_setCurrent(const double current);
void log_metadata(void);
void LOG_INFO(const char * pMessage);
void LOG_ERROR(const char * pMessage);
void LOG_DEBUG(const char * pMessage);
void LOG_DATA(const char * pMessage);
void LOG_INFO_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length);
void LOG_ERROR_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length);
void LOG_DEBUG_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length);

#endif /* ROBOCUP_LOG_H_ */
