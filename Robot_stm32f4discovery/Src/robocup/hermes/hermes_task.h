
#ifndef HERMES_TASK_H_
#define HERMES_TASK_H_

#include <stdio.h>
#include <string.h>


#include "hermes.h"

// When the packet is encoded some data in the header is still in a decoded forms
// To optimize the speed of communication, the destination address is read before decoding occurs.
// Since destination address is never of zero value, Cobs does not changes it's value when encoding.
typedef struct __attribute__((__packed__)) {
	uint8_t offsetFirstZero;
	packetHeaderStruct_t header;
} encodedPacketHeaderStruct_t;

void hermes_task_slave(void);

#endif // HERMES_TASK_H_
