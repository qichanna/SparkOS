# qemu-system-i386 -s -S -m 2048 hd60M.img
# qemu-system-x86_64 -s -S -hda hd60M.img
# 适用于mac
qemu-system-i386  -m 128M -s -S  -drive file=hd60M.img,index=0,media=disk,format=raw -d pcall,page,mmu,cpu_reset,guest_errors,page,trace:ps2_keyboard_set_translation
# qemu-system-i386  -m 128M -drive file=hd60M.img,index=0,media=disk,format=raw -d pcall,page,mmu,cpu_reset,guest_errors,page,trace:ps2_keyboard_set_translation