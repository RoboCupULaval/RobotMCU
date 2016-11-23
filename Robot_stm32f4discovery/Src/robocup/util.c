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

void log_init(void) {
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

void log_messageWithBufferDump(const char *pLogType, const char * pMessage, void * pBuffer, size_t length) {
	char bufferHumanReadable[3*100]; // For each byte, three character needed
	char messageAndBuffer[3*100+30];

	// Since we don't do dynamic allocation we need set a few limits
	if(length >= 100)
		length = 100;
	if(strlen(pMessage) > 30) {
		log_broadcast("ERROR", "log_messageWithBufferDump() does allow long message(>30) to be send out.");
		return;
	}
	convertBytesToStr(pBuffer, length, bufferHumanReadable);

	sprintf(messageAndBuffer, "%s %s\r\n", pMessage, bufferHumanReadable);
	log_broadcast(pLogType, messageAndBuffer);
}

void LOG_INFO_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length) {
	log_messageWithBufferDump("INFO", pMessage, pBuffer, length);
}

void LOG_ERROR_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length) {
	log_messageWithBufferDump("ERROR", pMessage, pBuffer, length);
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
