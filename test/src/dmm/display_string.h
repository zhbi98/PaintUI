
#ifndef __DISPLAY_STRING_H__
#define __DISPLAY_STRING_H__

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "display.h"
#include "fontlib.h"
#include "display_controller.h"

enum content_align {
    MANUAL_ALIGN = 0,
    CENTER_ALIGN = 1,
    LEFT_ALIGN   = 2,
    RIGHT_ALIGN  = 3,
};

enum content_layout {
    LAYOUT_R11   = 0,

    LAYOUT_R21   = 1,
    LAYOUT_R22   = 2,

    LAYOUT_R31   = 3,
    LAYOUT_R32   = 4,
    LAYOUT_R33   = 5,

    LAYOUT_R41   = 6,
    LAYOUT_R42   = 7,
    LAYOUT_R43   = 8,
    LAYOUT_R44   = 9,
};

enum content_selected {
    UNSELECT     = 0,
    SELECTED     = 1,
};

static int font_valid_width(int width, int height, unsigned char start_char, unsigned char character, const unsigned char * fontlib);
extern void read_font_valid_width(unsigned char font_size, unsigned char finish_character);
extern void display_character(int y, int x, int width, int height, unsigned int fg, unsigned int bg, unsigned char start_char, unsigned char character, const unsigned char * fontlib, unsigned char * vm);
extern void display_string(int y, int x, unsigned int fg, unsigned int bg, const unsigned char * string, unsigned char * vm);
extern void display_val(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char * vm, unsigned char * format, ...);

extern unsigned char check_gbk_size(unsigned char character);
extern unsigned short gbk_2byte_fontdata(unsigned char byte1, unsigned char byte2);
extern unsigned int find_gbk_2byte_character(unsigned short character, unsigned char * index_buf);

extern void display_gbk_cn_string(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char * vm);

extern unsigned char check_utf8_size(const unsigned char * string, unsigned char bits);
extern unsigned int unicode_to_utf8(unsigned int letter_uni);
extern unsigned short utf8_2byte_fontdata(unsigned char byte1, unsigned char byte2);
extern unsigned int utf8_3byte_fontdata(unsigned char byte1, unsigned char byte2, unsigned char byte3);
extern unsigned int find_utf8_2byte_character(unsigned short character, unsigned char * index_buf);
extern unsigned int find_utf8_3byte_character(unsigned int character, unsigned char * index_buf);

extern void display_cn_string(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char * vm);
extern void display_cn_val(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char * vm, unsigned char * format, ...);

extern unsigned int string_valid_width(unsigned char font_size, unsigned char * string);
extern unsigned int string_valid_height(unsigned char font_size, unsigned char * string);
extern void display_string_auto_place(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, unsigned char color, unsigned char font_size, unsigned char * string, unsigned char select, unsigned char * vm);

extern void display_widget_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm);
extern void display_mark_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm);
extern void display_measure_value_unit_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm);

extern void display_character_selected_digit(int y, int x, int width, int height, unsigned int fg, unsigned int bg, unsigned char start_char, unsigned char character, const unsigned char * fontlib, unsigned char * vm);
extern void display_cn_string_selected_digit(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char selected_digit, unsigned char * vm);
extern void display_string_auto_place_selected_digit(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, unsigned char color, unsigned char font_size, unsigned char * string, unsigned char select, unsigned char selected_digit, unsigned char * vm);
extern void display_main_measure_data_unit_content_selected_digit(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char selected_digit, unsigned char * vm);

extern void display_character_dmm(int y, int x, int width, int height, unsigned int fg, unsigned int bg, unsigned char start_char, unsigned char character, const unsigned char * fontlib, unsigned char * vm);
extern void display_cn_string_dmm(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char * vm);
extern void display_string_auto_place_dmm(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, unsigned char color, unsigned char font_size, unsigned char * string, unsigned char select, unsigned char * vm);
extern void display_measure_value_content_dmm(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm);

#endif
