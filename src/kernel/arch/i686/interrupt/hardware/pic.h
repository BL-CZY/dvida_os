#ifndef PIC_H
#define PIC_H

#include <stdint.h>
#include "../../../../lib/io/io.h"

void pic_config(uint8_t offset_pic1, uint8_t offset_pic2);

void mask_pic_port(int irq);

void unmask_pic_port(int irq);

void mask_all_pic();

void unmask_all_pic();

void pic_send_end_of_interrupt(int irq);

uint16_t read_pic_irr();

uint16_t read_pic_isr();

#endif