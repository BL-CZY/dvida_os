#include <stdint.h>

#include "lib/std/stdio.h"
#include "lib/utils/asm_utils.h"
#include "lib/utils/pic_utils.h"
#include "../boot/interrupt/pic.h"

void kernel_main(void)
{
    current_io_state = stdin_data;
    terminal_initialize();
    printf("Hello World!\n");

    enable_interrupts();

    for(;;)
    {
        halt_cpu();
    }
}