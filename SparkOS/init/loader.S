%include "init.S"
[BITS 16]
section loader vstart=LOADER_BASE_ADDR

;输出背景色绿色，前景色红色，并且跳动的字符串"1 MBR"
mov byte [gs:0x00],'2'
mov byte [gs:0x01],0xA4     ; A表示绿色背景闪烁，4表示前景色为红色

mov byte [gs:0x02],' '
mov byte [gs:0x03],0xA4

mov byte [gs:0x04],'L'
mov byte [gs:0x05],0xA4   

mov byte [gs:0x06],'O'
mov byte [gs:0x07],0xA4

mov byte [gs:0x08],'A'
mov byte [gs:0x09],0xA4

mov byte [gs:0x0a],'D'
mov byte [gs:0x0b],0xA4

mov byte [gs:0x0c],'E'
mov byte [gs:0x0d],0xA4

mov byte [gs:0x0e],'R'
mov byte [gs:0x0f],0xA4

; jmp $		       ; 通过死循环使程序悬停在此




; CYLS	EQU		0x0ff0			; �u�[�g�Z�N�^���ݒ肷��
; LEDS	EQU		0x0ff1
; VMODE	EQU		0x0ff2			; �F���Ɋւ�����B���r�b�g�J���[���H
; SCRNX	EQU		0x0ff4			; �𑜓x��X
; SCRNY	EQU		0x0ff6			; �𑜓x��Y
; VRAM	EQU		0x0ff8			; �O���t�B�b�N�o�b�t�@�̊J�n�Ԓn

; 		ORG		0xc200			; ���̃v���O�������ǂ��ɓǂݍ��܂��̂�

; 		MOV		AL,0x13			; VGA�O���t�B�b�N�X�A320x200x8bit�J���[
; 		MOV		AH,0x00
; 		INT		0x10
; 		MOV		BYTE [VMODE],8	; ��ʃ��[�h����������
; 		MOV		WORD [SCRNX],320
; 		MOV		WORD [SCRNY],200
; 		MOV		DWORD [VRAM],0x000a0000

; ; �L�[�{�[�h��LED��Ԃ�BIOS�ɋ����Ă��炤

; 		MOV		AH,0x02
; 		INT		0x16 			; keyboard BIOS
; 		MOV		[LEDS],AL




mov eax, KERNEL_START_SECTOR        ; kernel.bin所在的扇区号
mov bx, KERNEL_BIN_BASE_ADDR       ; 从磁盘读出后，写入到ebx指定的地址
mov cx, 5		       ; 读入的扇区数

call rd_disk_m_16
; call kernel_init
; jmp KERNEL_ENTRY_POINT 
jmp KERNEL_BIN_BASE_ADDR 




rd_disk_m_16:	   
;-------------------------------------------------------------------------------
				       ; eax=LBA??????
				       ; ebx=??????д????????
				       ; ecx=???????????
      mov esi,eax	  ;????eax
      mov di,cx		  ;????cx
;??д???:
;??1????????????????????
      mov dx,0x1f2
      mov al,cl
      out dx,al            ;???????????

      mov eax,esi	   ;???ax

;??2??????LBA???????0x1f3 ~ 0x1f6

      ;LBA???7~0λд????0x1f3
      mov dx,0x1f3                       
      out dx,al                          

      ;LBA???15~8λд????0x1f4
      mov cl,8
      shr eax,cl
      mov dx,0x1f4
      out dx,al

      ;LBA???23~16λд????0x1f5
      shr eax,cl
      mov dx,0x1f5
      out dx,al

      shr eax,cl
      and al,0x0f	   ;lba??24~27λ
      or al,0xe0	   ; ????7??4λ?1110,???lba??
      mov dx,0x1f6
      out dx,al

;??3??????0x1f7???д???????0x20 
      mov dx,0x1f7
      mov al,0x20                        
      out dx,al

;??4????????????
  .not_ready:
      ;??????д????д????????????????????????
      nop
      in al,dx
      and al,0x88	   ;??4λ?1???????????????????????????7λ?1???????
      cmp al,0x08
      jnz .not_ready	   ;??δ?????????????

;??5??????0x1f0????????
      mov ax, di
      mov dx, 256
      mul dx
      mov cx, ax	   ; di????????????????????????512??????ζ?????????
			   ; ????di*512/2?Σ?????di*256
      mov dx, 0x1f0
  .go_on_read:
      in ax,dx
      mov [bx],ax
      add bx,2		  
      loop .go_on_read
      ret



; rd_disk_m_32:	   
; ;-------------------------------------------------------------------------------
; 							 ; eax=LBA扇区号
; 							 ; ebx=将数据写入的内存地址
; 							 ; ecx=读入的扇区数
;       mov esi,eax	   ; 备份eax
;       mov di,cx		   ; 备份扇区数到di
; ;读写硬盘:
; ;第1步：设置要读取的扇区数
;       mov dx,0x1f2
;       mov al,cl
;       out dx,al            ;读取的扇区数

;       mov eax,esi	   ;恢复ax

; ;第2步：将LBA地址存入0x1f3 ~ 0x1f6

;       ;LBA地址7~0位写入端口0x1f3
;       mov dx,0x1f3                       
;       out dx,al                          

;       ;LBA地址15~8位写入端口0x1f4
;       mov cl,8
;       shr eax,cl
;       mov dx,0x1f4
;       out dx,al

;       ;LBA地址23~16位写入端口0x1f5
;       shr eax,cl
;       mov dx,0x1f5
;       out dx,al

;       shr eax,cl
;       and al,0x0f	   ;lba第24~27位
;       or al,0xe0	   ; 设置7～4位为1110,表示lba模式
;       mov dx,0x1f6
;       out dx,al

; ;第3步：向0x1f7端口写入读命令，0x20 
;       mov dx,0x1f7
;       mov al,0x20                        
;       out dx,al

; ;;;;;;; 至此,硬盘控制器便从指定的lba地址(eax)处,读出连续的cx个扇区,下面检查硬盘状态,不忙就能把这cx个扇区的数据读出来

; ;第4步：检测硬盘状态
;   .not_ready:		   ;测试0x1f7端口(status寄存器)的的BSY位
;       ;同一端口,写时表示写入命令字,读时表示读入硬盘状态
;       nop
;       in al,dx
;       and al,0x88	   ;第4位为1表示硬盘控制器已准备好数据传输,第7位为1表示硬盘忙
;       cmp al,0x08
;       jnz .not_ready	   ;若未准备好,继续等。

; ;第5步：从0x1f0端口读数据
;       mov ax, di	   ;以下从硬盘端口读数据用insw指令更快捷,不过尽可能多的演示命令使用,
; 			   ;在此先用这种方法,在后面内容会用到insw和outsw等

;       mov dx, 256	   ;di为要读取的扇区数,一个扇区有512字节,每次读入一个字,共需di*512/2次,所以di*256
;       mul dx
;       mov cx, ax	   
;       mov dx, 0x1f0
;   .go_on_read:
;       in ax,dx		
;       mov [ebx], ax
;       add ebx, 2
; 			  ; 由于在实模式下偏移地址为16位,所以用bx只会访问到0~FFFFh的偏移。
; 			  ; loader的栈指针为0x900,bx为指向的数据输出缓冲区,且为16位，
; 			  ; 超过0xffff后,bx部分会从0开始,所以当要读取的扇区数过大,待写入的地址超过bx的范围时，
; 			  ; 从硬盘上读出的数据会把0x0000~0xffff的覆盖，
; 			  ; 造成栈被破坏,所以ret返回时,返回地址被破坏了,已经不是之前正确的地址,
; 			  ; 故程序出会错,不知道会跑到哪里去。
; 			  ; 所以改为ebx代替bx指向缓冲区,这样生成的机器码前面会有0x66和0x67来反转。
; 			  ; 0X66用于反转默认的操作数大小! 0X67用于反转默认的寻址方式.
; 			  ; cpu处于16位模式时,会理所当然的认为操作数和寻址都是16位,处于32位模式时,
; 			  ; 也会认为要执行的指令是32位.
; 			  ; 当我们在其中任意模式下用了另外模式的寻址方式或操作数大小(姑且认为16位模式用16位字节操作数，
; 			  ; 32位模式下用32字节的操作数)时,编译器会在指令前帮我们加上0x66或0x67，
; 			  ; 临时改变当前cpu模式到另外的模式下.
; 			  ; 假设当前运行在16位模式,遇到0X66时,操作数大小变为32位.
; 			  ; 假设当前运行在32位模式,遇到0X66时,操作数大小变为16位.
; 			  ; 假设当前运行在16位模式,遇到0X67时,寻址方式变为32位寻址
; 			  ; 假设当前运行在32位模式,遇到0X67时,寻址方式变为16位寻址.

;       loop .go_on_read
;       ret




; kernel_init:
;    xor eax, eax
;    xor ebx, ebx		;ebx记录程序头表地址
;    xor ecx, ecx		;cx记录程序头表中的program header数量
;    xor edx, edx		;dx 记录program header尺寸,即e_phentsize

;    mov dx, [KERNEL_BIN_BASE_ADDR + 42]	  ; 偏移文件42字节处的属性是e_phentsize,表示program header大小
;    mov ebx, [KERNEL_BIN_BASE_ADDR + 28]   ; 偏移文件开始部分28字节的地方是e_phoff,表示第1 个program header在文件中的偏移量
; 					  ; 其实该值是0x34,不过还是谨慎一点，这里来读取实际值
;    add ebx, KERNEL_BIN_BASE_ADDR
;    mov cx, [KERNEL_BIN_BASE_ADDR + 44]    ; 偏移文件开始部分44字节的地方是e_phnum,表示有几个program header
; .each_segment:
;    cmp byte [ebx + 0], PT_NULL		  ; 若p_type等于 PT_NULL,说明此program header未使用。
;    je .PTNULL

;    ;为函数memcpy压入参数,参数是从右往左依然压入.函数原型类似于 memcpy(dst,src,size)
;    push dword [ebx + 16]		  ; program header中偏移16字节的地方是p_filesz,压入函数memcpy的第三个参数:size
;    mov eax, [ebx + 4]			  ; 距程序头偏移量为4字节的位置是p_offset
;    add eax, KERNEL_BIN_BASE_ADDR	  ; 加上kernel.bin被加载到的物理地址,eax为该段的物理地址
;    push eax				  ; 压入函数memcpy的第二个参数:源地址
;    push dword [ebx + 8]			  ; 压入函数memcpy的第一个参数:目的地址,偏移程序头8字节的位置是p_vaddr，这就是目的地址
;    call mem_cpy				  ; 调用mem_cpy完成段复制
;    add esp,12				  ; 清理栈中压入的三个参数
; .PTNULL:
;    add ebx, edx				  ; edx为program header大小,即e_phentsize,在此ebx指向下一个program header 
;    loop .each_segment
;    ret

; ;----------  逐字节拷贝 mem_cpy(dst,src,size) ------------
; ;输入:栈中三个参数(dst,src,size)
; ;输出:无
; ;---------------------------------------------------------
; mem_cpy:		      
;    cld
;    push ebp
;    mov ebp, esp
;    push ecx		   ; rep指令用到了ecx，但ecx对于外层段的循环还有用，故先入栈备份
;    mov edi, [ebp + 8]	   ; dst
;    mov esi, [ebp + 12]	   ; src
;    mov ecx, [ebp + 16]	   ; size
;    rep movsb		   ; 逐字节拷贝

;    ;恢复环境
;    pop ecx		
;    pop ebp
;    ret













fin:
		HLT
		JMP		fin


