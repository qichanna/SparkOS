#ifndef SPARKOS_INT_H
#define SPARKOS_INT_H
#include "commom/type.h"

#define IDT_COUNT 33

typedef struct{
    uint16 offset_low;
    uint16 selector;
    uint8 access_low;
    uint8 access_high;
    uint16 offset_high;
}IDT_DESC;

typedef struct{
    int vec_no;
    int gs,fs,es,ds; // push四个段寄存器
    int edi,esi,ebp,esp,ebx,edx,ecx,eax;
    int error_code,eip,cs,eflags;
}IDT_INFO;

void init_interupt();
void interrupt_real_fun(int,void*);
void set_idt_desc(IDT_DESC *idt_desc,uint16 offset_low,uint16 selector,uint8 access_low,uint8 access_hight,uint16 offset_high);
void initIDT();
void initPic();
void default_interrupt_entry(IDT_INFO);
#endif //SPARKOS_INT_H
