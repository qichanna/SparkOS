global write_mem8,io_hlt,out_byte
global _io_cli,_io_load_eflags,_io_store_eflags

io_hlt:
		hlt
		ret

write_vga_mem:
		mov		ECX,[ESP+4]
		mov		AL,[ESP+8]
		mov		[ECX],AL
		ret

out_byte:
    xor dx,dx
    xor ax,ax
    mov dx,[esp+4]
    mov al,[esp+8]
    out  dx,al
    ret

_io_cli:
		CLI
		RET

_io_load_eflags:
		PUSHFD
		POP		EAX
		RET

_io_store_eflags:
		MOV		EAX,[ESP+4]
		PUSH	EAX
		POPFD
		RET

