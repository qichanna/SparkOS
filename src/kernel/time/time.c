#include "time.h"

void initTime(){
    init_time_control();
    interrupt_real_fun(CLOCK_INT_NO, clock_function);
}

/*
 *
 *  0x43端口是控制8253控制字
 */
void init_time_control(){
    /*
     *  8253默认工作频率1.19318MHZ,即1193180，计数器0默认值0，0即表示65536，所以  1193180/65536=18.206表示1秒钟发生18.206次中断
     *  现在想提高中断频率，就需要把计数器默认值修改，比如我们想1秒钟中断100次，初始值为x, 那么1193180/x=100,x为1193180/100,
     *  0x40端口最多16位，所以每秒最少中断次数1193180/65535 = 18次左右
     */
    uint16 init_count = 0xFFFF;
    outb(0x43, (uint8)(0 << 6 | 3 << 4 | 2 << 1));  // 00_11_010_0  分别是选择计数器0,11先读低字节后读高字节，010方式二比率发生器，0二进制
    outb(0x40, (uint8)init_count); //计数器0端口是0x40，分别把初始值存入0x40端口，这是计数器0的初始寄存器，共16位，必须分2次写，先低8位，后高8位
    outb(0x40, (uint8)(init_count >> 8));
}

void clock_function(IDT_INFO info){
    int a = 0;
//    print_s("diffc");
}