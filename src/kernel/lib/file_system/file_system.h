//implemented in kernel/mod/file_system/fs_driver.c

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdint.h>

extern uint32_t current_directory_lba_address;
struct file;
struct directory;

void init_root();
void get_root();

int allocate_chunk();
void create_directory(char* name);
void create_file(char* name, char* file_extension);

char* fetch_current_dir_directories();
char* fetch_current_dir_files();
char* fetch_current_dir_contents();

#endif