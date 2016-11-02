/*
 * util.c
*/
#include "cmsis_os.h"
#include "semphr.h"
#include "queue.h"

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

static SemaphoreHandle_t mutex = NULL;

void log_init() {
	mutex = xSemaphoreCreateMutex();
}


void log_broadcast(const char *pLogType, const char *pMessage){
	char metaData[MAX_METADATA_LEN];
	const TickType_t msSinceStartup = xTaskGetTickCount() * portTICK_PERIOD_MS;

	snprintf(metaData, MAX_METADATA_LEN, "%s|%06u|R%d|", pLogType, (unsigned)msSinceStartup, ADDR_ROBOT);

	// Start of critical zone
	xSemaphoreTake(mutex, portMAX_DELAY);

	g_logHandle.write(metaData, strlen(metaData));
	g_logHandle.write(pMessage, strlen(pMessage));

	// End of critical zone
	xSemaphoreGive(mutex);

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
