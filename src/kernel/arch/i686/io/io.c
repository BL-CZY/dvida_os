#include "io.h"

__attribute__((cdecl))
void iowait()
{
    outb(0x80, 0);
}