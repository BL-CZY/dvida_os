#include <stdint.h>

#include "lib/std/stdio.h"
#include "lib/utils/asm_utils.h"
#include "lib/utils/pic_utils.h"
#include "lib/utils/time.h"
#include "lib/file_system/file_system.h"

void kernel_main(void)
{
    current_io_state = stdin_data;
    terminal_initialize();
    printf("Hello World!\n");

    enable_interrupts();

    get_root();
    //enter the shell
    create_directory("test");
    create_file("test", "txt");

    sleep(1);

    terminal_initialize();
    printf("root > ");
    current_io_state = stdin_command;

    for(;;)
    {
        halt_cpu();
    }
}
