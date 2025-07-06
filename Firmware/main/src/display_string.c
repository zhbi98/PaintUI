/**
 * @file display_string.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "display_controller.h"
#include "display_string.h"
#include "fontlib.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**
 * Calculate the valid width of a character in a font, Font data is stored with pixel lines 
 * from Height to Low, and byte bit scanning from Right to Left.
 * @param width The maximum width of the font.
 * @param height The height of the font.
 * @param start_char The ASCII code of the first character in the font library.
 * @param character The character to calculate width for.
 * @param fontlib Pointer to the font library data.
 * @return The actual width of the character in pixels.
 */
static int32_t font_valid_width(int32_t width, int32_t height, uint8_t start_char, 
    uint8_t character, const uint8_t * fontlib);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * pixel line    Height -> Low
 * byte bit scan Right  <- Left
 *

/**
 * Calculate the valid width of a character in a font, Font data is stored with pixel lines 
 * from Height to Low, and byte bit scanning from Right to Left.
 * @param width The maximum width of the font.
 * @param height The height of the font.
 * @param start_char The ASCII code of the first character in the font library.
 * @param character The character to calculate width for.
 * @param fontlib Pointer to the font library data.
 * @return The actual width of the character in pixels.
 */
static int32_t font_valid_width(int32_t width, int32_t height, uint8_t start_char, 
    uint8_t character, const uint8_t * fontlib)
{
    uint32_t bytes = (int32_t)((width + 7) / 8);
    uint32_t total_byte = bytes * height;
    character = character - start_char;
    uint32_t faddress = total_byte * character;

    uint32_t _width = 0;
    uint32_t _padding = 0;
    uint32_t _index = 0;

    for (uint32_t byte = 0; byte < bytes; byte++) {
        for (uint8_t bit = 0; bit < 8; bit++) {
            for (uint32_t line = 0; line < height; line++) {
                _index = (bytes * line) + ((bytes - 1) - byte);
                /*printf("Addr:%d:index:%d", faddress, _index);*/
                if ((fontlib[faddress + _index]) & (0x01 << bit)) {
                    _width = bytes * 8 - _padding;
                    /*printf("space:%d\n", _padding);*/
                    return _width + 1;
                }
            }
            _padding++;
        }
    }

    /** 
     * 2 bytes             /  3 bytes
     * 0, 1    | 0 (line)  /  0, 1, 2 | 0 (line)
     * 2, 3    | 1 (line)  /  3, 4, 5 | 1 (line)
     * 4, 5    | 2 (line)  /  6, 7, 8 | 2 (line)
     */

    _width = bytes * 8 - _padding;
    if (_width < 1) _width = 1;
    return _width + 1;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void read_font_valid_width(uint8_t font_size, uint8_t finish_character)
{
    uint8_t font_width = 0;

    uint32_t _start = en_font[font_size].base_char;

    for (uint32_t _char = _start; _char <= finish_character; _char++) {
        font_width = font_valid_width(en_font[font_size].width, 
            en_font[font_size].height, en_font[font_size].base_char, 
            _char, en_font[font_size].fontdata);
        logger("/*sym:[%c] width:*/%d,", 
        _char, font_width);
    }
}

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
    const uint8_t * fontlib, uint8_t * vm)
{
    uint32_t total_byte = 0; /*Total bytes per character in font data*/
    uint32_t faddress = 0; /*Font data address offset*/
    uint32_t column = 0; /*Current column counter*/

    uint32_t tx = 0, ty = 0;

    ty = y;
    tx = x;

    /*Calculate bytes needed per character (rounded up to nearest byte)*/
    total_byte = (int32_t)((width + 7) / 8) * height;
    character = character - start_char; /*Calculate character index in font library */
    faddress = character * total_byte;  /*Calculate starting address of character in font data*/

    for (int32_t i = 0; i < total_byte; i++) {
        for (int32_t j = 0; j < 8; j++) {
            if (fontlib[faddress] & (0x80 >> j)) {
                display_pixel(ty, tx, fg, vm);
            } else {
                if (bg != 0) {
                    display_pixel(ty, tx, bg, vm);
                }
            }
            tx++;
            column++;
            if (column >= width) {
                column = 0; /*Reset column counter*/
                ty++; /*Move to next line*/
                tx = x; /*Reset x position*/
                break; /*Skip remaining bits in this byte*/
            }
        }
        faddress++;
    }
}

/**
 * Determines the byte length of a UTF-8 character starting at given position.
 * @param string - Pointer to UTF-8 encoded string.
 * @param bits - Position in string to check.
 * @return Number of bytes in UTF-8 character (1-4), or 0 if invalid.
 */
uint8_t check_utf8_size(const uint8_t * string, uint8_t bits)
{
    if ((string[bits] & 0x80) == 0)
        return 1;
    else if ((string[bits] & 0xe0) == 0xc0)
        return 2;
    else if ((string[bits] & 0xf0) == 0xe0)
        return 3;
    else if ((string[bits] & 0xf8) == 0xf0)
        return 4;
    // If the char was invalid tell it's 1 byte long
    return 0;
}

/**
 * Converts a Unicode code point to UTF-8 encoding.
 * @param letter_uni - Unicode code point to convert (U+0000 to U+10FFFF).
 * @return UTF-8 encoded bytes packed into a uint32_t (1-4 bytes).
 */
uint32_t unicode_to_utf8(uint32_t letter_uni)
{
    if (letter_uni < 128) 
        return letter_uni;

    uint32_t bytes[4] = {0};

    if (letter_uni < 0x0800) {
        bytes[0] = ((letter_uni >>  6) & 0x1f) | 0xc0;
        bytes[1] = ((letter_uni >>  0) & 0x3f) | 0x80;
        bytes[2] = 0;
        bytes[3] = 0;
    } else if (letter_uni < 0x010000) {
        bytes[0] = ((letter_uni >> 12) & 0x0f) | 0xe0;
        bytes[1] = ((letter_uni >>  6) & 0x3f) | 0x80;
        bytes[2] = ((letter_uni >>  0) & 0x3f) | 0x80;
        bytes[3] = 0;
    } else if (letter_uni < 0x110000) {
        bytes[0] = ((letter_uni >> 18) & 0x07) | 0xf0;
        bytes[1] = ((letter_uni >> 12) & 0x3f) | 0x80;
        bytes[2] = ((letter_uni >>  6) & 0x3f) | 0x80;
        bytes[3] = ((letter_uni >>  0) & 0x3f) | 0x80;
    }

    uint32_t * res_p = (uint32_t *)bytes;
    return *res_p;
}

/**
 * Combines two UTF-8 bytes into a single 16-bit value for font data processing.
 * @param byte UTF-8 byte (higher byte in result).
 * @return UTF-8 bytes.
 */
uint8_t utf8_1byte_fontdata(uint8_t byte)
{
    return byte;
}

/**
 * Combines two UTF-8 bytes into a single 16-bit value for font data processing.
 * @param byte1 First UTF-8 byte (higher byte in result).
 * @param byte2 Second UTF-8 byte (lower byte in result).
 * @return Combined 16-bit value (byte1 in upper 8 bits, byte2 in lower 8 bits).
 */
uint16_t utf8_2byte_fontdata(uint8_t byte1, uint8_t byte2)
{
    uint16_t data = 0x0000;
    /**Combine bytes: shift byte1 left 8 bits and OR with byte2*/
    data = (byte1 << 8) | byte2;
    return data;
}

/**
 * Combines two UTF-8 bytes into a single 24-bit value for font data processing.
 * @param byte1 First UTF-8 byte (higher byte in result).
 * @param byte2 Second UTF-8 byte (lower byte in result).
 * @param byte3 Third UTF-8 byte (lower byte in result).
 * @return Combined 24-bit value.
 */
uint32_t utf8_3byte_fontdata(uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
    uint32_t data;

    data = ((byte1 << 16) & 0xff0000) | \
        ((byte2 << 8) & 0x00ff00) | ((byte3 << 0) & 0x0000ff);
    return data;
}

/**
 * Searches for a 1-byte UTF-8 character in a byte buffer.
 * @param character The 8-bit UTF-8 character to find (formed by byte).
 * @param index_buf Pointer to the buffer containing UTF-8 encoded characters.
 * @return The logical index (position) of the character if found, 0 if not found.
 */
uint32_t find_utf8_1byte_character(uint8_t character, uint8_t * index_buf)
{
    uint32_t index = 0;

    while (utf8_1byte_fontdata(index_buf[index]) != character) {
        index += 1;
        if (index >= 1024) return 0;
    }
    return index / 1;
}

/**
 * Searches for a 2-byte UTF-8 character in a byte buffer.
 * @param character The 16-bit UTF-8 character to find (formed by two bytes).
 * @param index_buf Pointer to the buffer containing UTF-8 encoded characters.
 * @return The logical index (position) of the character if found, 0 if not found.
 */
uint32_t find_utf8_2byte_character(uint16_t character, uint8_t * index_buf)
{
    uint32_t index = 0;

    while (utf8_2byte_fontdata(index_buf[index], 
        index_buf[index + 1]) != character
    ) {
        index += 2;
        if (index >= 1024) return 0;
    }
    return index / 2;
}

/**
 * Searches for a 3-byte UTF-8 character in a byte buffer.
 * @param character The 24-bit UTF-8 character to find (formed by two bytes).
 * @param index_buf Pointer to the buffer containing UTF-8 encoded characters.
 * @return The logical index (position) of the character if found, 0 if not found.
 */
uint32_t find_utf8_3byte_character(uint32_t character, uint8_t * index_buf)
{
    uint32_t index = 0;

    while (utf8_3byte_fontdata(index_buf[index], 
        index_buf[index + 1], index_buf[index + 2]) != character
    ) {
        index += 3;
        if (index >= 1024) return 0;
    }
    return index / 3;
}

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
    uint8_t font_size, uint8_t * string, uint8_t * vm)
{
    uint32_t bits = 0; /*Character index in font data*/
    uint32_t index = 0; /*Current byte position in string*/
    uint8_t utf8_size = 0; /*UTF-8 character byte length*/

    /**
     * UTF-8 coding rule
     * --------+---------------------------
     * 1byte   | english, italian, german
     * 2byte   | russian
     * 1-2byte | french, spanish
     * 3byte   | chinese, japan
     * --------+---------------------------
     */

    while (string[bits] != '\0') {
        utf8_size = check_utf8_size(string, bits);

        if (utf8_size == 2) {
            // Two bytes character (example: russian)
            index = find_utf8_2byte_character(utf8_2byte_fontdata(string[bits], string[bits + 1]), (uint8_t *)/*fontdata_2byte_index*/cn_index[font_size].index_buf);
            display_character(y, x, cn_font[font_size].width, cn_font[font_size].height, fg, bg, cn_font[font_size].base_char, index, cn_font[font_size].fontdata, vm);
            x = x + cn_font[font_size].width;
            bits += 2;
        } else if (utf8_size == 3) {
            // Three bytes character (example: Simplified chinese)
            index = find_utf8_3byte_character(utf8_3byte_fontdata(string[bits], string[bits + 1], string[bits + 2]), (uint8_t *)/*fontdata_3byte_index*/jp_index[font_size].index_buf);
            display_character(y, x, jp_font[font_size].width, jp_font[font_size].height, fg, bg, jp_font[font_size].base_char, index, jp_font[font_size].fontdata, vm);
            x = x + jp_font[font_size].width;
            bits += 3;
        } else {
            // One byte character (example: English)
            index = find_utf8_1byte_character(utf8_1byte_fontdata(string[bits]), (uint8_t *)/*fontdata_1byte_index*/en_index[font_size].index_buf);
            display_character(y, x, en_font[font_size].width, en_font[font_size].height, fg, bg, en_font[font_size].base_char, /*string[bits]*/index, en_font[font_size].fontdata, vm);
            /**
             * Real time dynamic calculation font width:
             * --------------------------------------------
             * x = x + font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata);
             */
            x = x + en_font[font_size].widthdata[/*string[bits]*/index - en_font[font_size].base_char];
            bits++;
        }
    }
}

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
    uint8_t font_size, uint8_t * string, uint8_t _bs, uint8_t * vm)
{
    uint32_t index = 0; /*Character index in font data*/
    uint32_t bits = 0; /*Current byte position in string*/
    uint8_t utf8_size = 0; /*UTF-8 character byte length*/

    uint16_t _wstr = 0; /*Calculated character width*/
    uint16_t _hstr = 0; /*Calculated string height*/

    uint8_t _fg = fg; /*Dynamic foreground color*/
    uint8_t _bg = bg; /*Dynamic background color*/

    /**
     * utf-8 coding rule
     * chinese: 3byte
     * english: 1byte
     * russian: 2byte
     * german : 1byte
     * french : 1-2byte
     * spanish: 1-2byte
     * italian: 1byte
     * japan  : 3byte
     */

    while (string[bits] != '\0') {
        utf8_size = check_utf8_size(string, bits);

        if (utf8_size == 2) {
            // Simplified chinese
            index = find_utf8_2byte_character(utf8_2byte_fontdata(string[bits], string[bits + 1]), (uint8_t *)/*fontdata_2byte_index*/cn_index[font_size].index_buf);
            display_character(y, x, cn_font[font_size].width, cn_font[font_size].height, fg, bg, cn_font[font_size].base_char, index, cn_font[font_size].fontdata, vm);
            x = x + cn_font[font_size].width;
            bits += 2;
        } else if (utf8_size == 3) {
            // Simplified chinese
            index = find_utf8_3byte_character(utf8_3byte_fontdata(string[bits], string[bits + 1], string[bits + 2]), (uint8_t *)/*fontdata_3byte_index*/jp_index[font_size].index_buf);
            display_character(y, x, jp_font[font_size].width, jp_font[font_size].height, fg, bg, jp_font[font_size].base_char, index, jp_font[font_size].fontdata, vm);
            x = x + jp_font[font_size].width;
            bits += 3;
        } else {
            // English
            index = find_utf8_1byte_character(string[bits], (uint8_t *)/*fontdata_1byte_index*/en_index[font_size].index_buf);
            // x = x + font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata);
            _wstr = en_font[font_size].widthdata[index - en_font[font_size].base_char];
            _hstr = string_valid_height(font_size, string);

            _fg = fg; _bg = bg;
            if ((string[bits] == '.') || (string[bits] == ',') || (string[bits] == ' ') || (string[bits] == ':') || (string[bits] == '-')) _bs++;
            if ((bits == _bs) && (string[bits] >= '0') &&  (string[bits] <= '9')) {
                display_bevel_rect(y, x, _wstr, _hstr, fg, 0, vm);
                _fg = _bg = bg;
            }

            display_character(y, x, en_font[font_size].width, en_font[font_size].height, _fg, _bg, en_font[font_size].base_char, index, en_font[font_size].fontdata, vm);
            x = x + _wstr;
            bits++;
        }
    }
}

/**
 * Calculates the total display width of a UTF-8 encoded string.
 * @param font_size Index for font size selection.
 * @param string Pointer to UTF-8 encoded string buffer.
 * @return Total pixel width required to display the string.
 */
uint32_t string_valid_width(uint8_t font_size, uint8_t * string)
{
    uint8_t bits = 0;
    uint32_t valid_width = 0;
    uint8_t utf8_size = 0;
    uint32_t index = 0;

    while (string[bits] != '\0') {
        utf8_size = check_utf8_size(string, bits);

        if (utf8_size == 2) {
            valid_width = valid_width + cn_font[font_size].width;
            bits += 2;
        } else if (utf8_size == 3) {
            valid_width = valid_width + jp_font[font_size].width;
            bits += 3;
        } else {
            /*Process 1-byte characters (e.g. English) with variable width*/
            index = find_utf8_1byte_character(utf8_1byte_fontdata(string[bits]), 
                (uint8_t *)/*fontdata_1byte_index*/en_index[font_size].index_buf);
            valid_width = valid_width + en_font[font_size]\
                .widthdata[/*string[bits]*/index - en_font[font_size].base_char];
            bits++;

            /**
             * valid_width = valid_width + font_valid_width(
             *    en_font[font_size].width, en_font[font_size].height, 
             *    en_font[font_size].base_char, string[bits], 
             *    en_font[font_size].fontdata);
             */
        }
    }
    return valid_width;
}

/**
 * Determines the display height of a UTF-8 encoded string.
 * @param font_size - Index for font size selection.
 * @param string - Pointer to UTF-8 encoded string buffer.
 * @return Pixel height of the string based on first character's font.
 */
uint32_t string_valid_height(uint8_t font_size, uint8_t * string)
{
    uint8_t utf8_size = 0;

    /*Here use first character's height*/
    utf8_size = check_utf8_size(string, 0);

    if (utf8_size == 2)
        return cn_font[font_size].height;
    else if (utf8_size == 3)
        return jp_font[font_size].height;
    else
        return en_font[font_size].height;
}

/**
 * Displays a string with specified alignment and layout within a widget area.
 * @param y Base Y coordinate (used when align=SPECIFY).
 * @param x Base X coordinate (used when align=SPECIFY).
 * @param align Text alignment (CENTER_ALIGN/LEFT_ALIGN/RIGHT_ALIGN/SPECIFY).
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
    uint8_t * string, uint8_t _invert, uint8_t * vm)
{
    uint32_t offset_y = 0, offset_x = 0; /*Vertical/horizontal offsets*/
    uint32_t last_y = 0, last_x = 0; /*Final display coordinates*/

    /*Calculate string dimensions*/
    uint16_t str_length = string_valid_width(font_size, string);
    uint16_t str_height = string_valid_height(font_size, string);

    /*Get widget dimensions*/
    uint32_t area_w = _Area[_area_idx].width;
    uint32_t area_h = _Area[_area_idx].height;

    /*Vertical positioning logic*/

    /**
     * Place row = 0 only 1 string display on center.
     * Place row = 1 only 2 string display on line 1.
     * Place row = 2 only 2 string display on line 2.
     * Place row = 3 only 3 string display on line 1.
     * Place row = 4 only 3 string display on line 2.
     * Place row = 5 only 3 string display on line 3.
     * Place row = 6 only 4 string display on line 1.
     * Place row = 7 only 4 string display on line 2.
     * Place row = 8 only 4 string display on line 3.
     * Place row = 9 only 4 string display on line 4.
     */
    switch (row) {
    case LAYOUT_R11: /*Single line center*/
        offset_y = (area_h - str_height) / 2;
        break;
    case LAYOUT_R21: /*Dual line - first line (+1px fine tuning)*/
        /*(+1) use to fine tuning the STRING_L2_1 offset_y*/
        offset_y = ((area_h / 2 - str_height) / 2) + (1);
        break;
    case LAYOUT_R22: /*Dual line - second line (-1px fine tuning)*/
        /*(-1) use to fine tuning the STRING_L2_2 offset_y*/
        offset_y = ((area_h / 2 - str_height) / 2) + (area_h / 2) - (1);
        break;
    case LAYOUT_R31: /*Triple line - first line*/
        offset_y = ((area_h / 3 - str_height) / 2);
        break;
    case LAYOUT_R32: /*Triple line - center line*/
        offset_y = (area_h - str_height) / 2;
        break;
    case LAYOUT_R33: /*Triple line - last line*/
        offset_y = ((area_h / 3 - str_height) / 2) + (area_h / 3) * 2;
        break;
    case LAYOUT_R41: /*Quad line - first line*/
        offset_y = ((area_h / 4 - str_height) / 2) + (area_h / 4) * 0;
        break;
    case LAYOUT_R42: /*Quad line - second line*/
        offset_y = ((area_h / 4 - str_height) / 2) + (area_h / 4) * 1;
        break;
    case LAYOUT_R43: /*Quad line - third line*/
        offset_y = ((area_h / 4 - str_height) / 2) + (area_h / 4) * 2;
        break;
    case LAYOUT_R44: /*Quad line - fourth line*/
        offset_y = ((area_h / 4 - str_height) / 2) + (area_h / 4) * 3;
        break;
    }

    /*Horizontal alignment logic*/

    /**
     * align = 0 String position x
     * align = 1 String auto center
     * align = 2 String auto left 
     * align = 3 String auto right
     */
    switch (align) {
    case CENTER_ALIGN: /*Center alignment*/
        offset_x = abs(area_w - str_length) / 2;
        break;
    case LEFT_ALIGN: /*Left alignment (+3px margin)*/
        /*(+3) left side stay 3 piexls*/
        offset_x = 0 + (3); 
        break;
    case RIGHT_ALIGN: /*Right alignment (-2px margin)*/
        /*(-2) right side stay 2 piexls*/
        offset_x = abs(area_w - str_length) / 2 * 2 - (2);
        break;
    }

    /*Get widget base coordinates*/
    uint32_t area_y = _Area[_area_idx].set_y;
    uint32_t area_x = _Area[_area_idx].set_x;

    /*Calculate final position*/
    if (align != SPECIFY) {
        last_y = area_y + offset_y;
        last_x = area_x + offset_x;
    } else {
        last_y = y;
        last_x = x;
    }

    /*Handle inverted display*/
    if (_invert) {
        color = BLACK;
        display_bevel_rect(last_y, last_x, 
            str_length, str_height, WHITE, 1, vm);
    }

    /*Render the string*/
    display_cn_string(last_y, last_x, 
        color, 0, font_size, 
        string, vm);
}

/**
 * Displays a string with N1 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_id=_MENU_LAST).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N1string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm)
{
    /*Display predefined menu string from content table*/
    if (str_id != _MENU_LAST) {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N1_PT, 
            (uint8_t *)menu_content[str_id], _invert, vm);
    } else {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N1_PT, 
            str_p, _invert, vm);
    }
}

/**
 * Displays a string with N2 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_id=_MENU_LAST).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N2string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm)
{
    /*Display predefined menu string from content table*/
    if (str_id != _MENU_LAST) {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N2_PT, 
            (uint8_t *)menu_content[str_id], _invert, vm);
    } else {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N2_PT, 
            str_p, _invert, vm);
    }
}

/**
 * Displays a string with N3 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_id=_MENU_LAST).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N3string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm)
{
    /*Display predefined menu string from content table*/
    if (str_id != _MENU_LAST) {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N3_PT, 
            (uint8_t *)menu_content[str_id], _invert, vm);
    } else {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N3_PT, 
            str_p, _invert, vm);
    }
}

/**
 * Displays a string with N4 (Normal-1) font style with flexible content source.
 * @param y Base Y coordinate for manual alignment.
 * @param x Base X coordinate for manual alignment.
 * @param align Text alignment (CENTER/LEFT/RIGHT/MANUAL).
 * @param row Layout row configuration (LAYOUT_R11 to LAYOUT_R44).
 * @param _area_idx Index of the display area in _Area array.
 * @param str_p Pointer to direct string content (used when str_id=_MENU_LAST).
 * @param str_id Menu content ID from predefined strings.
 * @param color Text display color.
 * @param _invert Inversion flag (1=inverted colors).
 * @param vm Video memory buffer pointer.
 */
void display_N4string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t _area_idx, 
    const uint8_t * str_p, uint32_t str_id, uint8_t color, uint8_t _invert, uint8_t * vm)
{
    /*Display predefined menu string from content table*/
    if (str_id != _MENU_LAST) {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N4_PT, 
            (uint8_t *)menu_content[str_id], _invert, vm);
    } else {
        display_string_align(y, x, align, row, _area_idx, color, FONT_N4_PT, 
            (uint8_t *)str_p, _invert, vm);
    }
}
