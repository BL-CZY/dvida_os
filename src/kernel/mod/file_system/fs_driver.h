#ifndef FS_DRIVER_H
#define FS_DRIVER_H

#include <stdint.h>

extern uint8_t data_buffer[512];
struct sbf_address;
typedef struct sbf_address sbf_address_t;

int wait_for_disk();
int read_sector(int lba);
int write_sector(int lba);

uint32_t pointer_to_lba(uint32_t pointer);
sbf_address_t atla_to_sbf(uint32_t atla_address);
void set_allocation_table_flag(uint32_t atla_address);

#endif