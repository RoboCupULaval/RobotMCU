/*
 * hermes_UT.h
 *
 *  Created on: Jul 2, 2016
 *      Author: philippe
 */

#ifndef ROBOCUP_HERMES_HERMES_UT_H_
#define ROBOCUP_HERMES_HERMES_UT_H_

#include "../robocup_define.h"
#include "hermes.h"



void test_hermes();
Result_t test_hermes_try_encode_decode(const char* payload, size_t payload_len);
Result_t test_hermes_invalid_packet(const char* pInvalid_packet, size_t packet_len);

#endif /* ROBOCUP_HERMES_HERMES_UT_H_ */
