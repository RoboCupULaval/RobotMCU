#include "usb.h"

// Buffer used for the rev
//static uint8_t s_usbRxBuffer[USB_MAX_PACKET_SIZE];

comHandle_t usb_init(){
	comHandle_t com;
	com.read = usb_read;
	com.write = usb_write;
	com.readUntilZero = usb_readUntilZero;
	return com;
}


size_t usb_read(void *pBuffer, size_t expectedLength){
	/*uint32_t revLen = 0;

	// We have no control on the length we receive
	CDC_Receive_FS(s_usbRxBuffer, &revLen);

	if(revLen > expectedLength) {
		for(;;); // TODO What do I do???
	}

	memcpy(pBuffer, s_usbRxBuffer, revLen);
	return revLen;*/

	for(;;) {}// Unimplemented
	return 0;
}

size_t usb_write(const void *pBuffer, size_t length){
	uint8_t res = CDC_Transmit_FS(pBuffer, length);
	return res == USBD_OK ? length : 0;
}

size_t usb_readUntilZero(void *pBuffer, size_t maxLength){
	/*uint32_t revLen = 0;

	CDC_Receive_FS(s_usbRxBuffer, &revLen);

	size_t lenUntilZero = strnlen(s_usbRxBuffer, maxLength);

	// No zero character in last packet
	if(lenUntilZero == maxLength) {
		return 0;
	}

	memcpy(pBuffer, s_usbRxBuffer, lenUntilZero);
	return lenUntilZero;
	*/

	for(;;) {}// Unimplemented
	return 0;
}
