# qemu-system-i386 -s -S -m 2048 osimg.img
# qemu-system-x86_64 -s -S -hda osimg.img
# 适用于mac
qemu-system-i386  -m 128M -s -S  -drive file=osimg.img,index=0,media=disk,format=raw -d pcall,page,mmu,cpu_reset,guest_errors,page,trace:ps2_keyboard_set_translation
# qemu-system-i386  -m 128M -drive file=osimg.img,index=0,media=disk,format=raw -d pcall,page,mmu,cpu_reset,guest_errors,page,trace:ps2_keyboard_set_translation