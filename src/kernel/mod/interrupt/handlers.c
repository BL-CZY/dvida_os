#include "handlers.h"
#include "../../lib/utils/pic_utils.h"
#include "../../lib/utils/asm_utils.h"
#include "../../lib/utils/time.h"
#include "../../lib/std/stdio.h"
#include "../../lib/std/keyboard.h"
#include "../../mod/terminal/terminal.h"
#include "../../mod/file_system/fs_driver.h"
#include "../../lib/file_system/file_system.h"

typedef struct interrupt_info
{
    uint32_t esp;
    uint32_t ds;
    uint32_t edi, esi, ebp, kernel_sep, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp_first, ss;
} __attribute__((packed)) interrupt_info;

//irq_0: timer
void irq_0()
{
    on_update();
}

//irq_1: keyboard
void irq_1()
{
    //get the scancode
    uint8_t scancode = inb(0x60);
    process_key(scancode);
}

void irq_handler(interrupt_info* info)
{
    switch(info->interrupt - 32)
    {
        case 0x00:
            irq_0();
            break;

        case 0x01:
            irq_1();
            break;

        default:
            printf("unhandled irq %u\n", info->interrupt);
            break;
    }
    pic_send_end_of_interrupt();
}

void __attribute__((cdecl)) isr_handler(interrupt_info* info)
{
    if(info->interrupt >= 32 && info->interrupt < 48)
    {
        irq_handler(info);
        return;
    }

    switch(info->interrupt)
    {
        default:
            printf("unhandled isr %u\n", info->interrupt);
            break;
    }
}