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

static int32_t font_valid_width(int32_t width, int32_t height, uint8_t start_char, 
    uint8_t character, const uint8_t * fontlib);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * pixel line    Height -> Low
 * byte bit scan Right  <- Left
 *
 * 0x00 -> 0 0 0 0 0 0 0 0
 * 0x00 -> 0 0 0 0 0 0 0 0
 * 0xFC -> 1 1 1 1 1 1 0 0
 * 0x42 -> 0 1 0 0 0 0 1 0
 * 0x42 -> 0 1 0 0 0 0 1 0
 * 0x42 -> 0 1 0 0 0 0 1 0
 * 0x7C -> 0 1 1 1 1 1 0 0
 * 0x48 -> 0 1 0 0 1 0 0 0
 * 0x48 -> 0 1 0 0 1 0 0 0
 * 0x44 -> 0 1 0 0 0 1 0 0
 * 0x44 -> 0 1 0 0 0 1 0 0
 * 0x42 -> 0 1 0 0 0 0 1 0
 * 0xE3 -> 1 1 1 0 0 0 1 1
 * 0x00 -> 0 0 0 0 0 0 0 0
 * 0x00 -> 0 0 0 0 0 0 0 0
 * 0x00 -> 0 0 0 0 0 0 0 0
 */
static int32_t font_valid_width(int32_t width, int32_t height, uint8_t start_char, 
    uint8_t character, const uint8_t * fontlib)
{
    uint32_t space = 0;

    uint32_t bytes, total_byte;
    uint32_t faddress = 0;
    uint32_t valid_width = 0;

    /*bytes per line*/
    bytes = (int32_t)((width + 7) / 8);
    /*bytes occupied by font*/
    total_byte = bytes * height;
    character = character - start_char;
    faddress = total_byte * character;

    for (uint32_t byte = 0; byte < bytes; byte++) {
        for (uint8_t bit = 0; bit < 8; bit++) {
            for (uint32_t line = 0; line < height; line++) {
                /** 
                 * 2 bytes
                 * 0, 1    | 0 (line)
                 * 2, 3    | 1 (line)
                 * 4, 5    | 2 (line)
                 *
                 * 3 bytes
                 * 0, 1, 2 | 0 (line)
                 * 3, 4, 5 | 1 (line)
                 * 6, 7, 8 | 2 (line)
                 */
                if ((fontlib[faddress + (bytes * line + ((bytes - 1) - byte))]) & (0x01 << bit)) {
                    valid_width = bytes * 8 - space;
                    /*printf("space:%d\n", space);*/
                    return valid_width + 1;
                }
                /*printf("faddress:%d\n", faddress);*/
                /*printf("index:%d\n", */
                /*(bytes * line + ((bytes - 1) - byte)));*/
            }
            space++;
        }
    }
    valid_width = bytes * 8 - space;
    if (valid_width <= 0)
        valid_width = 1;
    /*printf("space:%d\n", space);*/
    return valid_width + 1;
}

void read_font_valid_width(uint8_t font_size, uint8_t finish_character)
{
    uint8_t font_width = 0;

    uint32_t _start = en_font[font_size].base_char;

    for (uint32_t _char = _start; _char <= finish_character; _char++) {
        font_width = font_valid_width(
            en_font[font_size].width, 
            en_font[font_size].height, 
            en_font[font_size].base_char, 
            _char, 
            en_font[font_size].fontdata
        );
        logger("/*sym:[%c] width:*/%d,", 
        _char, font_width);
    }
}

void display_character(int32_t y, int32_t x, int32_t width, int32_t height, 
    uint32_t fg, uint32_t bg, uint8_t start_char, uint8_t character, 
    const uint8_t * fontlib, uint8_t * vm)
{
    uint32_t total_byte = 0;
    uint32_t faddress = 0;
    uint32_t column = 0;

    uint32_t tx, ty;

    ty = y;
    tx = x;

    /*How many bytes are needed for a character*/
    total_byte = (int32_t)((width + 7) / 8) * height;
    character = character - start_char;
    faddress = character * total_byte;

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
                column = 0;
                ty++;
                tx = x;
                break;
            }
        }
        faddress++;
    }
}

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

uint32_t unicode_to_utf8(uint32_t letter_uni)
{
    if (letter_uni < 128) 
        return letter_uni;

    uint32_t bytes[4];

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

uint8_t utf8_1byte_fontdata(uint8_t byte)
{
    return byte;
}

uint16_t utf8_2byte_fontdata(uint8_t byte1, uint8_t byte2)
{
    uint16_t data = 0x0000;

    data = (byte1 << 8) | byte2;
    return data;
}

uint32_t utf8_3byte_fontdata(uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
    uint32_t data;

    data = ((byte1 << 16) & 0xff0000) | \
        ((byte2 << 8) & 0x00ff00) | ((byte3 << 0) & 0x0000ff);
    return data;
}

uint32_t find_utf8_1byte_character(uint8_t character, uint8_t * index_buf)
{
    uint32_t index = 0;

    while (utf8_1byte_fontdata(index_buf[index]) != character) {
        index += 1;
        if (index >= 1024) return 0;
    }
    return index / 1;
}

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

void display_cn_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, 
    uint8_t font_size, uint8_t * string, uint8_t * vm)
{
    uint32_t bits = 0;
    uint32_t index = 0;
    uint8_t utf8_size = 0;

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

void _display_cn_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, 
    uint8_t font_size, uint8_t * string, uint8_t _bs, uint8_t * vm)
{
    uint32_t index = 0;
    uint32_t bits = 0;
    uint8_t utf8_size = 0;

    uint16_t _wstr = 0;
    uint16_t _hstr = 0;

    uint8_t _fg = fg;
    uint8_t _bg = bg;

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
            /*valid_width = valid_width + font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata);*/
            index = find_utf8_1byte_character(utf8_1byte_fontdata(string[bits]), (uint8_t *)/*fontdata_1byte_index*/en_index[font_size].index_buf);
            valid_width = valid_width + en_font[font_size].widthdata[/*string[bits]*/index - en_font[font_size].base_char];
            bits++;            
        }
    }
    return valid_width;
}

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

void display_string_auto_place(uint32_t y, uint32_t x, uint8_t align, 
    uint8_t row, uint32_t widget_num, uint8_t color, uint8_t font_size, 
    uint8_t * string, uint8_t select, uint8_t * vm)
{
    uint32_t offset_y = 0, offset_x = 0;
    uint32_t last_y = 0, last_x = 0;

    uint16_t str_length = string_valid_width(font_size, string);
    uint16_t str_height = string_valid_height(font_size, string);

    uint32_t widget_w = _Area[widget_num].width;
    uint32_t widget_h = _Area[widget_num].height;

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
    case LAYOUT_R11:
        offset_y = (widget_h - str_height) / 2;
        break;
    case LAYOUT_R21:
        /*(+1) use to fine tuning the STRING_L2_1 offset_y*/
        offset_y = ((widget_h / 2 - str_height) / 2) + (1);
        break;
    case LAYOUT_R22:
        /*(-1) use to fine tuning the STRING_L2_2 offset_y*/
        offset_y = ((widget_h / 2 - str_height) / 2) + (widget_h / 2) - (1);
        break;
    case LAYOUT_R31:
        offset_y = ((widget_h / 3 - str_height) / 2);
        break;
    case LAYOUT_R32:
        offset_y = (widget_h - str_height) / 2;
        break;
    case LAYOUT_R33:
        offset_y = ((widget_h / 3 - str_height) / 2) + (widget_h / 3) * 2;
        break;
    case LAYOUT_R41:
        offset_y = ((widget_h / 4 - str_height) / 2) + (widget_h / 4) * 0;
        break;
    case LAYOUT_R42:
        offset_y = ((widget_h / 4 - str_height) / 2) + (widget_h / 4) * 1;
        break;
    case LAYOUT_R43:
        offset_y = ((widget_h / 4 - str_height) / 2) + (widget_h / 4) * 2;
        break;
    case LAYOUT_R44:
        offset_y = ((widget_h / 4 - str_height) / 2) + (widget_h / 4) * 3;
        break;
    }

    /**
     * align = 0 String position x
     * align = 1 String auto center
     * align = 2 String auto left 
     * align = 3 String auto right
     */
    switch (align) {
    case CENTER_ALIGN:
        offset_x = abs(widget_w - str_length) / 2;
        break;
    case LEFT_ALIGN:
        /*(+3) left side stay 3 piexls*/
        offset_x = 0 + (3); 
        break;
    case RIGHT_ALIGN:
        /*(-2) right side stay 2 piexls*/
        offset_x = abs(widget_w - str_length) / 2 * 2 - (2);
        break;
    }

    uint32_t widget_y = _Area[widget_num].set_y;
    uint32_t widget_x = _Area[widget_num].set_x;

    if (align != MANUAL_ALIGN) {
        last_y = widget_y + offset_y;
        last_x = widget_x + offset_x;
    } else {
        last_y = y;
        last_x = x;
    }

    if (select) {
        color = BLACK;
        display_bevel_rect(last_y, last_x, 
            str_length, str_height, WHITE, 1, vm);
    }

    display_cn_string(last_y, last_x, 
        color, 0, font_size, 
        string, vm);
}

void display_N1string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t widget_num, 
    const uint8_t * string, uint32_t string_num, uint8_t color, uint8_t select, uint8_t * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N1_PT, 
            string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N1_PT, 
            (uint8_t *)menu_content[string_num], select, vm);
    }
}

void display_N2string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t widget_num, 
    const uint8_t * string, uint32_t string_num, uint8_t color, uint8_t select, uint8_t * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N2_PT, 
            string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N2_PT, 
            (uint8_t *)menu_content[string_num], select, vm);
    }
}

void display_N3string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t widget_num, 
    const uint8_t * string, uint32_t string_num, uint8_t color, uint8_t select, uint8_t * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N3_PT, 
            string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N3_PT, 
            (uint8_t *)menu_content[string_num], select, vm);
    }
}

void display_N4string(uint32_t y, uint32_t x, uint8_t align, uint8_t row, uint32_t widget_num, 
    const uint8_t * string, uint32_t string_num, uint8_t color, uint8_t select, uint8_t * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N4_PT, 
            (uint8_t *)string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N4_PT, 
            (uint8_t *)menu_content[string_num], select, vm);
    }
}
