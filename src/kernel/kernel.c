#include "lib/std/stdio.h"
#include <stdint.h>

void kernel_main(void)
{
    terminal_initialize();
    printf("Hello World!");
}