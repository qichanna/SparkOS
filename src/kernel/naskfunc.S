; naskfunc
; TAB=4

;[FORMAT "WCOFF"]				
;[INSTRSET "i486p"]			
BITS 16
;[FILE "naskfunc.nas"]

		GLOBAL	write_mem8

[SECTION .text]

;io_hlt:	; void io_hlt(void);
;		HLT
;		RET
extern test

write_mem8:	; void write_mem8(int addr, int data);

		; mov ax,0x12
		; ret
		; MOV		ECX,[ESP+4]		; [ESP+4]��addr�������Ă���̂ł����ECX�ɓǂݍ���
		; MOV		AL,[ESP+8]		; [ESP+8]��data�������Ă���̂ł����AL�ɓǂݍ���
		; MOV		[ECX],AL
		; RET
xor ax,ax
mov ax,0xb800
mov gs,ax

; call test

mov byte [gs:0x0a],'c'
mov byte [gs:0x0b],0xA4

mov byte [gs:0x0c],'N'
mov byte [gs:0x0d],0xA4   ; A表示绿色背景闪烁，4表示前景色为红色


; mov byte [gs:0x0e],'m'
; mov byte [gs:0x0f],0x4A

; mov byte [gs:0x10],'p'
; mov byte [gs:0x11],0xA4
;  jmp $
RET