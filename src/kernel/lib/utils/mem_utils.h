//implemented in mod/utils/mem_utils

#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include <stddef.h>

extern void* heap_start;
extern void* heap_end;
extern void* heap_current_address;

void memset(void* start, char val, size_t size);
void memcopy(void* from, void* to, size_t size);
void memmove(void* from, void* to, size_t size);

void* malloc(size_t size);
void free(void* target);
void realloc(void* target, size_t new_size);

#endif