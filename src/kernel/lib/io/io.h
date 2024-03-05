#ifndef IO_H
#define IO_H

#include <stdint.h>

void outb(uint16_t port, uint8_t value);

uint16_t inb(uint16_t port);

void io_wait();

#endif