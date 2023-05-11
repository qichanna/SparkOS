//__asm__(".code16gcc");
#include "utils/utils.h"
#include "int/int.h"
#include "kernel/time/time.h"
#include "kernel/utils/print_s.h"
#include "commom/global.h"
#include "mouse/mouse.h"

void init();
void set_color_panel();
void draw(unsigned char*, int , unsigned char, int, int, int, int);
// 字体
void print_single_font(char *vram, int xsize, int x, int y, char c, char);
void print_string(char *vram, int xsize, int x, int y, char c, char*);
extern char font_date[4096];

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

    int mx, my;
    mx = (xsize - 16) / 2;
    my = (ysize - 28 - 16) / 2;
    char mcursor[256];

//    static char font_A[16] = {
//            0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
//            0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
//    };

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
    print_string(vram, xsize, 10, 10, COL8_FFFFFF, "I am success!");

    initMouse(mcursor, COL8_008484);
    drawMouse(vram, xsize, 16, 16, mx, my, mcursor, 16);

    init();
//    sti();
     for (;;) {
         int a = 0;
     }
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

void draw(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
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
    return;
}

void print_string(char *vram, int xsize, int x, int y, char c, char* string){
    while (*string != '\0'){
        print_single_font(vram,xsize,x,y,c,*string);
        x += 8;
        string++;
    }
}

// 初始化
void init(){
    init_interupt();
    initTime();
    print_s("i am %c ok! %d! %s# %x$",'q',-956,"adgrc",29);
}
