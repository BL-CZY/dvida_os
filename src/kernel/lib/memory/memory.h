#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void memcopy();
void memset();
void memmove();

void* malloc(size_t size);
void free(void* target);
void realloc(void* target, size_t size);

#endif