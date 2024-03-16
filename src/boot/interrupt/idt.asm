[bits 32]

section .data
    
idt_start:
    times 64 * 256 db 0 ; reserve spaces for the idt
idt_end:

idt_descriptor:
    .limit: dw idt_end - idt_start
    .base: dd idt_start

section .text

global idt_init

extern isr_stub_table
extern printf

msg: db "here"

idt_init:
    mov eax, 0 ; initialize the counter

    .set_entry:
        cmp eax, 256 ; if counter is 256 then jump to end
        je .end ; jump if equal

        mov ebx, [isr_stub_table + eax * 4] ; mov the address of the handler to ebx

        mov word [idt_start + eax * 8], bx ; get the lower 16 bits of the address
        mov word [idt_start + eax * 8 + 2], 0x08 ; set the kernel code segment selector
        mov byte [idt_start + eax * 8 + 4], 0x00 ; reserved
        mov byte [idt_start + eax * 8 + 5], 0x8E ; set flags

        shr ebx, 16 ; get the higher 16 bits of the address
        mov word [idt_start + eax * 8 + 6], bx ; set the address of the handler

        inc eax ; increment the counter
        jmp .set_entry ; loop

    .end:
        lidt[idt_descriptor]
    
    ret
