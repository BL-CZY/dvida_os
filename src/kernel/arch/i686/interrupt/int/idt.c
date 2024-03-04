#include "idt.h"

static void idt_init(void)
{
    //loop to fill in the idt
    for(size_t i = 0; i < 256; ++i)
    {
        /**
         * this code is flawed, as when we change isr_stub_table[i], we are modifying the original value
         * once the original value is modified, it's "corrupted"
         * 
         * uint32_t high_address = (uint32_t)isr_stub_table[i];
         * uint32_t low_address = (uint32_t)isr_stub_table[i];
         * high_address = high_address >> 16; // shift higher addresses to the lower 16 bits
         * low_address = low_address & 0xFFFF; // use the mask to filter only the lower 16 bits
        */

        //copy the value so that in the later modification, the original value of isr_stub_table[i] won't change
        uint32_t isr_address = (uint32_t)isr_stub_table[i];

        //0x8E -> 0b1 00 0 E
        idt[i] = (idt_entry_t){(uint16_t)(isr_address & 0xFFFF), 0x08, 0, 0x8E, (uint16_t)(isr_address >> 16)};
    }

    idtr.limit = (uint16_t)sizeof(idt);
    idtr.base = (uintptr_t)&idt;

    __asm__ volatile (
        "lidt %0"
        : //output
        : "m" (idtr)
    );
}