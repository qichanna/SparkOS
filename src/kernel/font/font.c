#include "font.h"
extern char font_date[4096];

int bytesPerRow = 3;

void initFont(){
    print_string(vram, XSIZE, 10, 10, COL8_FFFFFF, "I am success!");
}

// 打印字体
void print_single_font(char *vram, int xsize, int x, int y, char c, char font)
{
    int i;
    char *p, d;
    for (i = 0; i < 16; i++) {
        p = vram + (y + i) * xsize + x;
        d = *(font * 16 + font_date + i);
        if ((d & 0x80) != 0) { p[0] = c; }
        if ((d & 0x40) != 0) { p[1] = c; }
        if ((d & 0x20) != 0) { p[2] = c; }
        if ((d & 0x10) != 0) { p[3] = c; }
        if ((d & 0x08) != 0) { p[4] = c; }
        if ((d & 0x04) != 0) { p[5] = c; }
        if ((d & 0x02) != 0) { p[6] = c; }
        if ((d & 0x01) != 0) { p[7] = c; }
    }
}

/*void print_single_font(char *vram, int xsize, int x, int y, char c, char font)
{
    int i;
    char *p, d;
    for (i = 0; i < 16; i++) {
        p = vram + (y + i) * xsize * bytesPerRow + x * bytesPerRow;
        d = *(font * 16 + font_date + i);
        if ((d & 0x80) != 0) {
            p[0] = 0x00;
            p[1] = 0x00;
            p[2] = 0x00;
        }
        if ((d & 0x40) != 0) {
            p[3] = 0x00;
            p[4] = 0x00;
            p[5] = 0x00;
        }
        if ((d & 0x20) != 0) {
            p[6] = 0x00;
            p[7] = 0x00;
            p[8] = 0x00;
        }
        if ((d & 0x10) != 0) {
            p[9] = 0x00;
            p[10] = 0x00;
            p[11] = 0x00;
        }
        if ((d & 0x08) != 0) {
            p[12] = 0x00;
            p[13] = 0x00;
            p[14] = 0x00;
        }
        if ((d & 0x04) != 0) {
            p[15] = 0x00;
            p[16] = 0x00;
            p[17] = 0x00;
        }
        if ((d & 0x02) != 0) {
            p[18] = 0x00;
            p[19] = 0x00;
            p[20] = 0x00;
        }
        if ((d & 0x01) != 0) {
            p[21] = 0x00;
            p[22] = 0x00;
            p[23] = 0x00;
        }

        *//*if ((d & 0x80) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x40) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x20) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x10) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x08) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x04) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x02) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }
        if ((d & 0x01) != 0) {
            *(p++) = 0x00;
            *(p++) = 0x00;
            *(p++) = 0x00;
        } else{
            p++;
            p++;
            p++;
        }*//*
    }
}*/

void print_string(char *vram, int xsize, int x, int y, char c, char* string){
    while (*string != '\0'){
        print_single_font(vram,xsize,x,y,c,*string);
        x += 8;
        string++;
    }
}