kernel.bin: bootpack.o naskfunc.o mbr.bin loader.bin kernel.bin
	x86_64-elf-ld -m elf_i386 -Ttext 0x600 -e main -o kernel.bin bootpack.o naskfunc.o
	dd if=mbr.bin of=../osimg.img bs=512 count=1 conv=notrunc
	dd if=loader.bin of=../osimg.img bs=512 count=1 seek=2 conv=notrunc
	dd if=kernel.bin of=../osimg.img bs=512 count=5 seek=9 conv=notrunc

bootpack.o: bootpack.c
	x86_64-elf-gcc -O0 -m32 -fno-asynchronous-unwind-tables -s -c -o bootpack.o bootpack.c

naskfunc.o: naskfunc.S
	nasm -f elf -o naskfunc.o naskfunc.S

mbr.bin: mbr.S
	nasm -o mbr.bin mbr.S

loader.bin: loader.S
	nasm loader.S -l loader.lst -o loader.bin

#test.bin: test.S
#	nasm test.S -l test.lst -o test.bin

clean:
	rm *.o
	rm *.bin
	rm *.lst
	rm ../osimg.img

