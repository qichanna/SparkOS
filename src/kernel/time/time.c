#include "time.h"

void initTime(){
    init_time_control();
    interrupt_real_fun(32, clock_function);
}

/*
 *
 *  0x43端口是控制8253控制字
 */
void init_time_control(){
    /*
     *  8253默认工作频率1.19318MHZ,即1193180，计数器0默认值0，0即表示65536，所以  1193180/65536=18.206表示1秒钟发生18.206次中断
     *  现在想提高中断频率，就需要把计数器默认值修改，比如我们想1秒钟中断100次，初始值为x, 那么1193180/x=100,x为1193180/100
     */
    uint8 init_count = 1193180/100;
    outb(0x43, (uint8)(0 << 6 | 3 << 4 | 2 << 1));  // 00_11_010_0  分别是选择计数器0,11先读低字节后读高字节，010方式二比率发生器，0二进制
    outb(0x40, (uint8)init_count); //计数器0端口是0x40，分别把
    outb(0x40, (uint8)init_count >> 8);
}

void clock_function(IDT_INFO info){
    int a = 0;
    s_print('w');
}