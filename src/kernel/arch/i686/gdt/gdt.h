#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr
{
    //the length of the gdt
    //it has to be n - 1, as the cpu will understand that as an offest that starts with 0
    uint16_t limit;
    //the start of it
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

extern void reload_segment(void);

void gdt_init(void);

#endif