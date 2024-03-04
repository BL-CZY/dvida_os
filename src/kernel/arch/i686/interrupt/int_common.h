#ifndef INT_COMMON_H
#define INT_COMMON_H

#include <stdint.h>

typedef struct
{
    uint32_t esp;
    uint32_t ds;
    uint32_t edi, esi, ebp, kernel_sep, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp_first, ss;
} __attribute__((packed)) interrupt_info;

#endif