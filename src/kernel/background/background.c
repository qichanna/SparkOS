#include "background.h"

void initBackground(){
    set_color_panel();
    drawBackground();
}

void drawBackground(){
    draw(vram, XSIZE, COL8_008484,  0,         0,          XSIZE - 1, YSIZE - 29);
    draw(vram, XSIZE, COL8_C6C6C6,  0,         YSIZE - 28, XSIZE -  1, YSIZE - 28);
    draw(vram, XSIZE, COL8_FFFFFF,  0,         YSIZE - 27, XSIZE -  1, YSIZE - 27);
    draw(vram, XSIZE, COL8_C6C6C6,  0,         YSIZE - 26, XSIZE -  1, YSIZE -  1);

    draw(vram, XSIZE, COL8_FFFFFF,  3,         YSIZE - 24, 59,         YSIZE - 24);
    draw(vram, XSIZE, COL8_FFFFFF,  2,         YSIZE - 24,  2,         YSIZE -  4);
    draw(vram, XSIZE, COL8_848484,  3,         YSIZE -  4, 59,         YSIZE -  4);
    draw(vram, XSIZE, COL8_848484, 59,         YSIZE - 23, 59,         YSIZE -  5);
    draw(vram, XSIZE, COL8_000000,  2,         YSIZE -  3, 59,         YSIZE -  3);
    draw(vram, XSIZE, COL8_000000, 60,         YSIZE - 24, 60,         YSIZE -  3);

    draw(vram, XSIZE, COL8_848484, XSIZE - 47, YSIZE - 24, XSIZE -  4, YSIZE - 24);
    draw(vram, XSIZE, COL8_848484, XSIZE - 47, YSIZE - 23, XSIZE - 47, YSIZE -  4);
    draw(vram, XSIZE, COL8_FFFFFF, XSIZE - 47, YSIZE -  3, XSIZE -  4, YSIZE -  3);
    draw(vram, XSIZE, COL8_FFFFFF, XSIZE -  3, YSIZE - 24, XSIZE -  3, YSIZE -  3);
}

// 设置背景色
void set_color_panel(){
    unsigned char rgb_table[16*3] = {
            0x00, 0x00, 0x00,
            0xff, 0x00, 0x00,
            0x00, 0xff, 0x00,
            0xff, 0xff, 0x00,
            0x00, 0x00, 0xff,
            0xff, 0x00, 0xff,
            0x00, 0xff, 0xff,
            0xff, 0xff, 0xff,
            0xc6, 0xc6, 0xc6,
            0x84, 0x00, 0x00,
            0x00, 0x84, 0x00,
            0x84, 0x84, 0x00,
            0x00, 0x00, 0x84,
            0x84, 0x00, 0x84,
            0x00, 0x84, 0x84,
            0x84, 0x84, 0x84
    };

    char *rgb = rgb_table;
    //0x03c8端口设置0号调色板
    outb(0x03c8,0);
    for (int i = 0; i < 16; ++i) {
        outb(0x03c9,*(rgb++)/4);
        outb(0x03c9,*(rgb++)/4);
        outb(0x03c9,*(rgb++)/4);
    }
    return;
}

void draw(char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
}

/*void draw(char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;
    int bytesPerRow = 3; // 24-bit
    for (y = y0; y <= y1; y++) {
        char *ybase = vram + (y * xsize * bytesPerRow);
        for (x = x0; x <= x1; x++){
            char *base = ybase + (x * bytesPerRow);
            base[0] = 0x99;
            base[1] = 0x88;
            base[2] = 0x77;
        }
    }
    return;
}*/
