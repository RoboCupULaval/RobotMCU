/*
 * util.c
*/
#include "util.h"


void convertBytesToStr(const void * ptr, size_t len, char* str){
  uint8_t *bytes = (uint8_t *)ptr;
  for(unsigned i = 0; i < len; i++){
    sprintf(str, "%02x:", bytes[i]);
    str += 3;
  }
  *str = '\0';
}


void Debug_Print(char * pStr){
	g_hermesHandle.com.write(pStr, strlen(pStr));
}
