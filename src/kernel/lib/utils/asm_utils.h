#ifndef IO_H
#define IO_H

#include <stdint.h>

extern void __attribute__((cdecl)) outb(uint16_t port, uint8_t value);
extern uint8_t __attribute__((cdecl)) inb(uint8_t port);
extern void __attribute__((cdecl)) outw(uint16_t port, uint16_t value);
extern uint16_t __attribute__((cdecl)) inw(uint16_t port);
extern void __attribute__((cdecl)) io_wait();

extern void __attribute__((cdecl)) disable_interrupts();
extern void __attribute__((cdecl)) enable_interrupts();
extern void __attribute__((cdecl)) halt_cpu();
extern void __attribute__((cdecl)) call_interrupt_0x80();

#endif