//implemented in kernel/mod/file_system/fs_driver.c

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdint.h>

extern uint32_t current_folder_lba_address;
struct file;
struct folder;

void init_root();
void get_root();

#endif