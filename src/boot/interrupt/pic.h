#ifndef PIC_H
#define PIC_H

#include <stdint.h>
#include "../../kernel/lib/utils/asm_utils.h"
#include "../../kernel/lib/std/stdio.h"

void pic_init();
void pic_config(uint8_t offset_pic1, uint8_t offset_pic2);

#endif