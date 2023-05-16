%include "head.S"
[BITS 16]
section .text

;mov byte [gs:0x00],'2'
;mov byte [gs:0x01],0xA4     ; A表示绿色背景闪烁，4表示前景色为红色
;
;mov byte [gs:0x02],' '
;mov byte [gs:0x03],0xA4
;
;mov byte [gs:0x04],'L'
;mov byte [gs:0x05],0xA4
;
;mov byte [gs:0x06],'O'
;mov byte [gs:0x07],0xA4
;
;mov byte [gs:0x08],'A'
;mov byte [gs:0x09],0xA4
;
;mov byte [gs:0x0a],'D'
;mov byte [gs:0x0b],0xA4
;
;mov byte [gs:0x0c],'E'
;mov byte [gs:0x0d],0xA4
;
;mov byte [gs:0x0e],'R'
;mov byte [gs:0x0f],0xA4


;屏蔽PIC所有中断
mov		AL,0x13			; VGA显卡，320x200x8bit
mov		AH,0x00
int		0x10

;mov al,0x13  ;VGA模式
;mov ah,0x00
;int 0x10
;
;mov ax, 0xa000
;mov es, ax        ; 将段地址存储在 ES 寄存器中
;xor di, di        ; 将 DI 寄存器清零
;mov al, 0x0e      ;设置第一个像素颜色0x0e是黄色
;mov es:[di], al   ; 将 AL 寄存器中的值写入显存的第一个像素位置
;
;xor ecx, ecx
;mov cx, 0xFFFF
;loop_start:
;    mov ax, 0xa000
;    mov es, ax
;    mov ax, 0xa0000
;    xor di,di
;    mov di,cx
;    add ax, cx
;    and al,0x0f
;    mov es:[di], al
;loop loop_start

;mov		al,0xff
;out		0x21,al
;nop						; 不断执行OUT指令
;out		0xa1,al

cli

; A20
in al,0x92
or al,0000_0010B
out 0x92,al

;load gdt
lgdt [gdt_ptr]

;set cr0
mov eax, cr0
and eax,0x7fffffff
or eax, 0x1
mov cr0, eax

;jmp $

jmp SELECTOR_CODE:enter_loader

[bits 32]
enter_loader:
mov eax, 10000b
mov ds, ax
mov es, ax
mov ss, ax
mov esp,0x8000
mov ebp,0x8000
mov fs, ax
mov gs, ax

;开启SSE
;call enable_sse

mov eax, KERNEL_START_SECTOR        ; kernel.bin所在的扇区号
mov ebx, KERNEL_BIN_BASE_ADDR       ; 从磁盘读出后，写入到ebx指定的地址
mov ecx, 26    ; 读入的扇区数

;pushfd
call rd_disk_m_32
;popfd
jmp KERNEL_BIN_BASE_ADDR


enable_sse:
mov eax, cr0
and ax, 0xFFFB		;clear coprocessor emulation CR0.EM
or ax, 0x2			;set coprocessor monitoring  CR0.MP
mov cr0, eax
mov eax, cr4
or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
mov cr4, eax
ret


rd_disk_m_32:
;-------------------------------------------------------------------------------
							 ; eax=LBA扇区号
							 ; ebx=将数据写入的内存地址
							 ; ecx=读入的扇区数
mov esi,eax	   ; 备份eax
mov di,cx		   ; 备份扇区数到di
;读写硬盘:
;第1步：设置要读取的扇区数
mov dx,0x1f2
mov al,cl
out dx,al            ;读取的扇区数

mov eax,esi	   ;恢复ax

;第2步：将LBA地址存入0x1f3 ~ 0x1f6

;LBA地址7~0位写入端口0x1f3
mov dx,0x1f3
out dx,al

;LBA地址15~8位写入端口0x1f4
mov cl,8
shr eax,cl
mov dx,0x1f4
out dx,al

;LBA地址23~16位写入端口0x1f5
shr eax,cl
mov dx,0x1f5
out dx,al

shr eax,cl
and al,0x0f	   ;lba第24~27位
or al,0xe0	   ; 设置7～4位为1110,表示lba模式
mov dx,0x1f6
out dx,al

;第3步：向0x1f7端口写入读命令，0x20
mov dx,0x1f7
mov al,0x20
out dx,al

;;;;;; 至此,硬盘控制器便从指定的lba地址(eax)处,读出连续的cx个扇区,下面检查硬盘状态,不忙就能把这cx个扇区的数据读出来



;第4步：检测硬盘状态
;.not_ready:		   ;测试0x1f7端口(status寄存器)的的BSY位
;  ;同一端口,写时表示写入命令字,读时表示读入硬盘状态
;  nop
;  in al,dx
;  and al,0x88	   ;第4位为1表示硬盘控制器已准备好数据传输,第7位为1表示硬盘忙
;  cmp al,0x08
;  jnz .not_ready	   ;若未准备好,继续等。
;
;;第5步：从0x1f0端口读数据
;mov ax, di	   ;以下从硬盘端口读数据用insw指令更快捷,不过尽可能多的演示命令使用,
;		   ;在此先用这种方法,在后面内容会用到insw和outsw等
;
;mov dx, 256	   ;di为要读取的扇区数,一个扇区有512字节,每次读入一个字,共需di*512/2次,所以di*256
;mul dx
;mov cx, ax
;mov dx, 0x1f0
;
;.go_on_read:
;  in ax,dx
;  mov [ebx], ax
;  add ebx, 2
;loop .go_on_read









.read_sector:
 mov dx,0x1f7
.not_ready:
  nop
  in al,dx
  and al,0x88	   ;第4位为1表示硬盘控制器已准备好数据传输,第7位为1表示硬盘忙
  cmp al,0x08
  jnz .not_ready	   ;若未准备好,继续等。

  mov ax, 1
  mov dx, 256
  mul dx
  mov cx, ax
  mov dx, 0x1f0

  .go_on_read:
    in ax,dx
    mov [ebx], ax
    add ebx, 2
  loop .go_on_read

  sub di,1
  cmp di,0
jnz .read_sector

ret

GDT_BASE:  dd    0x00000000
 	       dd    0x00000000
CODE_DESC:  dd    0x0000FFFF
 	        dd    00000000_1_1_0_0_1111_1_00_1_1000_00000000b
DATA_STACK_DESC:  dd    0x0000FFFF
		     dd    00000000110011111001001000000000b
;
;   VIDEO_DESC: dd    0x80000007	       ;limit=(0xbffff-0xb8000)/4k=0x7
;	       dd    DESC_VIDEO_HIGH4  ; 此时dpl已改为0
GDT_SIZE   equ   $ - GDT_BASE
GDT_LIMIT  equ   GDT_SIZE - 1

;   dq 50 dup(0)             ;不能预留 60个 ，60 * 8B 太大了（只有1M内存），50可以运行正常。
    ; times 60 dq 0					 ; 此处预留60个描述符的slot
SELECTOR_CODE equ (0x1<<3) + 000b + 00b         ; 相当于(CODE_DESC - GDT_BASE)/8 + TI_GDT + RPL0
SELECTOR_DATA equ (0x2<<3) + 000b + 00b	 ; 同上
 ;   SELECTOR_VIDEO equ (0x0003<<3) + TI_GDT + RPL0	 ; 同上

    ;以下是定义gdt的指针，前2字节是gdt界限，后4字节是gdt起始地址
gdt_ptr:dw  GDT_LIMIT
      	 dd  GDT_BASE


;fin:
;		HLT
;		JMP		fin


