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

static comHandle_t s_logHandle;
static SemaphoreHandle_t s_logLock = NULL;
static volatile double s_batteryVoltage = 0.0;

void log_init(comHandle_t comInterface) {
	s_logHandle = comInterface;
	s_logLock = xSemaphoreCreateMutex();
}

void log_setBatteryVoltage(const double batteryVoltage) {
	s_batteryVoltage = batteryVoltage;
}

void log_broadcast(const char *pLogType, const char *pMessage){
	char metaData[MAX_METADATA_LEN];
	const TickType_t msSinceStartup = xTaskGetTickCount() * portTICK_PERIOD_MS;

	snprintf(metaData, MAX_METADATA_LEN, "%s|%06u|R%d|B%2.1f|", pLogType, (unsigned)msSinceStartup, ADDR_ROBOT, s_batteryVoltage);

	// Start of critical zone
	xSemaphoreTake(s_logLock, portMAX_DELAY);

	s_logHandle.write(metaData, strlen(metaData));
	s_logHandle.write(pMessage, strlen(pMessage));

	// End of critical zone
	xSemaphoreGive(s_logLock);

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

void LOG_DEBUG_AND_BUFFER(const char * pMessage, void * pBuffer, size_t length) {
	log_messageWithBufferDump("DEBUG", pMessage, pBuffer, length);
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
void LOG_DATA(const char * pMessage){
	log_broadcast("DATA", pMessage);
}

//Return 1 when in debug mode (switch), else no
uint8_t robot_isDebug(void) {
	return HAL_GPIO_ReadPin(DEBUG_SWITCH_GPIO_Port, DEBUG_SWITCH_Pin);
}

//Return 1 when btn is pressed
uint8_t robot_isBtnPressed(void) {
	return HAL_GPIO_ReadPin(SWITCH_INPUT_GPIO_Port, SWITCH_INPUT_Pin);
}

//Return robot ID (rotary switch)
uint8_t robot_getID(void) {
	uint8_t id = 0;

	id |= HAL_GPIO_ReadPin(ID_0_demux_0_GPIO_Port, ID_0_demux_0_Pin);
	id |= (uint8_t)(HAL_GPIO_ReadPin(ID_1_demux_1_GPIO_Port, ID_1_demux_1_Pin) << 1);
	id |= (uint8_t)(HAL_GPIO_ReadPin(ID_2_demux_2_GPIO_Port, ID_2_demux_2_Pin) << 2);

	return id;
}

void dribbler_init(void) {
  	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
}
//Speed : PWM = 0 to 1.0
// todo: add check on input
void dribbler_setPWM(float speed) {
	uint32_t pwmTimerValue = (uint32_t)(speed * 65535.0f);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, pwmTimerValue);
}
