#include <stdint.h>
#include "lib/std/stdio.h"
#include "lib/utils/asm_utils.h"
#include "lib/utils/pic_utils.h"
#include "lib/utils/mem_utils.h"
#include "lib/utils/time.h"
#include "lib/file_system/file_system.h"
#include "mod/file_system/fs_driver.h"

void kernel_main(void)
{
    current_io_state = stdin_data;
    terminal_initialize();
    printf("Hello World!\n");
    *(char*)(0x40000000) = 'a';
    *(char*)(0x80000000) = 'b';
    *(char*)(0xBFFFFFFF) = 'c';

    get_root();
    //enter the shell

    sleep(1);
    
    terminal_initialize();
    printf("root > ");
    current_io_state = stdin_command;

    create_directory("test");
    create_directory("test");
    create_file("test", "txt");
    create_file("test", "txt");

    for(;;)
    {
        halt_cpu();
    }
}
