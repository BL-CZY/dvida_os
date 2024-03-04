#include <stdint.h>
#include "lib/terminal/terminalio.h"

extern void gdt_init(void);
extern void idt_init(void);
extern void irq_init(void);

void kernel_main(void)
{
    printf("%ce%s%cd%s%cc%u\n", "test", "test", vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK), 300);

    for(;;) {
        asm("hlt");
    }
}

void kernel_early(void)
{
    terminal_initialize();
    gdt_init();
    idt_init();
    irq_init();
    //enable interrupts
    __asm__ volatile(
        "sti"
    );
    kernel_main();
}