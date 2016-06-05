
#include "hermes.h"

// This is the file containing everything about communication

static const int BUFFERSIZE = 32; // maximum size for the nrf

struct packetHeaderStruct {
	char protocolVersion;
	char srcAddress;
	char destAddress;
	char packetType;
	char checksum;
};

// This is the main task, it is intended to run indefinitely
void hermesTask(void * pvParameters) {
	int accumulatedBytes = 0; // number of bytes accumulated before 0 reached
	unsigned char packetBuffer[BUFFERSIZE];
	unsigned char dataBuffer[BUFFERSIZE+2];
	packetHeaderStruct *currentPacketHeaderPtr;
	int packetIsCorrect = 1;
    int sizeOfTheData = -1;
	while (1)
	  {
        accumulatedBytes = 0;
        // Get data from device

		// The data is treated
        decobifyData(packetBuffer, dataBuffer, accumulatedBytes);


        // we "extract" the packet header
        // This is done here because we need the size for the checksum.
        currentPacketHeaderPtr = (packetHeaderStruct *) dataBuffer;
        sizeOfTheData = dataSizeArray[(*currentPacketHeaderPtr).packetType];
        //TODO
        // here the checksum is computed,
        // if wrong, send a warning packet to control tower





	  }
}

// This function creates a cobified copy of the Data
// It is the responsibility of the used to have enough space in the cobifiedData array
// (It takes 2 additionnal bytes.)
void cobifyData(const unsigned char *originalData,
		        unsigned char *cobifiedData, unsigned long originalNumberOfBytes) {

	const unsigned char *originalDataEnd = originalData + originalNumberOfBytes;
	unsigned char *byteToWrite = cobifiedData++; // we don't write at the first byte
	unsigned char code = 0x01;

	while (originalData < originalDataEnd) {
		// if it is a zero, write the jump number
		if (*originalData == 0) {
			*byteToWrite = code;
		    byteToWrite = cobifiedData;
		    cobifiedData++;
			code = 0x01;
		}
		// else, write the usual data
		else {
			*cobifiedData = *originalData;
			cobifiedData++;
			code++; // the number of bytes since 0, + 1
			// in case we reach 255 bytes
			if (code == 0xFF) {
				*byteToWrite = code;
			    byteToWrite = cobifiedData;
			    cobifiedData++;
				code = 0x01;
			}

		}
		originalData++;
	}

	// The final block is written
	*byteToWrite = code;
    byteToWrite = cobifiedData;
    cobifiedData++;
	code = 0x01;

	// the final 0 is written
	*cobifiedData = 0;
}

// This function makes a decobified copy of the original Data
void decobifyData(const unsigned char *originalData,
				  unsigned char *decobifiedData,
		          unsigned long numberOfBytes)
{
	const unsigned char *originalDataEnd = originalData+numberOfBytes;
	while (originalData < originalDataEnd)
	{
		int i, code = *originalData;
		originalData++;
		for (i=1; originalData < originalDataEnd && i < code; i++) {
			*decobifiedData = *originalData;
			decobifiedData++;
			originalData++;
		}
		if (code < 0xFF) {
			*decobifiedData = 0;
		    decobifiedData++;
		}

	}
}


