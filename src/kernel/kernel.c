#include <stdint.h>

#include "lib/std/stdio.h"
#include "lib/utils/asm_utils.h"

void kernel_main(void)
{
    terminal_initialize();
    printf("Hello World!\n");
    enable_interrupts();
    call_interrupt_0x80();
}