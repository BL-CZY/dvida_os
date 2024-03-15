//implemented in kernel/mod/utils/time.c

#ifndef TIME_H
#define TIME_H

#include <stdint.h>

extern int global_timer;

void update();
void sleep(int time);

#endif