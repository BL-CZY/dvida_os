#include "fs_driver.h"
#include "../../lib/file_system/file_system.h"
#include "../../lib/utils/time.h"
#include "../../lib/utils/asm_utils.h"
#include "../../lib/std/stdio.h"

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

//about the file system
/** description
 * I divided the 4 Gib disk into 4Kib chunks, which are 4 sectors
*/

//about the allocation table
/** description
 * this buffer keeps track of allocated and unallocated chunks in the storage
 * there are 4Gib, or 4*10^9 bytes in the disk
 * they are divided into 4Kib chunks
 * therefore, 4Gib/4Kib = 10^6
 * one chunk requires one bit to be marked unallocated/allocated
 * 10^6 / 8 = 125000
 * 
 * after 10 secs of thinking I realized that loading this into the memory and scanning the disk every time is stupid
 * 
 * as a result it's going to be in the storage.img
 * 125000/4096 = 30.2039832423546575645
 * so I am going to use 31 chunks
*/
/** addresing
 * allocation table addressing:
 * 31 sectors
 * 512 bytes per sector
 * 8 flags per byte
 * so it's going to be the SBF addressing
 * 
 * as it's offseted by 1 (right after the root dir)
 * it's 1 - 32 for sectors
 * 0 - 511 for bytes
 * 0 - 7 for flags
 * 
 * Allocation Table Linear Address (ATLA) would be the linear address of it
 * converting it to SBF would be:
 * S = ((ATLA / 8) / 512 ) % 32 + 1
 * B = (ATLA / 8) % 512
 * F = ATLA % 8
*/

typedef struct file
{
    char file_name[24]; // file name
    char file_extention[4]; // file extension
    uint32_t* ptr; // pointer to the next chunk
} file_t;

typedef struct folder
{
    char folder_name[28]; // folder name
    uint32_t* ptr; // pointer to the next chunk
} folder_t;

struct sbf_address
{
    uint8_t sector_address;
    uint16_t byte_address;
    uint8_t flag_address;
};

typedef struct sbf_address sbf_address_t;

uint8_t data_buffer[512];
uint32_t current_folder_lba_address;

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

void read_sector_with_retry(int lba, int times)
{
    for(int i = 0; i < times; ++i)
    {
        //if without error
        if(!read_sector(lba))
        {
            break;
        }
    }
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

uint32_t pointer_to_lba(uint32_t pointer)
{
    uint32_t temp = ((pointer >> 12) << 12);
    return (temp >> 9); //convert it to LBA, divide by 512
}

sbf_address_t atla_to_sbf(uint32_t atla_address)
{
    //formula
    return (sbf_address_t){((atla_address/8)/512)%32+1, (atla_address/8)%512, atla_address%8};
}

void set_allocation_table_flag(uint32_t atla_address)
{
    sbf_address_t temp = atla_to_sbf(atla_address);
    read_sector_with_retry(temp.sector_address, 100);
    for(int i = 0; i < 512; ++i)
    {
        printf("%u", data_buffer[i]);
    }
    printf("\n");
    data_buffer[temp.byte_address] = data_buffer[temp.byte_address] | (0x1 << (7-temp.flag_address));
    for(int i = 0; i < 512; ++i)
    {
        printf("%u", data_buffer[i]);
    }
    write_sector(temp.sector_address);
}

void init_root()
{
    for(int i = 0; i < 512; ++i)
    {
        data_buffer[i] = 0;
    }

    //clear the 2nd, 3rd, and 4th sector
    write_sector(1);
    write_sector(2);
    write_sector(3);

    //clear the 1st sector while initializing the DFRS magic word
    data_buffer[0] = 'D';
    data_buffer[1] = 'F';
    data_buffer[2] = 'R';
    data_buffer[3] = 'T';
    write_sector(0);
    //set current
    current_folder_lba_address = 0;

    //initialize the allocation table
    data_buffer[0] = 0;
    data_buffer[1] = 0;
    data_buffer[2] = 0;
    data_buffer[3] = 0;

    for(int i = 1; i <= 32; ++i)
    {
        printf("%u", i);
        write_sector(i);
    }

    //the root dir is used
    set_allocation_table_flag(0);
}

//get root dir
void get_root()
{
    //read the first sector, which is the root dir
    read_sector_with_retry(0, 100);
    /**
     * the 1-4 bytes are
     * DFRT
     * if they it's the dvida_os_root_dir
    */
    //get the 4 bytes about the root info

    int has_root_init = 0;

    //get the four bytes
    char magic_word[4];
    magic_word[0] = data_buffer[0];
    magic_word[1] = data_buffer[1];
    magic_word[2] = data_buffer[2];
    magic_word[3] = data_buffer[3];
    
    if(magic_word[0] == 'D' && magic_word[1] == 'F' && magic_word[2] == 'R' && magic_word[3] == 'T')
    {
        has_root_init = 1;
    }

    //if it's not the root, clear and initialize
    if(!has_root_init)
    {
        init_root();
    }
}