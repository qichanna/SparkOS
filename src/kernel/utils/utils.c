#include "utils.h"
extern void out_byte(int,int);
extern void _io_cli();
extern void _io_sti();
extern int _io_load_eflags();
extern void _io_store_eflags(int);

void outb(int port,int data){
    out_byte(port,data);
}

int inb(int port){
    int data = 0;
    asm volatile("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

void cli(){
    _io_cli();
}

void sti(){
    _io_sti();
}

int read_eflags(){
    return _io_load_eflags();
}

void restore_eflags(int eflags){
    _io_store_eflags(eflags);
}