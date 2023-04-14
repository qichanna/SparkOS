__asm__(".code16gcc");
// extern void io_hlt(void);
extern void write_mem8(void);

int main(void)
{
	// int i;

	// for (i = 0xa0000; i <= 0xaffff; i++) {
	// 	write_mem8(i, 15); /* MOV BYTE [i],15 */
	// }

write_mem8();

	// for (;;) {
	// 	io_hlt();
	// }
}
