#ifndef ROBOCUP_HERMES_COM_INTERFACE_H_
#define ROBOCUP_HERMES_COM_INTERFACE_H_
#include <stddef.h>

/***
 * Every communication medium uses by hermes must pass by this interface
 */
typedef size_t (*read_func_t)(void *pBuffer, size_t length);
typedef size_t (*write_func_t)(const void *pBuffer, size_t length);
typedef struct {
	read_func_t  read;
	read_func_t  readUntilZero;
	write_func_t write;
} comHandle_t;

#endif /* ROBOCUP_HERMES_COM_INTERFACE_H_ */
