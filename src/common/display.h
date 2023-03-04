#ifndef COMMON_DISPLAY_H
#define COMMON_DISPLAY_H

#include "configParser.h"
#include <stdbool.h>

int printSize(char *buff, int buffSize, unsigned long size, bool decimalSize);
void printMessage(const PtShConfig *config, const char *str, bool err);
void printHelpLine(char arg, const char *argw, const char *desc);

#endif
