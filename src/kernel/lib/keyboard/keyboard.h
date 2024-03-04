#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../terminal/terminalio.h"

#pragma region macros

// Press scancodes
#define ESCAPE_PRESS 0x01
#define ONE_PRESS 0x02
#define TWO_PRESS 0x03
#define THREE_PRESS 0x04
#define FOUR_PRESS 0x05
#define FIVE_PRESS 0x06
#define SIX_PRESS 0x07
#define SEVEN_PRESS 0x08
#define EIGHT_PRESS 0x09
#define NINE_PRESS 0x0A
#define ZERO_PRESS 0x0B
#define MINUS_PRESS 0x0C
#define EQUAL_PRESS 0x0D
#define BACKSPACE_PRESS 0x0E
#define TAB_PRESS 0x0F
#define Q_PRESS 0x10
#define W_PRESS 0x11
#define E_PRESS 0x12
#define R_PRESS 0x13
#define T_PRESS 0x14
#define Y_PRESS 0x15
#define U_PRESS 0x16
#define I_PRESS 0x17
#define O_PRESS 0x18
#define P_PRESS 0x19
#define OPEN_BRACKET_PRESS 0x1A
#define CLOSE_BRACKET_PRESS 0x1B
#define ENTER_PRESS 0x1C
#define LEFT_CTRL_PRESS 0x1D
#define A_PRESS 0x1E
#define S_PRESS 0x1F
#define D_PRESS 0x20
#define F_PRESS 0x21
#define G_PRESS 0x22
#define H_PRESS 0x23
#define J_PRESS 0x24
#define K_PRESS 0x25
#define L_PRESS 0x26
#define SEMICOLON_PRESS 0x27
#define APOSTROPHE_PRESS 0x28
#define BACK_TICK_PRESS 0x29
#define LEFT_SHIFT_PRESS 0x2A
#define BACKSLASH_PRESS 0x2B
#define Z_PRESS 0x2C
#define X_PRESS 0x2D
#define C_PRESS 0x2E
#define V_PRESS 0x2F
#define B_PRESS 0x30
#define N_PRESS 0x31
#define M_PRESS 0x32
#define COMMA_PRESS 0x33
#define PERIOD_PRESS 0x34
#define SLASH_PRESS 0x35
#define RIGHT_SHIFT_PRESS 0x36
#define KEYPAD_ASTERISK_PRESS 0x37
#define LEFT_ALT_PRESS 0x38
#define SPACE_PRESS 0x39
#define CAPS_LOCK_PRESS 0x3A
#define F1_PRESS 0x3B
#define F2_PRESS 0x3C
#define F3_PRESS 0x3D
#define F4_PRESS 0x3E
#define F5_PRESS 0x3F
#define F6_PRESS 0x40
#define F7_PRESS 0x41
#define F8_PRESS 0x42
#define F9_PRESS 0x43
#define F10_PRESS 0x44
#define NUM_LOCK_PRESS 0x45
#define SCROLL_LOCK_PRESS 0x46
#define KEYPAD_7_PRESS 0x47
#define KEYPAD_8_PRESS 0x48
#define KEYPAD_9_PRESS 0x49
#define KEYPAD_MINUS_PRESS 0x4A
#define KEYPAD_4_PRESS 0x4B
#define KEYPAD_5_PRESS 0x4C
#define KEYPAD_6_PRESS 0x4D
#define KEYPAD_PLUS_PRESS 0x4E
#define KEYPAD_1_PRESS 0x4F
#define KEYPAD_2_PRESS 0x50
#define KEYPAD_3_PRESS 0x51
#define KEYPAD_0_PRESS 0x52
#define KEYPAD_PERIOD_PRESS 0x53
#define F11_PRESS 0x57
#define F12_PRESS 0x58
#define RIGHT_ALT_PRESS 0x38
#define KEYPAD_ENTER_PRESS 0xE0, 0x1C
#define RIGHT_CTRL_PRESS 0xE0, 0x1D
#define MULTIMEDIA_PREV_TRACK_PRESS 0xE0, 0x10
#define MULTIMEDIA_NEXT_TRACK_PRESS 0xE0, 0x19
#define KEYPAD_ENTER_PRESS 0xE0, 0x1C
#define RIGHT_CTRL_PRESS 0xE0, 0x1D
#define MULTIMEDIA_MUTE_PRESS 0xE0, 0x20
#define MULTIMEDIA_CALC_PRESS 0xE0, 0x21
#define MULTIMEDIA_PLAY_PRESS 0xE0, 0x22
#define MULTIMEDIA_STOP_PRESS 0xE0, 0x24
#define MULTIMEDIA_VOL_DOWN_PRESS 0xE0, 0x2E
#define MULTIMEDIA_VOL_UP_PRESS 0xE0, 0x30
#define MULTIMEDIA_WWW_HOME_PRESS 0xE0, 0x32
#define KEYPAD_SLASH_PRESS 0xE0, 0x35
#define HOME_PRESS 0xE0, 0x47
#define CURSOR_UP_PRESS 0xE0, 0x48
#define PAGE_UP_PRESS 0xE0, 0x49
#define CURSOR_LEFT_PRESS 0xE0, 0x4B
#define CURSOR_RIGHT_PRESS 0xE0, 0x4D
#define END_PRESS 0xE0, 0x4F
#define CURSOR_DOWN_PRESS 0xE0, 0x50
#define PAGE_DOWN_PRESS 0xE0, 0x51
#define INSERT_PRESS 0xE0, 0x52
#define DELETE_PRESS 0xE0, 0x53
#define LEFT_GUI_PRESS 0xE0, 0x5B
#define RIGHT_GUI_PRESS 0xE0, 0x5C
#define APPS_PRESS 0xE0, 0x5D
#define ACPI_POWER_PRESS 0xE0, 0x5E
#define ACPI_SLEEP_PRESS 0xE0, 0x5F
#define ACPI_WAKE_PRESS 0xE0, 0x63
#define MULTIMEDIA_WWW_SEARCH_PRESS 0xE0, 0x65
#define MULTIMEDIA_WWW_FAVORITES_PRESS 0xE0, 0x66
#define MULTIMEDIA_WWW_REFRESH_PRESS 0xE0, 0x67
#define MULTIMEDIA_WWW_STOP_PRESS 0xE0, 0x68
#define MULTIMEDIA_WWW_FORWARD_PRESS 0xE0, 0x69
#define MULTIMEDIA_WWW_BACK_PRESS 0xE0, 0x6A
#define MULTIMEDIA_MY_COMPUTER_PRESS 0xE0, 0x6B
#define MULTIMEDIA_EMAIL_PRESS 0xE0, 0x6C
#define MULTIMEDIA_MEDIA_SELECT_PRESS 0xE0, 0x6D
#define PRINT_SCREEN_PRESS 0xE0, 0x2A, 0xE0, 0x37
#define PRINT_SCREEN_RELEASE 0xE0, 0xB7, 0xE0, 0xAA
#define PAUSE_PRESS 0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5

#define RELEASE(scancode) scancode+0x80

#pragma endregion

static int keyboard[256] = {0};
static int capslock = 0;

//keycodes
typedef enum
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

void print_key(keycode keycode, char* down, char* up)
{
    if(keycode >= 10 && keycode < 36)
    {
        if(!capslock)
        {
            if(keyboard[keycode_left_shift])
            {
                printf(up);
            }
            else
            {
                printf(down);
            }
        }
        else
        {
            if(keyboard[keycode_left_shift])
            {
                printf(down);
            }
            else
            {
                printf(up);
            }
        }
    }
    else
    {
        if(keyboard[keycode_left_shift])
        {
            printf(up);
        }
        else
        {
            printf(down);
        }
    }
}

void process_key(uint8_t scancode)
{
    switch (scancode)
    {
        #pragma region numbers

        case ZERO_PRESS:
            keyboard[keycode_0] = 1;
            print_key(keycode_0, "0", ")");
            break;

        case ONE_PRESS:
            keyboard[keycode_1] = 1;
            print_key(keycode_1, "1", "!");
            break;

        case TWO_PRESS:
            keyboard[keycode_2] = 1;
            print_key(keycode_2, "2", "@");
            break;

        case THREE_PRESS:
            keyboard[keycode_3] = 1;
            print_key(keycode_3, "3", "#");
            break;

        case FOUR_PRESS:
            keyboard[keycode_4] = 1;
            print_key(keycode_4, "4", "$");
            break;

        case FIVE_PRESS:
            keyboard[keycode_5] = 1;
            print_key(keycode_5, "5", "%%");
            break;

        case SIX_PRESS:
            keyboard[keycode_6] = 1;
            print_key(keycode_6, "6", "^");
            break;

        case SEVEN_PRESS:
            keyboard[keycode_7] = 1;
            print_key(keycode_7, "7", "&");
            break;

        case EIGHT_PRESS:
            keyboard[keycode_8] = 1;
            print_key(keycode_8, "8", "*");
            break;

        case NINE_PRESS:
            keyboard[keycode_9] = 1;
            print_key(keycode_9, "9", "(");
            break;

        case RELEASE(ZERO_PRESS):
            keyboard[keycode_0] = 0;
            break;

        case RELEASE(ONE_PRESS):
            keyboard[keycode_1] = 0;
            break;

        case RELEASE(TWO_PRESS):
            keyboard[keycode_2] = 0;
            break;

        case RELEASE(THREE_PRESS):
            keyboard[keycode_3] = 0;
            break;

        case RELEASE(FOUR_PRESS):
            keyboard[keycode_4] = 0;
            break;

        case RELEASE(FIVE_PRESS):
            keyboard[keycode_5] = 0;;
            break;

        case RELEASE(SIX_PRESS):
            keyboard[keycode_6] = 0;
            break;

        case RELEASE(SEVEN_PRESS):
            keyboard[keycode_7] = 0;
            break;

        case RELEASE(EIGHT_PRESS):
            keyboard[keycode_8] = 0;
            break;

        case RELEASE(NINE_PRESS):
            keyboard[keycode_9] = 0;
            break;

        #pragma endregion

        #pragma region letters

        case A_PRESS:
            keyboard[keycode_a] = 1;
            print_key(keycode_a, "a", "A");
            break;

        case B_PRESS:
            keyboard[keycode_b] = 1;
            print_key(keycode_b, "b", "B");
            break;

        case C_PRESS:
            keyboard[keycode_c] = 1;
            print_key(keycode_c, "c", "C");
            break;

        case D_PRESS:
            keyboard[keycode_d] = 1;
            print_key(keycode_d, "d", "D");
            break;

        case E_PRESS:
            keyboard[keycode_e] = 1;
            print_key(keycode_e, "e", "E");
            break;

        case F_PRESS:
            keyboard[keycode_f] = 1;
            print_key(keycode_f, "f", "F");
            break;

        case G_PRESS:
            keyboard[keycode_g] = 1;
            print_key(keycode_g, "g", "G");
            break;

        case H_PRESS:
            keyboard[keycode_h] = 1;
            print_key(keycode_h, "h", "H");
            break;

        case I_PRESS:
            keyboard[keycode_i] = 1;
            print_key(keycode_i, "i", "I");
            break;

        case J_PRESS:
            keyboard[keycode_j] = 1;
            print_key(keycode_j, "j", "J");
            break;

        case K_PRESS:
            keyboard[keycode_k] = 1;
            print_key(keycode_k, "k", "K");
            break;

        case L_PRESS:
            keyboard[keycode_l] = 1;
            print_key(keycode_l, "l", "L");
            break;

        case M_PRESS:
            keyboard[keycode_m] = 1;
            print_key(keycode_m, "m", "M");
            break;

        case N_PRESS:
            keyboard[keycode_n] = 1;
            print_key(keycode_n, "n", "N");
            break;

        case O_PRESS:
            keyboard[keycode_o] = 1;
            print_key(keycode_o, "o", "O");
            break;

        case P_PRESS:
            keyboard[keycode_p] = 1;
            print_key(keycode_p, "p", "P");
            break;

        case Q_PRESS:
            keyboard[keycode_q] = 1;
            print_key(keycode_q, "q", "Q");
            break;

        case R_PRESS:
            keyboard[keycode_r] = 1;
            print_key(keycode_r, "r", "R");
            break;

        case S_PRESS:
            keyboard[keycode_s] = 1;
            print_key(keycode_s, "s", "S");
            break;

        case T_PRESS:
            keyboard[keycode_t] = 1;
            print_key(keycode_t, "t", "T");
            break;

        case U_PRESS:
            keyboard[keycode_u] = 1;
            print_key(keycode_u, "u", "U");
            break;

        case V_PRESS:
            keyboard[keycode_v] = 1;
            print_key(keycode_v, "v", "V");
            break;

        case W_PRESS:
            keyboard[keycode_w] = 1;
            print_key(keycode_w, "w", "W");
            break;

        case X_PRESS:
            keyboard[keycode_x] = 1;
            print_key(keycode_x, "x", "X");
            break;

        case Y_PRESS:
            keyboard[keycode_y] = 1;
            print_key(keycode_y, "y", "Y");
            break;

        case Z_PRESS:
            keyboard[keycode_z] = 1;
            print_key(keycode_z, "z", "Z");
            break;

        case RELEASE(A_PRESS):
            keyboard[keycode_a] = 0;
            break;

        case RELEASE(B_PRESS):
            keyboard[keycode_b] = 0;
            break;

        case RELEASE(C_PRESS):
            keyboard[keycode_c] = 0;
            break;

        case RELEASE(D_PRESS):
            keyboard[keycode_d] = 0;
            break;

        case RELEASE(E_PRESS):
            keyboard[keycode_e] = 0;
            break;

        case RELEASE(F_PRESS):
            keyboard[keycode_f] = 0;
            break;

        case RELEASE(G_PRESS):
            keyboard[keycode_g] = 0;
            break;

        case RELEASE(H_PRESS):
            keyboard[keycode_h] = 0;
            break;

        case RELEASE(I_PRESS):
            keyboard[keycode_i] = 0;
            break;

        case RELEASE(J_PRESS):
            keyboard[keycode_j] = 0;
            break;

        case RELEASE(K_PRESS):
            keyboard[keycode_k] = 0;
            break;

        case RELEASE(L_PRESS):
            keyboard[keycode_l] = 0;
            break;

        case RELEASE(M_PRESS):
            keyboard[keycode_m] = 0;
            break;

        case RELEASE(N_PRESS):
            keyboard[keycode_n] = 0;
            break;

        case RELEASE(O_PRESS):
            keyboard[keycode_o] = 0;
            break;

        case RELEASE(P_PRESS):
            keyboard[keycode_p] = 0;
            break;

        case RELEASE(Q_PRESS):
            keyboard[keycode_q] = 0;
            break;

        case RELEASE(R_PRESS):
            keyboard[keycode_r] = 0;
            break;

        case RELEASE(S_PRESS):
            keyboard[keycode_s] = 0;
            break;

        case RELEASE(T_PRESS):
            keyboard[keycode_t] = 0;
            break;

        case RELEASE(U_PRESS):
            keyboard[keycode_u] = 0;
            break;

        case RELEASE(V_PRESS):
            keyboard[keycode_v] = 0;
            break;

        case RELEASE(W_PRESS):
            keyboard[keycode_w] = 0;
            break;

        case RELEASE(X_PRESS):
            keyboard[keycode_x] = 0;
            break;

        case RELEASE(Y_PRESS):
            keyboard[keycode_y] = 0;
            break;

        case RELEASE(Z_PRESS):
            keyboard[keycode_z] = 0;
            break;

        #pragma endregion

        #pragma region symbols

        case BACK_TICK_PRESS:
            print_key(keycode_backtick, "`", "~");
            keyboard[keycode_backtick] = 1;
            break;

        case MINUS_PRESS:
            print_key(keycode_minus, "-", "_");
            keyboard[keycode_minus] = 1;
            break;

        case EQUAL_PRESS:
            print_key(keycode_equal, "=", "+");
            keyboard[keycode_equal] = 1;
            break;

        case OPEN_BRACKET_PRESS:
            print_key(keycode_open_bracket, "[", "{");
            keyboard[keycode_open_bracket] = 1;
            break;

        case CLOSE_BRACKET_PRESS:
            print_key(keycode_close_bracket, "]", "}");
            keyboard[keycode_close_bracket] = 1;
            break;

        case BACKSLASH_PRESS:
            print_key(keycode_backslash, "\\", "|");
            keyboard[keycode_backslash] = 1;
            break;

        case SEMICOLON_PRESS:
            print_key(keycode_semicolon, ";", ":");
            keyboard[keycode_semicolon] = 1;
            break;

        case APOSTROPHE_PRESS:
            print_key(keycode_apostrophe, "\'", "\"");
            keyboard[keycode_apostrophe] = 1;
            break;

        case COMMA_PRESS:
            print_key(keycode_comma, ",", "<");
            keyboard[keycode_comma] = 1;
            break;

        case PERIOD_PRESS:
            print_key(keycode_period, ".", ">");
            keyboard[keycode_period] = 1;
            break;

        case SLASH_PRESS:
            print_key(keycode_slash, "/", "?");
            keyboard[keycode_slash] = 1;
            break;

        case RELEASE(BACK_TICK_PRESS):
            keyboard[keycode_backtick] = 0;
            break;

        case RELEASE(MINUS_PRESS):
            keyboard[keycode_minus] = 0;
            break;

        case RELEASE(EQUAL_PRESS):
            keyboard[keycode_equal] = 0;
            break;

        case RELEASE(OPEN_BRACKET_PRESS):
            keyboard[keycode_open_bracket] = 0;
            break;

        case RELEASE(CLOSE_BRACKET_PRESS):
            keyboard[keycode_close_bracket] = 0;
            break;

        case RELEASE(BACKSLASH_PRESS):
            keyboard[keycode_backslash] = 0;
            break;

        case RELEASE(SEMICOLON_PRESS):
            keyboard[keycode_semicolon] = 0;
            break;

        case RELEASE(APOSTROPHE_PRESS):
            keyboard[keycode_apostrophe] = 0;
            break;

        case RELEASE(COMMA_PRESS):
            keyboard[keycode_comma] = 0;
            break;

        case RELEASE(PERIOD_PRESS):;
            keyboard[keycode_period] = 0;
            break;

        case RELEASE(SLASH_PRESS):
            keyboard[keycode_slash] = 0;
            break;

        #pragma endregion

        #pragma region functional

        case LEFT_SHIFT_PRESS:
            keyboard[keycode_left_shift] = 1;
            break;

        case RELEASE(LEFT_SHIFT_PRESS):
            keyboard[keycode_left_shift] = 0;
            break;

        case SPACE_PRESS:
            printf(" ");
            keyboard[keycode_space] = 1;
            break;

        case RELEASE(SPACE_PRESS):
            keyboard[keycode_space] = 0;
            break;

        case ENTER_PRESS:
            printf("\n");
            keyboard[keycode_enter] = 1;
            break;
            
        case RELEASE(ENTER_PRESS):
            keyboard[keycode_enter] = 0;
            break;

        case BACKSPACE_PRESS:
            erasef(1);
            keyboard[keycode_backspace] = 1;
            break;

        case RELEASE(BACKSPACE_PRESS):
            keyboard[keycode_backspace] = 0;
            break;

        #pragma endregion
    }
}

#endif