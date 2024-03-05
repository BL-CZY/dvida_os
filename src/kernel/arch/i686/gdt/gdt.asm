[bits 32]

global reload_segment
extern printf

section .text

reload_segment:
    jmp 0x08:.reload_cs
    ret

.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret