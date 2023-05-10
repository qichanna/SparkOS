#ifndef SPARKOS_PRINT_S_H
#define SPARKOS_PRINT_S_H

#include "serial_print.h"
#include "stringUtils.h"

int print_s(char*,...);
int real_print(char*,char*,char*);
void numToStr(char**,int,int);

#endif //SPARKOS_PRINT_S_H
