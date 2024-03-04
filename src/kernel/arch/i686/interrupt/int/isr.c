#include "isr.h"

__attribute__((cdecl))
void isr_handler(interrupt_info* info)
{
    //printf("Interrupt %u got triggered\n", info->interrupt);
    //__asm__ volatile ("cli; hlt");

    if(info->interrupt >= 32 && info->interrupt < 48) //if within the range go to the irq
    {
        irq_handler(info);
    }
}