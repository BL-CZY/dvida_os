#include "../../lib/utils/time.h"
#include "../../lib/std/stdio.h"

int global_timer = 0;

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