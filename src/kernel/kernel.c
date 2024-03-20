#include <stdint.h>
#include "lib/std/stdio.h"
#include "lib/utils/asm_utils.h"
#include "lib/utils/pic_utils.h"
#include "lib/utils/mem_utils.h"
#include "lib/utils/time.h"
#include "lib/file_system/file_system.h"

void kernel_main(void)
{
    current_io_state = stdin_data;
    terminal_initialize();
    printf("Hello World!\n");

    get_root();
    //enter the shell

    sleep(1);
    for(;;)
    {
        halt_cpu();
    }

    *(char*)(0x80000000) = 'a';
    terminal_initialize();
    printf("root > ");
    current_io_state = stdin_command;
}
    for(;;)
    {
        halt_cpu();
    }
