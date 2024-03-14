//implemented in kernel/mod/keyboard/keyboard_driver.c

#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef enum keycode
{
    //number
    keycode_0 = 0,
    keycode_1 = 1,
    keycode_2 = 2,
    keycode_3 = 3,
    keycode_4 = 4,
    keycode_5 = 5,
    keycode_6 = 6,
    keycode_7 = 7,
    keycode_8 = 8,
    keycode_9 = 9,

    //letters
    keycode_a = 10,
    keycode_b = 11,
    keycode_c = 12,
    keycode_d = 13,
    keycode_e = 14,
    keycode_f = 15,
    keycode_g = 16,
    keycode_h = 17,
    keycode_i = 18,
    keycode_j = 19,
    keycode_k = 20,
    keycode_l = 21,
    keycode_m = 22,
    keycode_n = 23,
    keycode_o = 24,
    keycode_p = 25,
    keycode_q = 26,
    keycode_r = 27,
    keycode_s = 28,
    keycode_t = 29,
    keycode_u = 30,
    keycode_v = 31,
    keycode_w = 32,
    keycode_x = 33,
    keycode_y = 34,
    keycode_z = 35,

    //symbols
    keycode_comma = 36,
    keycode_period = 37,
    keycode_slash = 38,
    keycode_semicolon = 39,
    keycode_apostrophe = 40,
    keycode_open_bracket = 41,
    keycode_close_bracket = 42,
    keycode_backslash = 43,
    keycode_backtick = 44,
    keycode_minus = 45,
    keycode_equal = 46,

    //functional keys
    keycode_tab = 47,
    keycode_caps_lock = 48,
    keycode_left_shift = 49,
    keycode_left_ctrl = 50,
    keycode_fn = 51,
    keycode_home = 52,
    keycode_left_alt = 53,
    keycode_right_alt = 54,
    keycode_right_ctrl = 55,
    keycode_pageup = 56,
    keycode_pagedown = 57,
    keycode_up = 58,
    keycode_down = 59,
    keycode_left = 60,
    keycode_right = 61,
    keycode_right_shift = 62,
    keycode_backspace = 63,
    keycode_esc = 64,
    keycode_f1 = 65,
    keycode_f2 = 66,
    keycode_f3 = 67,
    keycode_f4 = 68,
    keycode_f5 = 69,
    keycode_f6 = 70,
    keycode_f7 = 71,
    keycode_f8 = 72,
    keycode_f9 = 73,
    keycode_f10 = 74,
    keycode_f11 = 75,
    keycode_f12 = 76,
    keycode_insert = 77,
    keycode_delete = 78,
    keycode_space = 79,
    keycode_enter = 80,
} keycode;

extern int keyboard[256];
extern int capslock;

void process_key(uint8_t scancode);

#endif