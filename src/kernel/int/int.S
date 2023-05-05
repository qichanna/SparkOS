extern idt_function
%macro IDT_FUNCTION 2
    global interrupt_exception_%1
    interrupt_exception_%1:
    pushad
    push ds
    push es
    push fs
    push gs

    call [idt_function+%1*4]

    pop gs 
    pop fs 
    pop es 
    pop ds
    popad 
    iret
%endmacro

IDT_FUNCTION 0x00,0
IDT_FUNCTION 0x01,0
IDT_FUNCTION 0x02,0
IDT_FUNCTION 0x03,0