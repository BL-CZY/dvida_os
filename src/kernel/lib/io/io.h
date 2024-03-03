#ifndef IO_H
#define IO_H

#include <stdint.h>

__attribute__((cdecl))
extern void outb(uint16_t port, uint8_t value); //implemented in asm

__attribute__((cdecl))
extern uint16_t inb(uint16_t port); //implemented in asm

__attribute__((cdecl))
void io_wait()
{
    outb(0x80, 0);
}

#endif