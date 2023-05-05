#include "int.h"
#include "kernel/utils/utils.h"

// ICW1    OCW2  OCW3  (主从，0X20, 0XA0)
// OCW1    ICW2 ICW3 ICW4    (主从，0X21, 0XA1)

// 0 ~ 19 为处理器内部固定的异常类型， 20~31 是 Intel保留的

static IDT_DESC idt_desc[IDT_COUNT];
void* idt_function[IDT_COUNT];

void init_interupt(){
    initIDT();
    initPic();
}

void initIDT(){
    // interrupt_exception();
    for (int i = 0; i < IDT_COUNT; ++i){
        idt_function[i] = interrupt_entry;
        // set_idt_desc(idt_desc + i,(uint16)interrupt_exception,8,0,0x8e,(uint32)interrupt_exception >> 16);
    }

    struct{
        uint16 size;
        uint16 address_low;
        uint16 address_high;
    } idt;
    idt.size = sizeof(idt_desc) - 1;
    idt.address_low = (uint32)idt_desc;
    idt.address_high = (uint32)idt_desc >> 16 ;
    __asm__ __volatile__("lidt %0"::"m"(idt));
}

void set_idt_desc(IDT_DESC *idt_desc,uint16 offset_low,uint16 selector,uint8 access_low,uint8 access_high,uint16 offset_high){
    idt_desc->offset_low = offset_low;
    idt_desc->selector = selector;
    idt_desc->access_low = access_low;
    idt_desc->access_high = access_high;
    idt_desc->offset_high = offset_high;
}

void initPic(){
    // 初始化主片PIC
    outb(0X20,0X11); // ICW1   最低位1，表示需要ICW4
    outb(0X21,0X20); // ICW2   0x00 - 0x1f 中断号CPU内部使用，所以从0x20开始,到0x27，虽然IR2被用于连接，但是也算进去
    outb(0X21,0x04); // ICW3   表示从IR2口接从片，也就是第三个
    outb(0X21,0X11); // ICW4   打开最低1位，表示x86处理器

    // 初始化从片PIC
    outb(0X20,0X11); // ICW1   最低位1，表示需要ICW4
    outb(0X21,0X28); // ICW2   接着上面的0x27后面，从0x28到0x2F
    outb(0X21,0x02); // ICW3   表示主片是2号后链接到我的，所以是0x02
    outb(0X21,0X11); // ICW4   打开最低1位，表示x86处理器

    // OCW1 屏蔽中断号 (主0X21,从0XA1)
    outb(0x21,0xfe); // 主片全部屏蔽
    outb(0xa1,0xff); // 从片全部屏蔽
}
void clock(){
    int a = 0;
    // while (1);
}

void interrupt_entry(IDT_INFO info){
    int a = info.gs;
    int b = 0;
}