//implemented in kernel/mod/crashell/interpreter.c

#ifndef SHELL_H
#define SHELL_H

extern char command_buffer[50];
extern int command_buffer_index;

void execute_command();

#endif
