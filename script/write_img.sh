dd if=init.bin of=hd60M.img bs=512 count=2 conv=notrunc
dd if=init_loader.bin of=hd60M.img bs=512 count=1 seek=2 conv=notrunc
dd if=kernel.bin of=hd60M.img bs=512 count=5 seek=9 conv=notrunc