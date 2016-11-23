/*
 * util.h
 *
 *  Created on: Jun 26, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_UTIL_H_
#define ROBOCUP_UTIL_H_


#include "robocup_define.h"

#define MAX_METADATA_LEN 128

void log_init(void);
void LOG_INFO(const char * pMessage);
void LOG_ERROR(const char * pMessage);
void LOG_DEBUG(const char * pMessage);
void LOG_INFO_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length);
void LOG_ERROR_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length);
void convertBytesToStr(const void * ptr, size_t len, char* str);


#endif /* ROBOCUP_UTIL_H_ */
