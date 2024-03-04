#include "irq.h"

void irq_init()
{
    //0x20 is 32 and 0x28 is 40, which are after the intel-reserved gates
    pic_config(0x20, 0x28);
    outb(0x21,0xfd);
    outb(0xa1,0xff);
}

//this is for keyboard
void irq_1()
{
    //read the scancode
    uint8_t scancode = inb(0x60);
    //jump to the keyboard function
    process_key(scancode);
}

void irq_handler(interrupt_info* info)
{
    //printf("passed interrupt %u to the irq handler\n", info->interrupt);

    int irq = info->interrupt - 32;

    //printf("irq %u got triggered\n", irq);

    switch(irq)
    {
        case 1:
            irq_1();
            break;

        default:
            printf("irq working in progress");
    }

    pic_send_end_of_interrupt(irq);
}