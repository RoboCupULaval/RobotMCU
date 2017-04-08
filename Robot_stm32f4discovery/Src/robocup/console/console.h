/*
 * hermes.h
 *
 *  Created on: 2016-06-21
 *      Author: Philippe Babin
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>
#include <string.h>

#include "../robocup_define.h"
#include "../com_interfaces/com_interface.h"
#include "../util.h"

void console_init(comHandle_t com);
void console_parseCommand(char pCmd[255], char parsedCmd[10][25]);


#endif // CONSOLE_H_
