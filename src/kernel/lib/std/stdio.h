//implemented in kernel/mod/terminal/terminal.c

#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>

typedef enum io_state
{
    stdin_command,
    stdin_data,
    stdout,
} io_state_t;

extern io_state_t current_io_state;

size_t strlen(char* str);
void terminal_initialize(void);
void printf(char* format, ...);
void erasef(int num);

#endif
