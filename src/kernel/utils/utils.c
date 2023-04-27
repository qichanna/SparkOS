#include "utils.h"
extern void out_byte(int,int);
extern void _io_cli();
extern int _io_load_eflags();
extern void _io_store_eflags(int);

void outb(int port,int data){
    out_byte(port,data);
}

void cli(){
    _io_cli();
}

int read_eflags(){
    return _io_load_eflags();
}

void restore_eflags(int eflags){
    _io_store_eflags(eflags);
}