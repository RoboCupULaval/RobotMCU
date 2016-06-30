/*
 * util.c
 *
 *  Created on: Jun 26, 2016
 *      Author: philippe
 */
#include "stdio.h"
#include <stdint.h>

void convertBytesToStr(const void * ptr, size_t len, char* str){
  uint8_t *bytes = (uint8_t *)ptr;
  for(unsigned i = 0; i < len; i++){
    sprintf(str, "%02x:", bytes[i]);
    str += 3;
  }
  *str = '\0';
}
