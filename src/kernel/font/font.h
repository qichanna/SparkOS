#ifndef SPARKOS_FONT_H
#define SPARKOS_FONT_H

#include "../../commom/global.h"

void initFont();
void print_single_font(char *vram, int xsize, int x, int y, char c, char);
void print_string(char *vram, int xsize, int x, int y, char c, char*);

#endif //SPARKOS_FONT_H
