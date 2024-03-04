#ifndef COMPUTE_SETTING_H
#define COMPUTE_SETTING_H

#include <stdint.h>
#include <stdarg.h>

uint32_t compute_setting(int bits, ...)
{
    va_list args;
    va_start(args, bits);
    uint32_t result = (uint32_t)va_arg(args, int);
    for(int i = 1; i < bits; ++i)
    {
        result = result | (uint32_t)va_arg(args, int);
    }
    return result;
}

#endif