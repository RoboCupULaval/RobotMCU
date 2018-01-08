/*
 * serialUsb.c
 *
 *  Created on: Apr 18, 2017
 *      Author: znuxor
 */

#include "stm32f4xx.h"
#include "serialUsb.h"
#include "usbd_cdc_if.h"

/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */


volatile simpleCB myCircularBuffer;

// This function reads a single cobs-encoded packet that was previously read through USB
// It returns 0 if success. If no packet, then it returns -1
int SerialRead(uint8_t* dataBuffer) {
	// check if there is a packet available
	// copy the indexes
	const int currReadIndex = myCircularBuffer.readIndex;
	const int currWriteIndex = myCircularBuffer.writeIndex;
	if (currReadIndex == currWriteIndex) {
		return -1;
	}
	else {
		// careful: a packet reception might happen anywhere in this function!

		// copy the packet into the buffer, must be cobs-encoded!!!
		strcpy((char *) dataBuffer, (char *) myCircularBuffer.dataTable[currReadIndex]);

		if (strlen(myCircularBuffer.dataTable[currReadIndex]) + 1u  != myCircularBuffer.lenTable[currReadIndex]) {
			volatile size_t foo;
			foo++;
		}

		// check if we need to upgrade the read index
		myCircularBuffer.readIndex = (myCircularBuffer.readIndex + 1) % CBPACKETNUMBER;
		return 0;
	}
}

// This function writes a single (preferably) cobs-encoded packet and sends it through USB
uint8_t SerialWrite(uint8_t* Buf, size_t Len) {
	return CDC_Transmit_FS(Buf, Len);
}
