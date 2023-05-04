#ifndef SPARKOS_INT_H
#define SPARKOS_INT_H
#include "../../commom/type.h"

#define IDT_COUNT 256

typedef struct{
    uint16 offset_low;
    uint16 selector;
    uint8 access_low;
    uint8 access_high;
    uint16 offset_high;
}IDT_DESC;

void init_interupt();
void set_idt_desc(IDT_DESC *idt_desc,uint16 offset_low,uint16 selector,uint8 access_low,uint8 access_hight,uint16 offset_high);
void initIDT();
void initPic();
void clock();
#endif //SPARKOS_INT_H
