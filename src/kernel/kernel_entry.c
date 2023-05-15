//__asm__(".code16gcc");
#include "utils/utils.h"
#include "int/int.h"
#include "kernel/time/time.h"
#include "kernel/utils/print_s.h"
#include "commom/global.h"
#include "mouse/mouse.h"
#include "keyboard/keyboard.h"

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


    char *vram = (char *) 0xa0000;


//    static char font_A[16] = {
//            0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
//            0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
//    };

    draw(vram, XSIZE, COL8_008484,  0,         0,          XSIZE -  1, YSIZE - 29);
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
    print_string(vram, XSIZE, 10, 10, COL8_FFFFFF, "I am success!");



    init();
    sti();
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
    initMouse();
    initKeyboard();
//    print_s("i am %c ok! %d! %s# %x$",'q',-956,"adgrc",29);

    while (1){
        cli();
        if(isPoolEmpty() && isMousePoolEmpty()){
            sti();
            hlt();
        } else if(!isPoolEmpty()){
            int data = getChar();
            println_s("%x",data);
            sti();
        } else if(!isMousePoolEmpty()){
            int data = getMouseChar();
//            println_s("%x",data);
            sti();
        }
    }
}
