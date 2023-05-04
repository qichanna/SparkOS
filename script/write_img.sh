dd if=init.bin of=osimg.img bs=512 count=1 conv=notrunc
dd if=init_loader.bin of=osimg.img bs=512 count=1 seek=1 conv=notrunc
dd if=kernel.bin of=osimg.img bs=512 count=4 seek=2 conv=notrunc