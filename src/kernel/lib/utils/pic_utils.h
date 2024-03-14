//implemented in boot/interrupt/pic.c

#ifndef PIC_UTILS_H
#define PIC_UTILS_H

#include <stdint.h>

void mask_pic_port(int irq);
void unmask_pic_port(int irq);
void mask_all_pic_ports();
void unmask_all_pic_ports();
void pic_send_end_of_interrupt();

#endif