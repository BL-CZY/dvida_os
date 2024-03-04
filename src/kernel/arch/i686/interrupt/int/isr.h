#ifndef ISR_H
#define ISR_H

#include <stdint.h>
#include "../int_common.h"
#include "../../../../lib/terminal/terminalio.h"
#include "../../../../lib/io/io.h"
#include "../hardware/pic.h"
#include "../hardware/irq.h"

__attribute__((cdecl))
void isr_handler(interrupt_info* info);

#endif