/*
 * serialUsb.h
 *
 *  Created on: Apr 18, 2017
 *      Author: znuxor
 */

#ifndef ROBOCUP_USB_SERIALUSB_H_
#define ROBOCUP_USB_SERIALUSB_H_

#define APP_RX_DATA_SIZE  260
#define APP_TX_DATA_SIZE  260
#define CBPACKETNUMBER 16

typedef struct simpleCB {
	uint8_t dataTable[CBPACKETNUMBER][APP_TX_DATA_SIZE];
	int readIndex; // index of next item to read
	int writeIndex; // index of next item to write
} simpleCB;

#endif /* ROBOCUP_USB_SERIALUSB_H_ */
