#include "../../lib/utils/time.h"
#include "../../lib/std/stdio.h"

int global_timer = 0;

/**
 * arguments: none
 * 
 * function: it will be called every time the pic timer fires an interrupt
*/
void update()
{
    ++global_timer;
}

/**
 * arguments:
 *  an int time
 * 
 * function: sleep for given time
*/
void sleep(int time)
{
    int temp = global_timer + time;
    while(global_timer != temp)
    {
        asm("hlt");
    }
    return;
}