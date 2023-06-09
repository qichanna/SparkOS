#ifndef SPARKOS_GLOBAL_H
#define SPARKOS_GLOBAL_H

#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15


#define CLOCK_INT_NO 0x20
#define KEYBOARD_INT_NO 0x21
#define MOUSE_INT_NO 0x2C
//#define XSIZE 1024
//#define YSIZE 768

#define XSIZE 320
#define YSIZE 200

#define PORT_DATA_8042 0X60

static char *vram = (char *) 0xa0000;
//static char *vram = (char *) 0xfd000000;
//static char *vram = (char *) 0xf000d431;

#endif //SPARKOS_GLOBAL_H
