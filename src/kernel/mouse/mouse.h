#ifndef SPARKOS_MOUSE_H
#define SPARKOS_MOUSE_H

void initMouse(char *mouse, char bc);
void drawMouse(char *vram, int vxsize, int pxsize,
                 int pysize, int px0, int py0, char *buf, int bxsize);

#endif //SPARKOS_MOUSE_H
