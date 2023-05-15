#include "keyboard.h"

struct KEYB0ARD_POOL pool;

void initKeyboard(){
    pool.size = 32;
    pool.free = 32;
    pool.start = 0;
    pool.end = 0;
    interrupt_real_fun(KEYBOARD_INT_NO,ketboard_int_function);
}

void ketboard_int_function(IDT_INFO info){
    putChar();
    int a = 0;
}

void putChar(){
    if(pool.free > 0){
        int code = inb(PORT_DATA_8042);
//        println_s("key_code: %x",code);
        pool.buf[pool.start++] = code;
        pool.free--;
        if(pool.start == pool.size){
            pool.start = 0;
        }
    }
}

int getChar(){
    if(pool.free < pool.size){
        int data = pool.buf[pool.end++];
        if(pool.end == pool.size){
            pool.end = 0;
        }
        pool.free++;
        return data;
    }
}

bool isPoolEmpty(){
    if(pool.free == pool.size) return true;
    return false;
}