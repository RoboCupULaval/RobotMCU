#include "cobs.h"

// This function creates a cobified copy of the data packet
// data -- A pointer to the raw payload.
// dstOut -- A pointer to the encoded packet.
// msg_len -- The length of the original payload in bytes.
// Return value: 0 if success, something else otherwise.
// Note: the destination location must have msg_len+2 bytes available in it.
int cobifyData(uint8_t *data, uint8_t *dstOut, size_t msg_len) {
	// The temporary pointers are initialized.
	uint8_t* ptr = data;
	uint8_t* dst = dstOut;
	uint8_t* code_ptr = dst; // the location at which to put the computed length code
	dst++; // skip the first position

	uint8_t code = 0x01; // the default code when the next byte is 0

	while (ptr < data+msg_len) {

		// if the current byte is zero
		if (*ptr == 0) {
			*code_ptr = code; // put the code at the appropriate location
			code_ptr = dst; // update the pointer to the next appropriate location
			code = 0x01; // code is reset
		}
		// otherwise the current byte is a regular one
		else {
			// copy the byte, update the pointers.
			*dst = *ptr;
			code++;

			// the whole packet is non-zero and longer than 255 (the code variable has wrapped), this is abnormal.
			if (code == 0x00) {
				return -1;
			}
		}

		// update the pointers
		ptr++;
		dst++;
	}
    // we add the final code value and then put the zero terminator at the end.
	*code_ptr = code;
	*dst = 0;

	// procedure over, return success
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
	uint8_t* ptr = msg;
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

