; edge triggered mode
; always ensure that a device is not in a interrupt state

; level triggered mode
; checks if the device actually needs attention

; *the PIC is designed to utilize the edge triggered mode
; *so this is gonna be used

; TODO APIC is designed for both, upgrade to the APIC!

[bits 32]

global outb
global inb

section .text

; choose to use dx and al for conventions
outb:
    mov dx, [esp + 4] ; get the port number
    mov al, [esp + 8] ; get the value
    out dx, al ; output the value of al to dx
    ret

inb:
    mov dx, [esp + 4] ; get the port number
    xor eax, eax
    in al, dx ; input the value of dx to al
    ret