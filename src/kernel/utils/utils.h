void outb(int port,int data);
int inb(int port);
void cli();
void sti();
void hlt();
int read_eflags();
void restore_eflags(int);