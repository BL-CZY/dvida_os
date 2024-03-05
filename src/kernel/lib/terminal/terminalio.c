#include "terminalio.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

uint8_t vga_entry_color_default()
{
    return VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;
}

uint8_t vga_entry_color_error()
{
    return VGA_COLOR_RED | VGA_COLOR_BLACK << 4;
}

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
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

uint16_t vga_entry(unsigned char uc, uint8_t color)
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

//ouput

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len])
    {
        ++len;
    }
    return len;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_advance()
{
    if(++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        ++terminal_row;
    }
    if(terminal_row == VGA_HEIGHT)
    {
        update_cursor_position(terminal_column, terminal_row - 1);
    }
    else
    {
        update_cursor_position(terminal_column, terminal_row);
    }
}

void terminal_newline()
{
    ++terminal_row;
    terminal_column = 0;
    if(terminal_row == VGA_HEIGHT)
    {
        terminal_moveup();
    }
    if(terminal_row == VGA_HEIGHT)
    {
        update_cursor_position(terminal_column, terminal_row - 1);
    }
    else
    {
        update_cursor_position(terminal_column, terminal_row);
    }
}

void terminal_putchar(char c)
{
    if(terminal_row == VGA_HEIGHT)
    {
        terminal_moveup();
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    //next line or new page
    terminal_advance();
}

void printf_no_color(const char* format)
{
    for(size_t i = 0; i < strlen(format); ++i)
    {
        terminal_putchar(format[i]);
    }
}

__attribute__((cdecl))
void printf(const char* format, ...)
{
    size_t length = strlen(format);
    terminal_color = vga_entry_color_default();
    va_list args;
    va_start(args, format);

    for(size_t i = 0; i < length; ++i)
    {
        switch(format[i])
        {
            case '\n':
                terminal_newline();
                break;
                
            case '%':
                switch(format[++i])
                {
                    case '%':
                        terminal_putchar('%');
                        break;

                    case 'c': //stands for color
                        switch(format[++i])
                        {
                            case 'd': //stands for default
                                terminal_color = vga_entry_color_default();
                                break;

                            case 'e': //stands for error
                                terminal_color = vga_entry_color_error();
                                break;

                            case 'c': //stands for customized
                                uint8_t color_ptr = (uint8_t)va_arg(args, int);
                                terminal_color = color_ptr;
                                break;
                        }
                        break;

                    case 's': //stands for string
                        char* str = va_arg(args, char*);
                        printf_no_color(str);
                        break;

                    case 'u': //stands for unsigned int
                        uint32_t num = (uint32_t)va_arg(args, int);
                        char buffer[10];
                        int ind = 0;
                        if(num == 0)
                        {
                            terminal_putchar('0');
                        }
                        while(num != 0)
                        {
                            buffer[ind] = '0' + num % 10;
                            num /= 10;
                            ++ind;
                        }
                        --ind;
                        while(ind >= 0)
                        {
                            terminal_putchar(buffer[ind]);
                            --ind;
                        }
                        break;
                }
                break;

            default:
                terminal_putchar(format[i]);
        }
    }

    terminal_color = vga_entry_color_default();
}

void terminal_back()
{
    if(terminal_column != 0)
    {
        --terminal_column;
    }
    else
    {
        if(terminal_row != 0)
        {
            --terminal_row;
            terminal_column = VGA_WIDTH - 1;
        }
    }
    update_cursor_position(terminal_column, terminal_row);
}

size_t cursor_back()
{
    size_t cursor_column = terminal_column;
    size_t cursor_row = terminal_row;
    if(cursor_column != 0)
    {
        --cursor_column;
    }
    else
    {
        if(cursor_row != 0)
        {
            --cursor_row;
            cursor_column = VGA_WIDTH - 1;
        }
    }
    return cursor_row * VGA_WIDTH + cursor_column;
}

void erasef(int number)
{
    for(int i = 0; i < number; ++i)
    {
        terminal_back();
        const size_t index = terminal_row * VGA_WIDTH + terminal_column;
        terminal_buffer[index] = vga_entry('\0', terminal_color);

        while((uint8_t)terminal_buffer[cursor_back()] == (uint8_t)'\0' && !terminal_column == 0)
        {
            terminal_back();
        }
    }
}