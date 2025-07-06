/**
 * @file display_string.h
 *
 */

#ifndef __DISPLAY_STRING_H__
#define __DISPLAY_STRING_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>
#include <stdlib.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    MANUAL_ALIGN = 0,
    CENTER_ALIGN,
    LEFT_ALIGN,
    RIGHT_ALIGN,
    _ALIGN_LAST,
};

typedef uint8_t _align_t;

enum {
    LAYOUT_R11 = 0,
    LAYOUT_R21,
    LAYOUT_R22,
    LAYOUT_R31,
    LAYOUT_R32,
    LAYOUT_R33,
    LAYOUT_R41,
    LAYOUT_R42,
    LAYOUT_R43,
    LAYOUT_R44,
    _LAYOUT_LAST,
};

typedef uint8_t _layout_t;

enum {
    UNSELECT = 0,
    SELECTED,
    _LAST,
};

typedef uint8_t _selected_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void display_character(int32_t y, int32_t x, int32_t width, int32_t height, 
    uint32_t fg, uint32_t bg, uint8_t start_char, uint8_t character, const uint8_t * fontlib, uint8_t * vm);
uint8_t check_utf8_size(const uint8_t * string, uint8_t bits);
uint32_t unicode_to_utf8(uint32_t letter_uni);
uint8_t utf8_1byte_fontdata(uint8_t byte);
uint16_t utf8_2byte_fontdata(uint8_t byte1, uint8_t byte2);
uint32_t utf8_3byte_fontdata(uint8_t byte1, uint8_t byte2, uint8_t byte3);
uint32_t find_utf8_1byte_character(uint8_t character, uint8_t * index_buf);
uint32_t find_utf8_2byte_character(uint16_t character, uint8_t * index_buf);
uint32_t find_utf8_3byte_character(uint32_t character, uint8_t * index_buf);
void read_font_valid_width(uint8_t font_size, uint8_t finish_character);
void display_cn_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, uint8_t font_size, uint8_t * string, uint8_t * vm);
void _display_cn_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, uint8_t font_size, uint8_t * string, uint8_t _bs, uint8_t * vm);
uint32_t string_valid_width(uint8_t font_size, uint8_t * string);
uint32_t string_valid_height(uint8_t font_size, uint8_t * string);
void display_string_align(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, uint8_t color, uint8_t font_size, 
    uint8_t * string, uint8_t _invert, uint8_t * vm);
void display_N1string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);
void display_N2string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);
void display_N3string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);
void display_N4string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);

#endif /*__DISPLAY_STRING_H__*/
