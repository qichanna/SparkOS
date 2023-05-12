#ifndef SPARKOS_KEYBOARD_H
#define SPARKOS_KEYBOARD_H

#include <stdbool.h>
#include "../int/int.h"
#include "../utils/utils.h"
#include "../../commom/global.h"
#include "../utils/print_s.h"

#define KEYBOARD_PORT 0x60

struct KEYB0ARD_POOL{
    unsigned char buf[32];
    int size;
    int free;
    int start;
    int end;
};

void initKeyboard();
void ketboard_int_function(IDT_INFO);
void putChar();
int getChar();
bool isPoolEmpty();
#endif //SPARKOS_KEYBOARD_H
