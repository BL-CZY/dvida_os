[bits 32]

global inb
global outb
global inw
global outw
global io_wait

global disable_interrupts
global enable_interrupts
global halt_cpu

global get_eax
global get_ebx
global get_ecx
global get_edx
global get_esp
global get_ebp

global set_eax
global set_ebx
global set_ecx
global set_edx
global set_esp
global set_ebp

global call_interrupt_0x80

section .text
    
    ; arguments:
    ;   a uint16_t port
    ;
    ; return:
    ;   a uint8_t value
    ;
    ; function: it will read in the port dx, and read the value of the port to al
    inb:
        mov dx, [esp + 4]
        in al, dx
        ret

    ; arguments:
    ;   a uint16_t port
    ;   a uint8_t value
    ;
    ; function: it will write the value stored in al into the port stored in dx
    outb:
        mov dx, [esp + 4]
        mov al, [esp + 8]
        out dx, al
        ret

    ; arguments:
    ;   a uint16_t port
    ;
    ; return:
    ;   a uint16_t value
    ;
    ; function: it will read in the port dx, and read the value of the port to ax
    inw:
        mov dx, [esp + 4]
        in ax, dx
        ret

    ; arguments:
    ;   a uint16_t port
    ;   a uint8_t value
    ;
    ; function: it will write the value stored in ax into the port stored in dx
    outw:
        mov dx, [esp + 4]
        mov ax, [esp + 8]
        out dx, ax
        ret

    ; arguments: none
    ; 
    ; function: transfer things to random ports to wait for a lil bit
    io_wait:
        mov dx, 0x80
        mov al, 0x00
        out dx, al
        ret

    ; arguments: none
    ; 
    ; function: diable interrupts, avoid the use of inline asm
    disable_interrupts:
        cli
        ret

    ; arguments: none
    ; 
    ; function: enable interrupts, avoid the use of inline asm
    enable_interrupts:
        sti
        ret

    ; arguments: none
    ; 
    ; function: halt the cpu, avoid the use of inline asm
    halt_cpu:
        hlt
        ret

    ; arguments: none
    ; 
    ; function: system call 0x80
    call_interrupt_0x80:
        int 0x80
        ret

    get_eax:
        mov eax, eax
        ret

    get_ebx:
        mov eax, ebx
        ret

    get_ecx:
        mov eax, ecx
        ret

    get_edx:
        mov eax, edx
        ret

    get_esp:
        mov eax, esp
        ret

    get_ebp:
        mov eax, ebp
        ret

    set_eax:
        mov eax, [esp + 4]
        ret

    set_ebx:
        mov ebx, [esp + 4]
        ret

    set_ecx:
        mov ecx, [esp + 4]
        ret

    set_edx:
        mov edx, [esp + 4]
        ret

    set_esp:
        mov esp, [esp + 4]
        ret

    set_ebp:
        mov ebp, [esp + 4]
        ret