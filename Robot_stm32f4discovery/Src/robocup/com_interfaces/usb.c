#include "usb.h"

//#define ACTIVATE_USB


comHandle_t usb_init(void){
	//MX_USB_DEVICE_Init();

	comHandle_t com;
	com.read = usb_read;
	com.write = usb_write;
	com.readUntilZero = usb_readUntilZero;
	return com;
}


size_t usb_read(__attribute__ ((unused)) void *pBuffer,
		        __attribute__ ((unused)) size_t expectedLength){
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
#ifdef ACTIVATE_USB
	uint16_t length16b = length & 0xFFFF;
	uint8_t res;
	do {
		res = CDC_Transmit_FS((uint8_t*)pBuffer, length16b);
	} while(res == USBD_BUSY);
	return res == USBD_OK ? length16b : 0;
#endif
}

size_t usb_readUntilZero(__attribute__ ((unused)) void *pBuffer,
		                 __attribute__ ((unused)) size_t maxLength){
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
