#include "hermes.h"

#define FinishBlock(X) (*code_ptr = (X), code_ptr = dst++, code = 0x01)

/***
 * This function creates a cobified copy of the Data
 * It is the responsibility of the used to have enough space in the cobifiedData array
 * (It takes 2 additionnal bytes.)
 * data    : Pointer to the raw payload
 * msg_len : Length of the payload in bytes
 * dstOut  : Pointer to the encoded packet. It's zero terminated string
 */
int cobifyData(const void *data, size_t msg_len, char *dstOut) {
	const unsigned char *ptr = (const unsigned char *) data;
	unsigned char *dst = (unsigned char *) dstOut;
	const unsigned char *end = (const unsigned char*) (ptr) + msg_len;
	unsigned char *code_ptr = dst++;
	unsigned char code = 0x01;

	while (ptr < end) {
		if (*ptr == 0)
			FinishBlock(code);
		else {
			*dst++ = *ptr;
			if (++code == 0xFF)
				FinishBlock(code);
		}
		ptr++;
	}

	FinishBlock(code);
	*code_ptr = 0;
	return 0;
}

/***
 * This function makes a decobified copy of the original Data
 * ptr     : Pointer to the zero terminate encoded packet
 * len     : Length of the packet (Why? It's zero terminated!?!)
 * dstOut  : Pointer to the decoded payload
 * dst_len : Number of byte in the payload, should alway be payload's len -1
 */
int  decobifyData(const char *msg, size_t len, void *dstOut, size_t *dst_len) {
	if(len >= COBS_MAX_PAYLOAD_LEN)
		return -1;
	unsigned char *ptr = (unsigned char*) msg;
	unsigned char *dst = (unsigned char*) dstOut;
	const unsigned char *end = ptr + len;
	*dst_len = 0;
	while (ptr < end) {
		int i, code = *ptr++;
		for (i = 1; i < code; i++) {
			// If we get to the end too soon, the pack is invalid
			if (ptr >= end)
				return -1;
			*dst++ = *ptr++;
			(*dst_len)++;

		}
		// code mark the number of byte until a zero, so a zero is added at is position
		if (code < 0xFF)
			*dst++ = 0;
		(*dst_len)++;
	}
	(*dst_len)--;
	return 0;
}

