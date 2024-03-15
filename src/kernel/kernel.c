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

    if(read_sector(0) == 0)
    {
        for(int i = 0; i < 512; ++i)
        {
            printf("%u", data_buffer[i]);
        }
    }

    for(;;)
    {
        halt_cpu();
    }
}