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

    char* test_str = (char*)malloc(3);
    test_str[0] = 'a';
    *(test_str + 1) = 'a';
    *(test_str + 2) = '\0';

    if(*(test_str) == 'a')
    {
        if(*(test_str + 1) == 'a')
        {
            printf("yeah?");
            asm("int $0x80");
        }
    }
    if(*(test_str) == 'a')
    {
        printf("yeah!");
        asm("int $0x80");
    }

    for(;;)
    {
        halt_cpu();
    }
    terminal_initialize();
    printf("root > ");
    current_io_state = stdin_command;
}
