#include "handlers.h"

typedef struct interrupt_info
{
    uint32_t esp;
    uint32_t ds;
    uint32_t edi, esi, ebp, kernel_sep, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp_first, ss;
} __attribute__((packed)) interrupt_info;

void __attribute__((cdecl)) isr_handler(interrupt_info* info)
{
    printf("interrupt %u got triggered\n", info->interrupt);
}