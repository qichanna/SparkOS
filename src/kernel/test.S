%include "init.S"
[BITS 16]	
section loader

; 输出背景色绿色，前景色红色，并且跳动的字符串"1 MBR"
; mov byte [gs:0x00],'2'
; mov byte [gs:0x01],0xA4     ; A表示绿色背景闪烁，4表示前景色为红色

; mov byte [gs:0x02],' '
; mov byte [gs:0x03],0xA4

; mov byte [gs:0x04],'L'
; mov byte [gs:0x05],0xA4   

; mov byte [gs:0x06],'O'
; mov byte [gs:0x07],0xA4

; mov byte [gs:0x08],'A'
; mov byte [gs:0x09],0xA4

; mov byte [gs:0x0a],'D'
; mov byte [gs:0x0b],0xA4

; mov byte [gs:0x0c],'E'
; mov byte [gs:0x0d],0xA4

; mov byte [gs:0x0e],'S'
; mov byte [gs:0x0f],0xA4

; jmp $		       ; 通过死循环使程序悬停在此



mov al,0x13  ;VGA模式
mov ah,0x00
int 0x10


mov ax, 0xa000
mov es, ax        ; 将段地址存储在 ES 寄存器中
xor di, di        ; 将 DI 寄存器清零
mov al, 0x0e      ;设置第一个像素颜色0x0e是黄色
mov es:[di], al   ; 将 AL 寄存器中的值写入显存的第一个像素位置

xor ecx, ecx
mov cx, 0xFFFF
loop_start:
    mov ax, 0xa000
    mov es, ax
    mov ax, 0xa0000
    xor di,di
    mov di,cx
    add ax, cx
    and al,0x0f
    mov es:[di], al
loop loop_start



; mov ax, 0xa000
; mov es, ax
; xor di, di
; mov al, 0x0f
; mov es:[di], al 

jmp $
; fin:
    ; HLT
    ; jmp fin







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


; 		MOV		AH,0x02
; 		INT		0x16 			; keyboard BIOS
; 		MOV		[LEDS],AL

; fin:
; 		HLT
; 		JMP		fin


