#ifndef TERMINAL_H

#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>
#include "../../modules/interrupt/pic/io.h"

//defining colorcodes
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

static inline uint8_t vga_entry_color_default(void);
static inline uint8_t vga_entry_color_error(void);
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
static inline uint16_t vga_entry(unsigned char uc, uint8_t color);
void terminal_initialize(void);
void terminal_customize_initialize(enum vga_color fg, enum vga_color bg);
void terminal_setcolor(uint8_t color);
void terminal_moveup(void);

//terminal color setting

static inline uint8_t vga_entry_color_default()
{
    return VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;
}

static inline uint8_t vga_entry_color_error()
{
    return VGA_COLOR_RED | VGA_COLOR_BLACK << 4;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4; 
    //uint8_t: unsigned int with 8 bits which is the type(_t)
    //the color codes are stored in a byte
    /**
     * 0 0 0 0 0 0 0 0
     * bg << 4 would shift it to the higher 4
     * b b b b 0 0 0 0
     * 0 0 0 0 f f f f
     * | is bitwise or, which will make it
     * b b b b f f f f 
    */
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    //an unsigned char is a byte that can represent ASCII value
    return (uint16_t)uc | (uint16_t)color << 8;
    /**
     * 0 0 0 0 0 0 0 0 u u u u u u u u
     * c c c c c c c c 0 0 0 0 0 0 0 0
     * 
     * structure:
     * bg color 4bits
     * font color 4bits
     * ASCII code 8bits
    */
}

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*)0xB8000;//the output device is located at 0xB8000

    for(size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry('\0', terminal_color);
            /**
             * terminal_buffer[index] represents the address terminal_buffer + index, and we are going
             * to change the content there. also, the terminal is emptied as we fill it with ' '
            */
        }
    }
}

//customized initialization
void terminal_customize_initialize(enum vga_color fg, enum vga_color bg)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(fg, bg);
    terminal_buffer = (uint16_t*)0xB8000;//the output device is located at 0xB8000

    for(size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry('\0', terminal_color);
            /**
             * terminal_buffer[index] represents the address terminal_buffer + index, and we are going
             * to change the content there. also, the terminal is emptied as we fill it with ' '
            */
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_moveup()
{
    //TODO: in the future store the commands somewhere so that terminal_movedown() can be implemented

    for(size_t y = 1; y < VGA_HEIGHT; ++y)
    {
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t original = (y - 1) * VGA_WIDTH + x;
            const size_t rewrite = y * VGA_WIDTH + x;
            terminal_buffer[original] = terminal_buffer[rewrite]; 
        }
    }

    for(size_t x = 0; x < VGA_WIDTH; ++x)
    {
        terminal_buffer[(VGA_HEIGHT - 1) * (VGA_WIDTH) + x] = vga_entry(' ', terminal_color);
    }
    
    --terminal_row;
}

void update_cursor_position(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

#endif
