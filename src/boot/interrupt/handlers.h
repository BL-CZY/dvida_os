#include "../../kernel/lib/std/stdio.h"

#include <stdint.h>

struct interrupt_info;

void __attribute__((cdecl)) isr_handler();