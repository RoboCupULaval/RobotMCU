/*
 * util.c
*/
#include "cmsis_os.h"
#include "util.h"

// Convert a series of bytes in a human readable format.
// The output buffer is expected to be 3 times the length of the input buffer.
// Ex: 0xDEADBEEF => de:ad:be:ef:
void convertBytesToStr(const void * ptr, size_t len, char* str){
  uint8_t *bytes = (uint8_t *)ptr;
  for(unsigned i = 0; i < len; i++){
    sprintf(str, "%02x:", bytes[i]);
    str += 3;
  }
  *str = '\0';
}

void log_broadcast(const char *pLogType, const char *pMessage){
	static char metaData[MAX_METADATA_LEN];
	TickType_t msSinceStartup = xTaskGetTickCount() * portTICK_PERIOD_MS;

	snprintf(metaData, MAX_METADATA_LEN, "%s|%06u|R%d|", pLogType, (unsigned)msSinceStartup, ADDR_ROBOT);

	g_logHandle.write(metaData, strlen(metaData));
	g_logHandle.write(pMessage, strlen(pMessage));
}


void LOG_INFO(const char * pMessage){
	log_broadcast("INFO", pMessage);
}
void LOG_ERROR(const char * pMessage){
	log_broadcast("ERROR", pMessage);
}
void LOG_DEBUG(const char * pMessage){
	log_broadcast("DEBUG", pMessage);
}
