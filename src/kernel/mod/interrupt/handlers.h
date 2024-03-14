#include <stdint.h>

struct interrupt_info;

void irq_0();
void irq_1();

void __attribute__((cdecl)) isr_handler();