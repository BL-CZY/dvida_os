#include <stdint.h>

#include "lib/terminal/terminalio.h"

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
    kernel_main();
}