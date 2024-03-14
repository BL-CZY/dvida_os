#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>
#include "../../lib/std/keyboard.h"

void end_of_command();
void process_stdin_common(keycode keycode, char* down, char* up);
void process_stdin_common(keycode keycode, char* down, char* up);
void process_stdin_command(keycode keycode, char* down, char* up);
void process_stdin_data(keycode keycode, char* down, char* up);
void process_printable_key(keycode keycode, char* down, char* up);

#endif