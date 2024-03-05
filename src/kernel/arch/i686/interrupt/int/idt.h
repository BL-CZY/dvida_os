#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>
#include "../../../../lib/terminal/terminalio.h"

typedef struct idt_entry
{
    uint16_t isr_low; //the lower 16 bits of the isr address
    uint16_t kernel_cs; //the gdt segment selector the the cpu will load
    uint8_t reserved; //reserved for padding
    /**
     * Gate type
     * 0b0101 or 0x5: Task Gate, note that in this case, the Offset value is unused and should be set to zero.
     * 0b0110 or 0x6: 16-bit Interrupt Gate
     * 0b0111 or 0x7: 16-bit Trap Gate
     * 0b1110 or 0xE: 32-bit Interrupt Gate
     * 0b1111 or 0xF: 32-bit Trap Gate 
     * 
     * DPL
     * privilege level
     * 
     * P
     * set to 1 so that it's valid
    */
    uint8_t attributes; //attributes
    uint16_t isr_high; //the higher 16 bits of the isr address
} __attribute__((packed)) idt_entry_t;

//like gdt descriptor
typedef struct idt_register
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

/**
 * these are the idt and idtr
 * 
 * the interrupt description table would consider 256 entries
*/

static idt_entry_t idt[256];
static idt_register_t idtr;

extern void* isr_stub_table[]; //void* could point to any type of objects, so here it points to the start of the isr_stub_table

void idt_init(void);

#endif