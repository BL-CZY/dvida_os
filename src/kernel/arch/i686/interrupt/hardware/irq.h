#ifndef IRQ_H
#define IRQ_H

#include "pic.h"
#include "../../../../lib/keyboard/keyboard.h"
#include "../int_common.h"

void irq_init();

void irq_1();

void irq_handler(interrupt_info* info);

#endif