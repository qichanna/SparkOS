//__asm__(".code16gcc");
#include "utils/utils.h"
#include "int/int.h"
#include "kernel/time/time.h"
#include "kernel/utils/print_s.h"

#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15

void init();
void set_color_panel();
void draw(unsigned char*, int , unsigned char, int, int, int, int);

void main(void)
{
    set_color_panel();
//     char* p = 0xa0000;
//     for (int i = 0; i <= 0xaffff; i++) {
//     	write_mem8(i, 15);
//     	write_mem8(i, i & 0x0f);
//        *(p + i) = 0;
//        *(p + i) = i & 0x0f;
//     }

    char *vram;
    int xsize, ysize;
    vram = (char *) 0xa0000;
    xsize = 320;
    ysize = 200;

    draw(vram, xsize, COL8_008484,  0,         0,          xsize -  1, ysize - 29);
    draw(vram, xsize, COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
    draw(vram, xsize, COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
    draw(vram, xsize, COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);

    draw(vram, xsize, COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
    draw(vram, xsize, COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
    draw(vram, xsize, COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
    draw(vram, xsize, COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
    draw(vram, xsize, COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
    draw(vram, xsize, COL8_000000, 60,         ysize - 24, 60,         ysize -  3);

    draw(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
    draw(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
    draw(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
    draw(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);
    init();
    sti();
     for (;;) {
         int a = 0;
     }
}

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

void draw(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
}

void init(){
    init_interupt();
    initTime();
    print_s("i am %c ok! %d! %s# %x$",'q',-956,"adgrc",29);
}
