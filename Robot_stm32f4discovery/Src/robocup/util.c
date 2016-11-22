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
	id |= (HAL_GPIO_ReadPin(ID_1_demux_1_GPIO_Port, ID_1_demux_1_Pin) << 1);
	id |= (HAL_GPIO_ReadPin(ID_2_demux_2_GPIO_Port, ID_2_demux_2_Pin) << 2);

	return id;
}

void dribbler_init(void) {
  	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
}
//Speed : PWM = 0 to 1.0
void dribbler_setPWM(float speed) {
	int pwm = (int)(speed * 65535.0f);
  	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, pwm);
}
