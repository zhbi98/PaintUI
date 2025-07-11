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
    ALIGN_SPECIFY = 0,
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
    _ALIGN_LAST,
};

typedef uint8_t _align_t;

enum {
    INVE_NONE = 0,
    INVE_EN,
    _INV_LAST,
};

typedef uint8_t _inverse_t;

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

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void read_font_valid_width(uint8_t font_size, uint8_t finish_character);

/**
 * Displays a single character on screen using a bitmap font.
 * @param y Starting Y coordinate (top position).
 * @param x Starting X coordinate (left position).
 * @param width Width of each character in pixels.
 * @param height Height of each character in pixels.
 * @param fg Foreground color (pixel on).
 * @param bg Background color (pixel off, 0 means transparent).
 * @param start_char First character in font library.
 * @param character Character to display.
 * @param fontlib Pointer to font bitmap data.
 * @param vm Pointer to video memory/framebuffer.
 */
void display_character(int32_t y, int32_t x, int32_t width, int32_t height, 
    uint32_t fg, uint32_t bg, uint8_t start_char, uint8_t character, 
    const uint8_t * fontlib, uint8_t * vm);

/**
 * Determines the byte length of a UTF-8 character starting at given position.
 * @param string - Pointer to UTF-8 encoded string.
 * @param bits - Position in string to check.
 * @return Number of bytes in UTF-8 character (1-4), or 0 if invalid.
 */
uint8_t check_utf8_size(const uint8_t * string, uint8_t bits);

/**
 * Converts a Unicode code point to UTF-8 encoding.
 * @param letter_uni - Unicode code point to convert (U+0000 to U+10FFFF).
 * @return UTF-8 encoded bytes packed into a uint32_t (1-4 bytes).
 */
uint32_t unicode_to_utf8(uint32_t letter_uni);

/**
 * Combines two UTF-8 bytes into a single 16-bit value for font data processing.
 * @param byte UTF-8 byte (higher byte in result).
 * @return UTF-8 bytes.
 */
uint8_t utf8_1byte_fontdata(uint8_t byte);

/**
 * Combines two UTF-8 bytes into a single 16-bit value for font data processing.
 * @param byte1 First UTF-8 byte (higher byte in result).
 * @param byte2 Second UTF-8 byte (lower byte in result).
 * @return Combined 16-bit value (byte1 in upper 8 bits, byte2 in lower 8 bits).
 */
uint16_t utf8_2byte_fontdata(uint8_t byte1, uint8_t byte2);

/**
 * Combines two UTF-8 bytes into a single 24-bit value for font data processing.
 * @param byte1 First UTF-8 byte (higher byte in result).
 * @param byte2 Second UTF-8 byte (lower byte in result).
 * @param byte3 Third UTF-8 byte (lower byte in result).
 * @return Combined 24-bit value.
 */
uint32_t utf8_3byte_fontdata(uint8_t byte1, uint8_t byte2, uint8_t byte3);

/**
 * Searches for a 1-byte UTF-8 character in a byte buffer.
 * @param character The 8-bit UTF-8 character to find (formed by byte).
 * @param index_buf Pointer to the buffer containing UTF-8 encoded characters.
 * @return The logical index (position) of the character if found, 0 if not found.
 */
uint32_t find_utf8_1byte_character(uint8_t character, uint8_t * index_buf);

/**
 * Searches for a 2-byte UTF-8 character in a byte buffer.
 * @param character The 16-bit UTF-8 character to find (formed by two bytes).
 * @param index_buf Pointer to the buffer containing UTF-8 encoded characters.
 * @return The logical index (position) of the character if found, 0 if not found.
 */
uint32_t find_utf8_2byte_character(uint16_t character, uint8_t * index_buf);

/**
 * Searches for a 3-byte UTF-8 character in a byte buffer.
 * @param character The 24-bit UTF-8 character to find (formed by two bytes).
 * @param index_buf Pointer to the buffer containing UTF-8 encoded characters.
 * @return The logical index (position) of the character if found, 0 if not found.
 */
uint32_t find_utf8_3byte_character(uint32_t character, uint8_t * index_buf);

/**
 * Displays a UTF-8 encoded string with multi-language support.
 * @param y Vertical starting position (row coordinate).
 * @param x Horizontal starting position (column coordinate).
 * @param fg Foreground color (RGB format).
 * @param bg Background color (RGB format).
 * @param font_size Index for font size selection.
 * @param string Pointer to UTF-8 encoded string buffer.
 * @param vm Pointer to video memory buffer.
 */
void display_cn_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, 
    uint8_t font_size, uint8_t * string, uint8_t * vm);

/**
 * Displays UTF-8 encoded multi-language string with special formatting.
 * @param y Vertical start position (row coordinate).
 * @param x Horizontal start position (column coordinate).
 * @param fg Foreground color (RGB format).
 * @param bg Background color (RGB format).
 * @param font_size Index for font size selection.
 * @param string Pointer to UTF-8 encoded string buffer.
 * @param _bs Special character position marker.
 * @param vm Pointer to video memory buffer.
 */
void _display_cn_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, 
    uint8_t font_size, uint8_t * string, uint8_t _bs, uint8_t * vm);

/**
 * Calculates the total display width of a UTF-8 encoded string.
 * @param font_size Index for font size selection.
 * @param string Pointer to UTF-8 encoded string buffer.
 * @return Total pixel width required to display the string.
 */
uint32_t string_valid_width(uint8_t font_size, uint8_t * string);

/**
 * Determines the display height of a UTF-8 encoded string.
 * @param font_size - Index for font size selection.
 * @param string - Pointer to UTF-8 encoded string buffer.
 * @return Pixel height of the string based on first character's font.
 */
uint32_t string_valid_height(uint8_t font_size, uint8_t * string);

/**
 * Displays a string with specified alignment and layout within a widget area.
 * @param y Base Y coordinate (used when align=ALIGN_SPECIFY).
 * @param x Base X coordinate (used when align=ALIGN_SPECIFY).
 * @param align Text alignment (ALIGN_CENTER/ALIGN_LEFT/ALIGN_RIGHT/ALIGN_SPECIFY).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the widget area in _Area array.
 * @param color Text color.
 * @param font_size Font size index.
 * @param string Pointer to UTF-8 encoded string.
 * @param _invert Flag for inverted color display.
 * @param vm Video memory buffer pointer.
 *
 * Features:
 * - Supports multi-line text layouts (1-4 lines).
 * - Provides horizontal alignment options.
 * - Handles inverted color rendering.
 * - Works with widget area dimensions.
 */
void display_string_align(uint32_t y, uint32_t x, uint8_t align, 
    uint8_t row, uint32_t _area_idx, uint8_t color, uint8_t font_size, 
    uint8_t * string, uint8_t _invert, uint8_t * vm);

/**
 * Displays a string with N1 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_p!=NULL).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N1string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);

/**
 * Displays a string with N2 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_p!=NULL).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N2string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);

/**
 * Displays a string with N3 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_p!=NULL).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N3string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);

/**
 * Displays a string with N4 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_p!=NULL).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N4string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm);

#endif /*__DISPLAY_STRING_H__*/
