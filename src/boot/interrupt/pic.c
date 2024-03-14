#include "../../kernel/lib/utils/pic_utils.h"
#include "pic.h"

// a port is an entry for input/output, such as keyboard and sound

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

/**
 * ICW1 -- initialization control word
 * 
 * 0 0 0 0 _ _ _ _
 * *5-7 are ignored, so 0
 * 
 * *set
 * 0: ICW4, if set the PIC wants to receive the ICW4
 * 
 * 1: SGNL, if set there is only 1 PIC
 *          if unset there are two and an ICW3 must be sent(for the slave PIC ig)
 * 
 * 2: ADI, ignored, 0
 * 
 * 3: LTIM, 1 --> level triggered mode: if the device actually needs attention
 *          0 --> edge triggered mode: always ensure that a device is not in a interrupt state
 *          *↑ is the mode that we use
 * 
 * *set
 * 4: INIT, set to 1 to init the PIC
*/

/**
 * ICW2
 * 
 * it's basically the offset
 * but as the last three digits are ignored, it has to be a multiple of 8
*/

/**
 * ICW3
 * 
 * Master:
 * (1) _ _ _ _ _ _ _ _
 * generally saying that if the ir input has a slave or not
 * 
 * *the ir2 is connected to the interrupt of the slave PIC
 * 
 * Slave:
 * (1) 0 0 0 0 0 _ _ _
 * this is from where in the Master PIC is the ir from
 * *2 --> 0 1 0 we are using this one
 * 1 --> 001
 * 3 --> 011
 * ...
 * 
*/

/**
 * ICW4
 * 
 * (1) 0 0 0 _ _ _ _ _
 * 
 * *x86 uses 1
 * 0: if set, it's 8086/8088 mode
 *    if unset, it's MCS 80/85 mode
 * 
 * *no for now
 * 1: if set, the cpu will auto send the end of interrupt message
 * 
 * *x86 doesn't need this
 * 2&3: buffered or not
 * 
 * *doesn't matter for x86
 * 4: if set, special fully nested mode
 *    otherwise, not special fully nested mode
 * fully nested mode refers to the mode in which the cpu will prioritize the interrupt based on its number
 * for example, IR0 would have a higher priority
 * but with multiple PICs, it will produce misunderstandings due to numberings
 * *special fully nested mode won't do so
 * *but x86 doesn't need that anyways
*/

/**
 * mask: masked --> disabled
 *       viceversa
 * 1 --> masked
 * 0 --> unmasked
*/

/**
 * arguments:
 *  
*/
void pic_config(uint8_t offset_pic1, uint8_t offset_pic2)
{
    //ICW1
    //the 0th and the 4th are set
    outb(PIC1_COMMAND_PORT, 0b00010001);
    //the chip is not that fast, so wait
    io_wait();
    outb(PIC2_COMMAND_PORT, 0b00010001);
    io_wait();

    //ICW2
    outb(PIC1_DATA_PORT, offset_pic1);
    io_wait();
    outb(PIC2_DATA_PORT, offset_pic2);
    io_wait();

    //ICW3
    outb(PIC1_DATA_PORT, 0b00000100);
    io_wait();
    outb(PIC2_DATA_PORT, 0b00000010);
    io_wait();

    //ICW4
    outb(PIC1_DATA_PORT, 0b00000001);
    io_wait();
    outb(PIC2_DATA_PORT, 0b00000001);
    io_wait();

    //clear registers
    outb(PIC1_DATA_PORT, 0);
    outb(PIC2_DATA_PORT, 0);
}

//mask a port
void mask_pic_port(int irq)
{
    uint8_t port;
    if(irq >= 8)
    {
        //if irq >= 8, it's modifiying the PIC2
        irq -= 8;
        port = PIC2_DATA_PORT;
    }
    else
    {
        port = PIC1_DATA_PORT;
    }

    uint8_t mask = inb(port); //get the current mask info
    outb(port, mask | (1 << irq)); //mask the port
}

//unmask a port
void unmask_pic_port(int irq)
{
    uint8_t port;
    if(irq >= 8)
    {
        //if irq >= 8, it's modifiying the PIC2
        irq -= 8;
        port = PIC2_DATA_PORT;
    }
    else
    {
        port = PIC1_DATA_PORT;
    }

    uint8_t mask = inb(port); //get the current mask info
    //~ means not
    outb(port, mask & ~(1 << irq)); //mask the port
}

//mask all
void mask_all_pic_ports()
{
    //mask all
    outb(PIC1_DATA_PORT, 0b11111111);
    io_wait();
    outb(PIC2_DATA_PORT, 0b11111111);
    io_wait();
}

//unmask all
void unmask_all_pic_ports()
{
    //mask all
    outb(PIC1_DATA_PORT, 0b00000000);
    io_wait();
    outb(PIC2_DATA_PORT, 0b00000000);
    io_wait();
}

/**
 * OCW2
 * end of interrupts:
 * 001 --> non-specific
 * 011 --> specific
*/

void pic_send_end_of_interrupt(int irq)
{
    if(irq >= 8)
    {
        //both non-specific
        outb(PIC2_COMMAND_PORT, 0b00100000);
    }
    outb(PIC1_COMMAND_PORT, 0b00100000);
}

/**
 * IRR and ISR
 * IRR interrupt request register, is the interrupt that is called
 * ISR in-service register, is the interrupt that is now being serviced
 * 
 * ICW3
 * 0 0 0 0 0 _ _ _
 * 
 * *set to 1
 * 3: if set --> poll command, which means that the IRQ(interrupt request) can check the request without
 *               servicing it
 * 
 * 2: doesn't matter for now
 * 
 * *set to 1
 * 1: set to read
 * 
 * 0: unset for IRR
 *    set for ISR
*/

uint16_t read_pic_irr()
{
    outb(PIC1_COMMAND_PORT, 0b00001010); //output command
    outb(PIC2_COMMAND_PORT, 0b00001010);
    return (uint16_t)(inb(PIC2_COMMAND_PORT)) | ((uint16_t)(inb(PIC1_COMMAND_PORT)) << 8); //read in value
}

uint16_t read_pic_isr()
{
    outb(PIC1_COMMAND_PORT, 0b00001011);
    outb(PIC2_COMMAND_PORT, 0b00001011);
    return (uint16_t)(inb(PIC2_COMMAND_PORT)) | ((uint16_t)(inb(PIC1_COMMAND_PORT)) << 8); //read in value
}

void pic_init()
{
    pic_config(0x20, 0x28);
}