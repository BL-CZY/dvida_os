#include "fs_driver.h"
#include "../../lib/file_system/file_system.h"
#include "../../lib/utils/time.h"
#include "../../lib/utils/asm_utils.h"

// ATA Ports
#define ATA_DATA_PORT 0x1F0
#define ATA_ERROR_PORT 0x1F1
#define ATA_SECTOR_COUNT_PORT 0x1F2
#define ATA_LBA_LOW_PORT 0x1F3
#define ATA_LBA_MID_PORT 0x1F4
#define ATA_LBA_HIGH_PORT 0x1F5
#define ATA_DRIVE_PORT 0x1F6
#define ATA_COMMAND_PORT 0x1F7
#define ATA_STATUS_PORT 0x1F7

// ATA Commands
#define ATA_CMD_READ_SECTORS 0x20
#define ATA_CMD_WRITE_SECTORS 0x30

char data_buffer[512];

int wait_for_disk()
{
    uint32_t time = 0;
    // Poll for completion (you might want to implement a timeout mechanism)
    while ((inw(ATA_STATUS_PORT) & 0x80) != 0x80)
    {
        ++time;
        if(time > 1000000)
        {
            return 0;
        }
    }
    return 1;
}

int read_sector(int lba)
{
    sleep(1);
    //no error
    outb(ATA_ERROR_PORT, 0);
    // Select drive (Assuming drive 0, replace with appropriate value if needed)
    // set 111 to enter LBA mode
    outb(ATA_DRIVE_PORT, 0xE0 | ((lba >> 24) & 0x0F));
    
    // Set sector count to 1
    outb(ATA_SECTOR_COUNT_PORT, 1);

    // Set LBA address
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH_PORT, (lba >> 16) & 0xFF);

    // Issue the read command
    outb(ATA_COMMAND_PORT, ATA_CMD_READ_SECTORS);
    if(!wait_for_disk())
    {
        return 1; //failed
    }

    sleep(1);

    // Read data from the data port
    for(int i = 0; i < 512; i += 2)
    {
        uint16_t temp = inw(ATA_DATA_PORT);
        data_buffer[i] = (uint8_t)temp;
        data_buffer[i + 1] = (uint8_t)(temp >> 8);
    }

    return 0;
}

int write_sector(int lba)
{
    sleep(1);
    //no error
    outb(ATA_ERROR_PORT, 0);
    // Select drive (Assuming drive 0, replace with appropriate value if needed)
    // set 111 to enter LBA mode
    outb(ATA_DRIVE_PORT, 0xE0 | ((lba >> 24) & 0x0F));

    // Set sector count to 1
    outb(ATA_SECTOR_COUNT_PORT, 1);

    // Set LBA address
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH_PORT, (lba >> 16) & 0xFF);

    // Issue the read command
    outb(ATA_COMMAND_PORT, ATA_CMD_WRITE_SECTORS);
    // if(!wait_for_disk())
    // {
    //     return 1; //failed
    // }

    sleep(1);

    //write the data from the data buffer
    for(int i = 0; i < 512; i += 2)
    {
        outw(ATA_DATA_PORT, (data_buffer[i]) | (data_buffer[i + 1] << 8));
    }

    return 0;
}