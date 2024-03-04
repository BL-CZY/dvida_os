#include <stdint.h>

void kernel_main(void)
{
    printf("%ce%s%cd%s%cc%u\n", "test", "test", vga_entry_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK), 300);
    //__asm__ volatile ("int $0x20");

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
    printf("hopefully interrupts are enabled\n");
    kernel_main();
}