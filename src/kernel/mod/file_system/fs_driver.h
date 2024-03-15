#ifndef FS_DRIVER_H
#define FS_DRIVER_H

extern char data_buffer[512];

int wait_for_disk();
int read_sector(int lba);
int write_sector(int lba);

#endif