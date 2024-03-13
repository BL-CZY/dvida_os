#ifndef IO_H
#define IO_H

#include <stdint.h>

extern __attribute__((cdecl)) void outb(uint16_t port, uint8_t value);
extern uint8_t __attribute__((cdecl)) inb(uint8_t port);
extern void __attribute__((cdecl)) outw(uint16_t port, uint16_t value);
extern uint16_t __attribute__((cdecl)) inw(uint16_t port);
void io_wait();

#endif