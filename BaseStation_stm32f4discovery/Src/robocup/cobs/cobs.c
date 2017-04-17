#include "cobs.h"

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

// This function makes a decobified copy of the original data.
// Inputs:
//   ptr -- A pointer to a zero-terminated packet.
//   dstOut -- A pointer to the appropriate location for the decobified packet.
//   dst_len -- A pointer to a location to store the length of the  packet.
// Return value: 0 if success, something else otherwise.
int decobifyData(uint8_t *msg, uint8_t *dstOut, size_t *dst_len) {

	// we check if the message is properly zero-terminated with a correct length.
	int len = strnlen((char *) msg, COBS_MAX_PAYLOAD_LEN+2); // does not include the zero-terminator in the length
	if (len >= COBS_MAX_PAYLOAD_LEN) {
		return -1;
	}

	// we start the decobification process
	uint8_t* ptr = (unsigned char*) msg;
	uint8_t* dst = dstOut; // changing pointer to the byte location
	uint8_t* end = ptr + len; // a pointer to the last character (zero terminator)
	uint8_t code; // the length code

	// fetch the first length code and skip its location
	code = *ptr;
	ptr++;

	while (ptr < end) {

		// reached end of message, break out of while loop
		if (code == 0) {
			break;
		}

		// we copy the next bytes
		for (int i = 0; i < code-1; i++) {
			// If we get to the end too soon, the packet is malformed.
			if (ptr >= end) {
				return -1;
			}
			// we copy the byte, then continue on to the next location
			*dst = *ptr;
			ptr++;
			dst++;
		}

		// we fetch the next length code and put a zero in its place
		code = (*ptr);
		ptr++;
		dst = 0;
		dst++;
	}

	// we set the length of the decobificated packet,
	// which is always len-1 since len does not count the zero-terminator.
	(*dst_len) = len-1;

	// Process over, success status is returned.
	return 0;
}

