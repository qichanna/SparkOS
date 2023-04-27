#rm -f *
#dd if=init.bin of=hd60M.img bs=512 count=1 conv=notrunc
#dd if=init_loader.bin of=hd60M.img bs=512 count=1 seek=1 conv=notrunc
#dd if=kernel.bin of=hd60M.img bs=512 count=1 seek=2 conv=notrunc
sh ../script/write_img.sh

# qemu-system-i386 -s -S -m 2048 hd60M.img
# qemu-system-x86_64 -s -S -hda hd60M.img
# qemu-system-x86_64 -fda hd60M.img
#qemu-system-i386-hda hd60M.img
#qemu-system-i386 -s -S -hda hd60M.img
# 适用于mac
#qemu-system-i386  -m 128M  -drive file=hd60M.img,index=0,media=disk,format=raw -d pcall,page,mmu,cpu_reset,guest_errors,page,trace:ps2_keyboard_set_translation
qemu-system-i386  -m 128M -s -S  -drive file=hd60M.img,index=0,media=disk,format=raw,id=hd0 -d pcall,page,mmu,cpu_reset,guest_errors,page,trace:ps2_keyboard_set_translation