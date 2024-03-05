#ifndef TERMINALIO_H

#define TERMINALIO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

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

uint8_t vga_entry_color_default();

uint8_t vga_entry_color_error();

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);

uint16_t vga_entry(unsigned char uc, uint8_t color);

void terminal_initialize(void);

//customized initialization
void terminal_customize_initialize(enum vga_color fg, enum vga_color bg);

void terminal_setcolor(uint8_t color);

void terminal_moveup();

void update_cursor_position(int x, int y);

size_t strlen(const char* str);

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

void terminal_advance();

void terminal_newline();

void terminal_putchar(char c);

void printf_no_color(const char* format);

void printf(const char* format, ...);

void terminal_back();

size_t cursor_back();

void erasef(int number);

#endif