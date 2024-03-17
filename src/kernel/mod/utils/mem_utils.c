#include "../../lib/utils/mem_utils.h"
#include "../../lib/std/stdio.h"

#include <stdint.h>

#define HEAP_START_ADDRESS 0x80000000  // 2 GiB
#define HEAP_END_ADDRESS   0xC0000000  // 4 GiB

// Variables to track the start and current position of the heap
const void* heap_start = (void*)HEAP_START_ADDRESS;
const void* heap_end = (void*)HEAP_END_ADDRESS;
void* heap_current_address = (void*)HEAP_START_ADDRESS;

void* memset(void* start, int val, size_t size)
{
    uint8_t* p = (uint8_t*)start;
 
    for(size_t i = 0; i < size; i++)
    {
        p[i] = (uint8_t)val;
    }
 
    return start;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (const uint8_t*)src;
 
    for(size_t i = 0; i < n; i++)
    {
        pdest[i] = psrc[i];
    }
 
    return dest;
}

void* memmove(void *dest, const void *src, size_t n)
{
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;
 
    if(src > dest)
    {
        for(size_t i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }
    } 
    else if(src < dest) 
    {
        for(size_t i = n; i > 0; i--)
        {
            pdest[i-1] = psrc[i-1];
        }
    }
 
    return dest;
}

void* malloc(size_t size)
{
    /**
     * the block structure:
     * the heap is divided into 4 bytes blocks
     * every time it will allocate an extra block at the beginning to keep track of the information of this block
    */

    /**
     * allocations
     * reuse alloc: allocate from those freed
     * lazy alloc: allocate from the current location
     * brute force alloc: search the entire heap
    */

    //check for lazy alloc
    //TODO implement reuse alloc and brute force alloc
    size_t block_num = 1 + (size/4 + (size%4 > 0));
    int lazy_alloc = 1;

    if(heap_current_address + size > heap_end)
    {
        lazy_alloc = 0;
    }

    if(lazy_alloc)
    {
        //set the information about the first block
        *(uint32_t*)heap_current_address = block_num * 4;
        void* result = heap_current_address + 4;
        heap_current_address += block_num * 4;
        return result;
    }

    //TODO placeholder, it will be a system interrupt call
    return 0;
}


void free(void* target)
{
    void* start = target - 4;
    size_t size = (size_t)(*(uint32_t*)start);
    for(size_t i = 0; i < size; ++i)
    {
        *(char*)(start + i) = '\0';
    }
}

void* realloc(void* target, size_t new_size)
{
    void* start = target;
    size_t size = *(size_t*)(start - 4);
    void* new_address = malloc(new_size);
    memcpy(start, new_address, size);
    free(start);
    return new_address;
}