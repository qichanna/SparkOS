#include "mouse.h"

struct MOUSE_POOL mousePool;
struct MOUSE_INFO mouseInfo;

int mx = (XSIZE - 16) / 2;
int my = (YSIZE - 28 - 16) / 2;
char mcursor[256];

void initMouse(){
    mousePool.size = 128;
    mousePool.free = 128;
    mousePool.start = 0;
    mousePool.end = 0;

    mouseInfo.phase = 0;
    mouseInfo.x = 0;
    mouseInfo.y = 0;
    mouseInfo.click = 0;

    interrupt_real_fun(MOUSE_INT_NO,mouse_int_function);
    readyFinish();
    outb(0x64,0x60);// 打开读写模式0x20读，0x60写
    readyFinish();
    outb(0x60,0x47); //激活鼠标模式，使用数据寄存器可以接受数据，以至于可以达到中断
    readyFinish();
    outb(0x64,0xd4);// 从设备接收数据，激活鼠标
    readyFinish();
    outb(0x60,0xf4);// 发送数据0xf4，会有回复，比如鼠标是0xfa

    initCursor(mcursor, COL8_008484);
    drawMouse(vram, XSIZE, 16, 16, mx, my, mcursor, 16);
}

void readyFinish(){
    while (1){
        if((inb(0x64) & 0x02) == 0){
            break;
        }
    }
}

void initCursor(char *mouse, char color)
{
    static char cursor[16][16] = {
            "**************..",
            "*OOOOOOOOOOO*...",
            "*OOOOOOOOOO*....",
            "*OOOOOOOOO*.....",
            "*OOOOOOOO*......",
            "*OOOOOOO*.......",
            "*OOOOOOO*.......",
            "*OOOOOOOO*......",
            "*OOOO**OOO*.....",
            "*OOO*..*OOO*....",
            "*OO*....*OOO*...",
            "*O*......*OOO*..",
            "**........*OOO*.",
            "*..........*OOO*",
            "............*OO*",
            ".............***"
    };
    int x, y;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            if (cursor[y][x] == '*') {
                mouse[y * 16 + x] = COL8_000000;
            }
            if (cursor[y][x] == 'O') {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }
            if (cursor[y][x] == '.') {
                mouse[y * 16 + x] = color;
            }
        }
    }
}

void drawMouse(char *vram, int vxsize, int pxsize,
                 int pysize, int px0, int py0, char *buf, int bxsize)
{
    int x, y;
    for (y = 0; y < pysize; y++) {
        for (x = 0; x < pxsize; x++) {
            vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
        }
    }
    return;
}

/*void drawMouse(char *vram, int vxsize, int pxsize,
               int pysize, int px0, int py0, char *buf, int bxsize)
{
    char *base = vram;
    int x, y;
    int bytesPerRow = 3; // 24-bit
    for (y = 0; y < pysize; y++) {
        char *ybase = vram + ((py0+y) * vxsize * bytesPerRow);
        for (x = 0; x < pxsize; x++) {
            base = ybase + ((px0+x) * bytesPerRow);
            switch (buf[y * bxsize + x]) {
                case COL8_000000:
                    base[0] = 0xff;
                    base[1] = 0xff;
                    base[2] = 0xff;
                    break;
                case COL8_FFFFFF:
                    base[0] = 0x00;
                    base[1] = 0x00;
                    base[2] = 0x00;
                    break;
                default:
                    base[0] = 0x99;
                    base[1] = 0x88;
                    base[2] = 0x77;
                    break;
            }
        }
    }
    return;
}*/

void mouse_int_function(){
    putMouseChar();
//    println_s("mouse: %x",data);

}

void putMouseChar(){
    if(mousePool.free > 0){
        unsigned int code = inb(PORT_DATA_8042);
//        println_s("mouse_code: %x  %d",code, code);
        mousePool.buf[mousePool.start++] = code;
        mousePool.free--;
        if(mousePool.start == mousePool.size){
            mousePool.start = 0;
        }
    }
}

int getMouseChar(){
    if(mousePool.free < mousePool.size){
        unsigned int data = mousePool.buf[mousePool.end++];
//        println_s("getMouseChar: %x  %d  %d",data, data,mousePool.free);
        if(mousePool.end == mousePool.size){
            mousePool.end = 0;
        }
        mousePool.free++;

        if(mouseInfo.phase == 0){
            if(data == 0xfa){
                mouseInfo.phase = 1;
            }
        } else if(mouseInfo.phase == 1){
            if((data & 0xc8) == 0x08){ // 高4位值0-3，低4位值8-F
                mouseInfo.info[0] = data;
                mouseInfo.phase = 2;
            }
        } else if(mouseInfo.phase == 2){
            mouseInfo.info[1] = data;
            mouseInfo.phase = 3;
        } else if(mouseInfo.phase == 3){
            mouseInfo.info[2] = data;
            mouseInfo.phase = 1;
            mouseInfo.click = mouseInfo.info[0] & 0x07;
            mouseInfo.x = mouseInfo.info[1];
            mouseInfo.y = mouseInfo.info[2];
            if((mouseInfo.info[0] & 0x10) != 0){
                mouseInfo.x |= 0xffffff00;
            }
            if((mouseInfo.info[0] & 0x20) != 0){
                mouseInfo.y |= 0xffffff00;
            }
            mouseInfo.y = -mouseInfo.y;
//            draw(vram, XSIZE, COL8_008484, 32, 16, 32 + 15 * 8 - 1, 31);
//            print_string(vram, XSIZE, 32, 16, COL8_FFFFFF, "sssss");
            draw(vram, XSIZE, COL8_008484, mx, my, mx + 15, my + 15); // 隐藏鼠标

            mx += mouseInfo.x;
            my += mouseInfo.y;
            if(mx < 0) mx = 0;
            if(my < 0) my = 0;
            if(mx > XSIZE - 16) mx = XSIZE - 16;
            if(my > YSIZE - 16) my = YSIZE - 16;

//            draw(vram, XSIZE, COL8_008484, 0, 0, 79, 15);
//            print_string(vram, XSIZE, 0, 0, COL8_FFFFFF, "sssss");
            initFont();// 先重绘文字
            drawMouse(vram, XSIZE, 16, 16, mx, my, mcursor, 16);// 在重绘鼠标
        }
        return data;
    }
    return 1;
}

bool isMousePoolEmpty(){
    if(mousePool.free == mousePool.size) return true;
    return false;
}