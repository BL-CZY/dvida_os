#include "interpreter.h"
#include "../../lib/shell/shell.h"
#include "../../lib/utils/str_utils.h"
#include "../../lib/std/stdio.h"

char command_buffer[50];
int command_buffer_index = 0;

void echo()
{
    int i = 6;
    while(command_buffer[i] != '"')
    {
        if(i >= 50)
        {
            break;
        }
        char temp[2] = {command_buffer[i], '\0'};
        printf(temp);
        ++i;
    }
    printf("\n");
}

void clear()
{
    terminal_initialize();
}

void help()
{
    printf("Commands Available:\n");
    printf("echo - Echo a string to stdout\n");
    printf("clear - Clear the terminal output\n");
    printf("help - Display list of available commands\n");
}

void execute_command()
{
    //command search
    if(strcmp(command_buffer, "echo", 4))
    {
        echo();
    }
    else if(strcmp(command_buffer, "clear", 5))
    {
        clear();
    }
    else if(strcmp(command_buffer, "help", 4))
    {
        help();
    }
    else
    {
        printf("Command not found.\n");
    }
    command_buffer_index = 0;
    printf("root > ");
    current_io_state = stdin_command;
}
