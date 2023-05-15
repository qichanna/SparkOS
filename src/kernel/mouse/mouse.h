#ifndef SPARKOS_MOUSE_H
#define SPARKOS_MOUSE_H

#include <stdbool.h>
#include "commom/global.h"
#include "kernel/int/int.h"
#include "kernel/utils/print_s.h"

struct MOUSE_POOL{
    unsigned char buf[128];
    int size;
    int free;
    int start;
    int end;
};

struct MOUSE_INFO{
    char info[3];
    int phase;
    int x;
    int y;
    int click;
};

void initMouse();
void initCursor(char *mouse, char bc);
void drawMouse(char *vram, int vxsize, int pxsize,
                 int pysize, int px0, int py0, char *buf, int bxsize);

void mouse_int_function();
void readyFinish();


void putMouseChar();
int getMouseChar();
bool isMousePoolEmpty();


#endif //SPARKOS_MOUSE_H
