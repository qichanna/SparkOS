#ifndef SPARKOS_TIME_H
#define SPARKOS_TIME_H

#include "kernel/int/int.h"
#include "kernel/utils/utils.h"
#include "kernel/utils/print_s.h"
#include "commom/global.h"

void initTime();
void init_time_control();
void clock_function(IDT_INFO info);

#endif //SPARKOS_TIME_H
