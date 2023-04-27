%include "head.S"
[BITS 16]
mov ax,cs
mov ds,ax
mov es,ax
mov ss,ax
mov fs,ax
mov sp,0x7c00
mov ax,0xb800
mov gs,ax

mov     ax, 0x0600  ;ah=0x06 清屏功能  al=0 清除所有行
mov     bx, 0x0700  ;上卷属性
mov     cx, 0  ;左上角(0,0)
mov     dx, 0x184f ;右下角(18,4f),0x18=24,0x4f=79, 25行，每行80个字符
int     0x10

mov byte [gs:0x00],'I'
mov byte [gs:0x01],0xA4

mov byte [gs:0x02],'n'
mov byte [gs:0x03],0xA4

mov byte [gs:0x04],'i'
mov byte [gs:0x05],0xA4

mov byte [gs:0x06],'t'
mov byte [gs:0x07],0xA4

mov byte [gs:0x08],'!'
mov byte [gs:0x09],0xA4

mov eax, 0x0 ; 将内存地址0x900存储到寄存器AX中
mov es, ax     ; 将寄存器AX的值存储到段寄存器ES中，用于存储数据

mov ah, 0x02   ; 设置AH寄存器的值为0x02，表示读取扇区
mov al, 1  ; 设置AL寄存器的值为0x0A，表示要读取的扇区数
mov ch, 0x00   ; 设置磁头号为0
mov dh, 0x00   ; 设置磁盘号为0
mov cl, LOADER_START_SECTOR   ; 设置起始扇区号为2

mov bx, LOADER_BASE_ADDR ; 设置BX寄存器的值为0，用于存储读取数据的返回状态
mov dl, 0x80   ; 设置DL寄存器的值为0x80，表示要读取的磁盘号为80h

int 13h       ; 调用int 0x13中断，进行扇区读取操作

jmp LOADER_BASE_ADDR

rd_disk_m_16:
      mov esi,eax
      mov di,cx

      mov dx,0x1f2
      mov al,cl
      out dx,al

      mov eax,esi

      mov dx,0x1f3
      out dx,al

      mov cl,8
      shr eax,cl
      mov dx,0x1f4
      out dx,al

      shr eax,cl
      mov dx,0x1f5
      out dx,al

      shr eax,cl
      and al,0x0f
      or al,0xe0
      mov dx,0x1f6
      out dx,al

      mov dx,0x1f7
      mov al,0x20
      out dx,al

  .not_ready:
      nop
      in al,dx
      and al,0x88
      cmp al,0x08
      jnz .not_ready

      mov ax, di
      mov dx, 256
      mul dx
      mov cx, ax
      mov dx, 0x1f0
  .go_on_read:
      in ax,dx
      mov [bx],ax
      add bx,2
      loop .go_on_read
      ret

times 510-($-$$) db 0
db 0x55,0xaa