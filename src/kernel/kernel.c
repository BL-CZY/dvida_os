#include <stdint.h>

#include "lib/std/stdio.h"
#include "lib/utils/asm_utils.h"
#include "lib/utils/pic_utils.h"
#include "mod/file_system/fs_driver.h"

void kernel_main(void)
{
    current_io_state = stdin_data;
    terminal_initialize();
    printf("Hello World!\n");

    enable_interrupts();

    //enter the shell
    terminal_initialize();
    printf("root > ");
    current_io_state = stdin_command;

    for(;;)
    {
        halt_cpu();
    }
}
