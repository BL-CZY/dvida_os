//implemented in mod/utils/mem_utils

#ifndef MEM_UTILS_H
#define MEM_UTILS_H

#include <stddef.h>

extern const void* heap_start;
extern const void* heap_end;
extern void* heap_current_address;

void* memset(void* start, int val, size_t size);
void* memcopy(void* dest, const void* src, size_t n);
void* memmove(void *dest, const void *src, size_t n);

void* malloc(size_t size);
void free(void* target);
void* realloc(void* target, size_t new_size);

#endif