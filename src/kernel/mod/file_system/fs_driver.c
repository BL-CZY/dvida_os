#include "fs_driver.h"
#include "../../lib/file_system/file_system.h"
#include "../../lib/utils/time.h"
#include "../../lib/utils/asm_utils.h"
#include "../../lib/std/stdio.h"
#include "../../lib/utils/mem_utils.h"

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
 * I divided the 4 Gib disk into 4Kib chunks, which are 8 sectors
 * The first chunk will be at 0, and the first 32 bytes will be used for root directory configuration
*/
/** the root directory
 * The structure of the root directory is a little bit different from others
 * The minimal root directory contains 40 sectors rather than 8
 * But only the last 8 sector is usable
 * The last 31 sectors is the allocation table
 * And the first sector are reserved for settings
 * TODO You can append it
*/
/** about files and folders
 * As written, the structs are about fsiles and folders.
 * As the ptr variable will always be 4Kib aligned, there are 12 bits available for extra settings
 * I will list the settings here: from the least significant bit from the most significant bit
 * 0: must be set if used
 * 1: set if it's a folder, unset if it's a file
 * 2-3: privilege level
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

typedef struct directory
{
    char folder_name[28]; // folder name
    uint32_t* ptr; // pointer to the next chunk
} directory_t;

struct sbf_address
{
    uint8_t sector_address;
    uint16_t byte_address;
    uint8_t flag_address;
};

typedef struct sbf_address sbf_address_t;

//this buffer is used to read and write a sector
uint8_t data_buffer[512];
//this buffer will store the information about the contents in a directory
//there are 4096 bytes in a chunk
//and is's divided into 32 bytes subchunks
//every subchunk would contain the information
char directory_content_buffer[4096];
uint32_t current_directory_lba_address;

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

uint32_t sbf_to_atla(sbf_address_t sbf_address)
{
    //formula
    return (sbf_address.sector_address - 1) * 512 * 8 + (sbf_address.byte_address) * 8 + (sbf_address.flag_address);
}

void set_allocation_table_flag(uint32_t atla_address)
{
    sbf_address_t temp = atla_to_sbf(atla_address);
    read_sector_with_retry(temp.sector_address, 100);
    data_buffer[temp.byte_address] = data_buffer[temp.byte_address] | (0x1 << (7-temp.flag_address));
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
    data_buffer[1] = 'V';
    data_buffer[2] = 'F';
    data_buffer[3] = 'S';
    write_sector(0);
    //set current
    current_directory_lba_address = 0;

    //initialize the allocation table
    data_buffer[0] = 0;
    data_buffer[1] = 0;
    data_buffer[2] = 0;
    data_buffer[3] = 0;

    for(int i = 1; i <= 32; ++i)
    {
        write_sector(i);
    }

    //the root dir is used
    //the following three chunks are used for the allocation table
    set_allocation_table_flag(0);
    set_allocation_table_flag(1);
    set_allocation_table_flag(2);
    set_allocation_table_flag(3);
    //for root
    set_allocation_table_flag(4);
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
    
    if(magic_word[0] == 'D' && magic_word[1] == 'V' && magic_word[2] == 'F' && magic_word[3] == 'S')
    {
        has_root_init = 1;
    }

    //if it's not the root, clear and initialize
    if(!has_root_init)
    {
        init_root();
    }

    //the first 32 sectors are used
    current_directory_lba_address = 32;
}

/**
 * arguments: none
 * 
 * function: this will go through the allocatio table and find an allocatable chunk
*/
int allocate_chunk()
{
    //store the data_buffer
    char temp_buffer[512];
    for(int n = 0; n < 512; ++n)
    {
        temp_buffer[n] = data_buffer[n];
    }
    int atla_result = -1;
    //get the allocation table
    for(int i = 1; i < 32; ++i)
    {
        //read
        read_sector_with_retry(i, 100);
        //check every byte in a sector
        for(int j = 0; j < 512; ++j)
        {
            for(int n = 0; n < 8; ++n)
            {
                if(((data_buffer[j] >> (7 - n)) & 0x1) == 0)
                {
                    //allocate
                    data_buffer[j] = data_buffer[j] | (0x1 << (7 - n));
                    atla_result = sbf_to_atla((sbf_address_t){i, j, n});
                    write_sector(i);
                    //restore the data buffer
                    for(int n = 0; n < 512; ++n)
                    {
                        data_buffer[n] = temp_buffer[n];
                    }
                    return atla_result;
                }
            }
        }
    }

    return atla_result;
}

void fetch_current_dir_contents(int lba_address)
{
    for (int i = 0; i < 8; ++i)
    {
        //read
        read_sector_with_retry(lba_address + i, 100);
        for (int j = 0; j < 512; ++j)
        {
            directory_content_buffer[i * 512 + j] = data_buffer[j];
        }
    }
}

//at this point, if type = 1, it's a folder, otherwise it's a file
int check_repeat_file_or_directory_name(int type, char* name)
{
    char temp[28];
    for (int i = 0; i < 28; ++i)
    {
        temp[i] = name[i];
    }
    fetch_current_dir_contents(current_directory_lba_address);
    for(int i = 0; i < 127; ++i)
    {
        //as the second bit will be 1 if it's a directory, here it will check it
        if(((directory_content_buffer[i * 32 + 31] & 0x1) != 0x1) ||
           (directory_content_buffer[i * 32 + 31] & 0x2) != (type << 1))
        {
            continue;
        }
        int same = 1;
        for(int j = 0; j < 28; ++j)
        {
            if(directory_content_buffer[i * 32 + j] != temp[j])
            {
                printf("%u", j);
                same = 0;
                break;
            }
        }
        if(same == 1)
        {
            printf("can't create file/folder with same names\n");
            return 0;
        }
    }
    return 1;
}

void create_directory(char* name)
{
    int name_len = strlen(name);
    char temp[28];
    for(int i = 0; i < 28; ++i)
    {
        if(i >= name_len)
        {
            temp[i] = '\0';
        }
        else
        {
            temp[i] = name[i];
        }
    }
    if(!check_repeat_file_or_directory_name(1, temp))
    {
        return;
    }
    //TODO error handling
    //read an entire chunk
    for(int i = 0; i < 8; ++i)
    {
        read_sector_with_retry(current_directory_lba_address + i, 100);
        for(int j = 0; j < 512; j += 32)
        {
            //get the last bytes of the 32 bytes block
            //check if the last bit of the block is 1
            if((data_buffer[j + 31] & 0x1) != 0x1)
            {
                //if not then it's empty
                //allocate
                //sort out the information
                //address, multiply by 4096 to convert to the actual byte address
                uint32_t byte_address = allocate_chunk() << 12;
                char address_buffer[4];
                address_buffer[0] = (byte_address >> 24) & 0xFF; // Most significant byte
                address_buffer[1] = (byte_address >> 16) & 0xFF;
                address_buffer[2] = (byte_address >> 8) & 0xFF;
                address_buffer[3] = byte_address & 0xFF; // Least significant byte
                //default settings
                //set present
                address_buffer[3] = address_buffer[3] | 0x1;
                //set folder
                address_buffer[3] = address_buffer[3] | 0x2;
                //name
                char name_buffer[28];
                int name_length = strlen(name);
                for(int n = 0; n < 28; ++n)
                {
                    //if exceeds the length inputed
                    if(n >= name_length)
                    {
                        name_buffer[n] = '\0';
                    }
                    else
                    {
                        //otherwise set them equal
                        name_buffer[n] = name[n];
                    }
                }
                //write to the data_buffer and write to the sector
                for(int n = 0; n < 28; ++n)
                {
                    data_buffer[j + n] = name_buffer[n];
                }
                for(int n = 28; n < 32; ++n)
                {
                    data_buffer[j + n] = address_buffer[n - 28];
                }
                write_sector(current_directory_lba_address + i);
                return;
            }
        }
    }
    printf("You will be able to create more things in a directory in the future!\n");
}

void create_file(char* name, char* file_extension)
{
    int name_len = strlen(name);
    int extension_len = strlen(file_extension);
    char temp[28];
    for(int i = 0; i < 24; ++i)
    {
        if(i >= name_len)
        {
            temp[i] = '\0';
        }
        else
        {
            temp[i] = name[i];
        }
    }
    for(int i = 0; i < 4; ++i)
    {
        if(i >= extension_len)
        {
            temp[i + 24] = '\0';
        }
        else
        {
            temp[i + 24] = file_extension[i];    
        }
    }
    if(!check_repeat_file_or_directory_name(0, temp))
    {
        return;
    }
    //TODO error handling
    //read an entire chunk
    for(int i = 0; i < 8; ++i)
    {
        read_sector_with_retry(current_directory_lba_address + i, 100);
        for(int j = 0; j < 512; j += 32)
        {
            //get the last bytes of the 32 bytes block
            //check if the last bit of the block is 1
            if((data_buffer[j + 31] & 0x1) != 0x1)
            {
                //if not then it's empty
                //allocate
                //sort out the information
                //address, multiply by 4096 to convert to the actual byte address
                uint32_t byte_address = allocate_chunk() << 12;
                char address_buffer[4];
                address_buffer[0] = (byte_address >> 24) & 0xFF; // Most significant byte
                address_buffer[1] = (byte_address >> 16) & 0xFF;
                address_buffer[2] = (byte_address >> 8) & 0xFF;
                address_buffer[3] = byte_address & 0xFF; // Least significant byte
                //default settings
                //set present
                address_buffer[3] = address_buffer[3] | 0x1;
                //set folder
                address_buffer[3] = address_buffer[3] | 0x0;
                //name
                char name_buffer[24];
                int name_length = strlen(name);
                for(int n = 0; n < 24; ++n)
                {
                    //if exceeds the length inputed
                    if(n >= name_length)
                    {
                        name_buffer[n] = '\0';
                    }
                    else
                    {
                        //otherwise set them equal
                        name_buffer[n] = name[n];
                    }
                }
                //extension
                char file_extension_buffer[4];
                int file_extension_length = strlen(file_extension);
                for(int n = 0; n < 4; ++n)
                {
                    //if exceeds the length inputed
                    if(n >= file_extension_length)
                    {
                        file_extension_buffer[n] = '\0';
                    }
                    else
                    {
                        //otherwise set them equal
                        file_extension_buffer[n] = file_extension[n];
                    }
                }
                //write to the data_buffer and write to the sector
                for(int n = 0; n < 24; ++n) 
                {
                    data_buffer[j + n] = name_buffer[n];
                }
                for(int n = 24; n < 28; ++n)
                {
                    data_buffer[j + n] = file_extension_buffer[n - 24];
                }
                for(int n = 28; n < 32; ++n)
                {
                    data_buffer[j + n] = address_buffer[n - 28];
                }
                write_sector(current_directory_lba_address + i);
                return;
            }
        }
    }
    printf("You will be able to create more things in a directory in the future!\n");
}   
