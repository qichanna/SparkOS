void outb(int port,int data);
void cli();
void sti();
int read_eflags();
void restore_eflags(int);