

#include "chip_select_demux.h"

static Demux_Handle HandleDemux;

void demux_Init(GPIO_TypeDef *gpio, uint16_t a0, uint16_t a1, uint16_t a2, chip_select notConnect) {
	HandleDemux.gpio = gpio;
	HandleDemux.a0 = a0;      // mux select pins
	HandleDemux.a1 = a1;
	HandleDemux.a2 = a2;
	HandleDemux.notConnect_pin = notConnect;

    demux_Disconnect();
}

// this function activate the right combination of select pin for output from CS_0 to CS_7
void demux_ConnectTo(chip_select CS){
	if(CS == CS_0){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_RESET);
	}
	else if(CS == CS_1){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_RESET);
	}
	else if(CS == CS_2){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_RESET);
	}
	else if(CS == CS_3){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_RESET);
	}
	else if(CS == CS_4){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_SET);
	}
	else if(CS == CS_5){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_SET);
	}
	else if(CS == CS_6){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_SET);
	}
	else if(CS == CS_7){
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(HandleDemux.gpio, HandleDemux.a2, GPIO_PIN_SET);
	}
}

// this function use the unassigned pin when there is no communication
void demux_Disconnect(){
	demux_ConnectTo(HandleDemux.notConnect_pin);
}
