[bits 32]

section .data

gdt_start: ; memory address for the start of the gdt

    .null:          dw 0x00     ; limit_low
                    dw 0x00     ; base_low
                    db 0x00     ; base_middle
                    db 0x00     ; access
                    db 0x00     ; granularity
                    db 0x00     ; base_high
    
    .kernel_code:   dw 0xFFFF   ; it has the access to all the memory if paging is enabled
                    dw 0x00     ; start from 0
                    db 0x00     ; start from 0
                    db 0x9A     ; kernel code access
                    db 0xCF     ; flags + the higher 4 bits of the memory span
                    db 0x00     ; start from 0

    .kernel_data:   dw 0xFFFF   ; it has the access to all the memory if paging is enabled
                    dw 0x00     ; start from 0
                    db 0x00     ; start from 0
                    db 0x92     ; kernel data access
                    db 0xCF     ; flags + the higher 4 bits of the memory span
                    db 0x00     ; start from 0

    .user_code:     dw 0xFFFF   ; it has the access to all the memory if paging is enabled
                    dw 0x00     ; start from 0
                    db 0x00     ; start from 0
                    db 0xFA     ; user code access
                    db 0xCF     ; flags + the higher 4 bits of the memory span
                    db 0x00     ; start from 0

    .user_data:     dw 0xFFFF   ; it has the access to all the memory if paging is enabled
                    dw 0x00     ; start from 0
                    db 0x00     ; start from 0
                    db 0xF2     ; user data access
                    db 0xCF     ; flags + the higher 4 bits of the memory span
                    db 0x00     ; start from 0

gdt_end: ; memory address of the end of the gdt

gdt_descriptor: ; set the gdt descriptor
    .limit: dw gdt_end - gdt_start
    .base: dd gdt_start

section .text

global gdt_init

gdt_init: ; initialize gdt
    lgdt[gdt_descriptor] ; load the gdt
    call reload_segment ; reload the segment
    ret

reload_segment:
    jmp 0x08:.reload_cs ; long jump to kernel code to reload segments

.reload_cs:
    mov ax, 0x10 ; set ax to kernel data
    mov ds, ax ; set ds
    mov es, ax ; set es
    mov fs, ax ; set fs
    mov gs, ax ; set gs
    mov ss, ax ; set ss
    ret