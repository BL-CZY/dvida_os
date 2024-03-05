#include "io.h"

void outb(uint16_t port, uint8_t value) //implemented in asm
{
    __asm__ volatile( //inline asm
        "out %0, %1" //output %0 to %1 port
        : //no output
        : "a" (value), "Nd" (port) //two input 0 and 1
    );
}

uint16_t inb(uint16_t port) //implemented in asm
{
    uint16_t result;
    __asm__ volatile( //inline asm
        "in %w1, %0" //input %w1 from %0
        : "=a" (result) //output
        : "Nd" (port) //input
    );
    return result;
}

void io_wait()
{
    outb(0x80, 0);
}