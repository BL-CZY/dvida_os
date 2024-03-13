[bits 32]

global inb
global outb
global inw
global outw
global io_wait

global disable_interrupts
global enable_interrupts
global halt_cpu

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
        push 0x00
        push 0x80
        call outb
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