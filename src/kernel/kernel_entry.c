//__asm__(".code16gcc");
#include "utils/utils.h"
#include "int/int.h"
#include "kernel/time/time.h"
#include "kernel/utils/print_s.h"
#include "commom/global.h"
#include "mouse/mouse.h"
#include "keyboard/keyboard.h"
#include "kernel/background/background.h"
#include "kernel/font/font.h"

void init();

void main(void)
{
//     char* p = 0xa0000;
//     for (int i = 0; i <= 0xaffff; i++) {
//     	write_mem8(i, 15);
//     	write_mem8(i, i & 0x0f);
//        *(p + i) = 0;
//        *(p + i) = i & 0x0f;
//     }

    init();
    sti();
     for (;;) {
         int a = 0;
     }
}

// 初始化
void init(){
    initBackground();
    initFont();
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
