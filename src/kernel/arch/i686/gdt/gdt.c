#include "gdt.h"

void gdt_init(void)
{
    gdt_entry_t gdt[5];
    gdt[0] = (gdt_entry_t){0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //null descriptor

    /**
     * limit_low is a 20 bits value, and it's set to 0xFFFFFF to maximize it, now the register can accesss
     * all the 4Gib length of the memory
     * 
     * base_low is a 32 bits value, and it's set to 0 so that the segment can access 
     * start from 0 to the 4Gib length
    */
    //im just gonna copy the format of the one on the osdev wiki
    //https://wiki.osdev.org/GDT_Tutorial

    /**
     * the access byte is 0b10011010
     * 1 present
     * 00 highest privilage level
     * 1 code segment
     * 1 executable
     * 0 can't jump
     * 1 readable
     * 0 can't access for security reasons(accidental modifications that may corrupt the pages)
    */

   /**
    * the granularity byte is 0b11001111
    * 1 the size of the a page is 4096
    * 1 32 bits processor
    * 0 not 64 bits so 0
    * 0 reserved byte for idk reasons
    * 1111 meaning paging enabled
    * 4096 * 0xFFFFF = 4GB
   */

    gdt[1] = (gdt_entry_t){0xFFFF, 0x00, 0x00, 0x9A, 0xCF, 0}; //kernel level code segment
    gdt[2] = (gdt_entry_t){0xFFFF, 0x00, 0x00, 0x92, 0xCF, 0}; //kernel level data segment
    gdt[3] = (gdt_entry_t){0xFFFF, 0x00, 0x00, 0xFA, 0xCF, 0}; //user mode code segment
    gdt[4] = (gdt_entry_t){0xFFFF, 0x00, 0x00, 0xF2, 0xCF, 0}; //user mode data segment

    gdt_ptr_t gdt_descriptor = (gdt_ptr_t){(uint16_t)sizeof(gdt) - 1, (uintptr_t)&gdt};

    __asm__ volatile (
        "lgdt %0"
        : //output
        : "m" (gdt_descriptor) //input, "m" means that it is a memory address
    );

    reload_segment();
}