
#include "display_string.h"

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
static int font_valid_width(int width, int height, unsigned char start_char, unsigned char character, const unsigned char * fontlib)
{
    unsigned int space = 0;

    unsigned int bytes, total_byte;
    unsigned long faddress = 0;
    unsigned int valid_width = 0;

    // bytes per line
    bytes = (int)((width + 7) / 8);
    // bytes occupied by font
    total_byte = bytes * height;
    character = character - start_char;
    faddress = total_byte * character;

    for (unsigned int byte = 0; byte < bytes; byte++) {
        for (unsigned char bit = 0; bit < 8; bit++) {
            for (unsigned int line = 0; line < height; line++) {
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
                    // printf("space:%d\n", space);
                    return valid_width + 1;
                }
                // printf("faddress:%d\n", faddress);
                // printf("index:%d\n", 
                // (bytes * line + ((bytes - 1) - byte)));
            }
            space++;
        }
    }
    valid_width = bytes * 8 - space;
    if (valid_width <= 0)
        valid_width = 1;
    // printf("space:%d\n", space);
    return valid_width + 1;
}

void read_font_valid_width(unsigned char font_size, unsigned char finish_character)
{
    unsigned char font_width = 0;

    // example:
    // read_font_valid_width(FONT_N2_PT, 'z');
    for (unsigned int character = en_font[font_size].base_char; character <= finish_character; character++) {
        font_width = font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, character, en_font[font_size].fontdata);
        printf("character:[%c] font width:%d,\n", character, font_width);
    }
}

void display_character(int y, int x, int width, int height, unsigned int fg, unsigned int bg, unsigned char start_char, unsigned char character, const unsigned char * fontlib, unsigned char * vm)
{
    unsigned int total_byte = 0;
    unsigned long faddress = 0;
    unsigned int column = 0;

    unsigned int tx, ty;

    ty = y;
    tx = x;

    // How many bytes are needed for a character
    total_byte = (int)((width + 7) / 8) * height;
    character = character - start_char;
    faddress = character * total_byte;

    for (int i = 0; i < total_byte; i++) {
        for (int j = 0; j < 8; j++) {
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

unsigned int find_ascii_character(unsigned char character, unsigned char * index_buf)
{
    unsigned int index = 0;

    // printf("byte: %xH", character);
    while (index_buf[index] != character) {
        index += 1;
        if (index >= 1024)
            return 0;
    }
    // printf("font index: %d", index);
    return index / 1;
}

void display_string(int y, int x, unsigned int fg, unsigned int bg, const unsigned char * string, unsigned char * vm)
{
    // Multi-language mixed display is not supported
    unsigned char bits = 0;
    unsigned int index = 0;

    while (string[bits] != '\0') {
        /**
         * Displays the original writing of characters:
         * ---------------------------------------------
         * display_character(y, x, 12, 16, fg, bg, ' ', string[bits], fontdata_en12x16, vm);
         * x = x + font_valid_width(12, 16, ' ', string[bits], fontdata_en12x16);
         * bits++;
         */

        index = find_ascii_character(string[bits], (unsigned char *)/*fontdata_2byte_index*/en_index[FONT_N1_PT].index_buf);
        display_character(y, x, en_font[FONT_N1_PT].width, en_font[FONT_N1_PT].height, fg, bg, en_font[FONT_N1_PT].base_char, /*string[bits]*/index, en_font[FONT_N1_PT].fontdata, vm);
        /**
         * Real time dynamic calculation font width:
         * ---------------------------------------------
         * x = x + font_valid_width(en_font[FONT_N1_PT].width, en_font[FONT_N1_PT].height, en_font[FONT_N1_PT].base_char, string[bits], en_font[FONT_N1_PT].fontdata);
         */
        x = x + en_font[FONT_N1_PT].widthdata[string[bits] - en_font[FONT_N1_PT].base_char];
        bits++;
    }
}

void display_val(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char * vm, unsigned char * format, ...)
{
    // Multi-language mixed display is not supported
    unsigned char value[128];

    va_list parameter_pointer;

    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string(y, x, fg, bg, value, vm);
}

unsigned char check_gbk_size(unsigned char character)
{
    // printf("character: %xH", character);
    if ((character >= 0x00) && (character <= 0x7f))
        // English 1 byte
        return 1;
    if ((character >= 0xb0) && (character <= 0xf7))
        // Simplified chinese 2 bytes
        return 2;
    return 255;
}

unsigned char gbk_1byte_fontdata(unsigned char byte)
{
    return byte;
}

unsigned short gbk_2byte_fontdata(unsigned char byte1, unsigned char byte2)
{
    unsigned short data;

    data = (byte1 << 8) | byte2;
    return data;
}

unsigned int find_gbk_1byte_character(unsigned char character, unsigned char * index_buf)
{
    unsigned int index = 0;

    // printf("byte: %xH", character);
    while (gbk_2byte_fontdata(index_buf[index], index_buf[index + 1]) != character) {
        index += 1;
        if (index >= 1024)
            return 0;
    }
    // printf("font index: %d", index);
    return index / 1;
}

unsigned int find_gbk_2byte_character(unsigned short character, unsigned char * index_buf)
{
    unsigned int index = 0;

    // printf("byte: %xH", character);
    while (gbk_2byte_fontdata(index_buf[index], index_buf[index + 1]) != character) {
        index += 2;
        if (index >= 1024)
            return 0;
    }
    // printf("font index: %d", index);
    return index / 2;
}

void display_gbk_cn_string(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char * vm)
{
    unsigned int bits = 0;
    unsigned int index = 0;

    while (string[bits] != '\0') {
        if (check_gbk_size(string[bits]) == 2) {
            // Simplified chinese
            index = find_gbk_2byte_character(gbk_2byte_fontdata(string[bits], string[bits + 1]), (unsigned char *)/*fontdata_2byte_index*/cn_index[font_size].index_buf);
            display_character(y + 1, x, cn_font[font_size].width, cn_font[font_size].height, fg, bg, cn_font[font_size].base_char, index, cn_font[font_size].fontdata, vm);
            x = x + cn_font[font_size].width;
            bits += 2;
        } else {
            // English
            index = find_gbk_1byte_character(gbk_1byte_fontdata(string[bits]), (unsigned char *)/*fontdata_2byte_index*/en_index[font_size].index_buf);
            display_character(y, x, en_font[font_size].width, en_font[font_size].height, fg, bg, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata, vm);
            x = x + font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, /*string[bits]*/ index, en_font[font_size].fontdata);
            bits++;
        }
    }
}

unsigned char check_utf8_size(const unsigned char * string, unsigned char bits)
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

unsigned int unicode_to_utf8(unsigned int letter_uni)
{
    if (letter_uni < 128) 
        return letter_uni;

    unsigned int bytes[4];

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

    unsigned int * res_p = (unsigned int *)bytes;
    return *res_p;
}

unsigned char utf8_1byte_fontdata(unsigned char byte)
{
    return byte;
}

unsigned short utf8_2byte_fontdata(unsigned char byte1, unsigned char byte2)
{
    unsigned short data;

    data = (byte1 << 8) | byte2;
    return data;
}

unsigned int utf8_3byte_fontdata(unsigned char byte1, unsigned char byte2, unsigned char byte3)
{
    unsigned int data;

    data = ((byte1 << 16) & 0xff0000) | ((byte2 << 8) & 0x00ff00) | ((byte3 << 0) & 0x0000ff);
    return data;
}

unsigned int find_utf8_1byte_character(unsigned char character, unsigned char * index_buf)
{
    unsigned int index = 0;

    // printf("byte: %xH", character);
    while (utf8_1byte_fontdata(index_buf[index]) != character) {
        index += 1;
        if (index >= 1024)
            return 0;
    }
    // printf("font index: %d", index);
    return index / 1;
}

unsigned int find_utf8_2byte_character(unsigned short character, unsigned char * index_buf)
{
    unsigned int index = 0;

    // printf("byte: %xH", character);
    while (utf8_2byte_fontdata(index_buf[index], index_buf[index + 1]) != character) {
        index += 2;
        if (index >= 1024)
            return 0;
    }
    // printf("font index: %d", index);
    return index / 2;
}

unsigned int find_utf8_3byte_character(unsigned int character, unsigned char * index_buf)
{
    unsigned int index = 0;

    // printf("byte: %xH", character);
    while (utf8_3byte_fontdata(index_buf[index], index_buf[index + 1], index_buf[index + 2]) != character) {
        index += 3;
        if (index >= 1024)
            return 0;
    }
    // printf("font index: %d", index);
    return index / 3;
}

void display_cn_string(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char * vm)
{
    unsigned int bits = 0;
    unsigned int index = 0;
    unsigned char utf8_size = 0;

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
            index = find_utf8_2byte_character(utf8_2byte_fontdata(string[bits], string[bits + 1]), (unsigned char *)/*fontdata_2byte_index*/cn_index[font_size].index_buf);
            display_character(y, x, cn_font[font_size].width, cn_font[font_size].height, fg, bg, cn_font[font_size].base_char, index, cn_font[font_size].fontdata, vm);
            x = x + cn_font[font_size].width;
            bits += 2;
        } else if (utf8_size == 3) {
            // Three bytes character (example: Simplified chinese)
            index = find_utf8_3byte_character(utf8_3byte_fontdata(string[bits], string[bits + 1], string[bits + 2]), (unsigned char *)/*fontdata_3byte_index*/jp_index[font_size].index_buf);
            display_character(y, x, jp_font[font_size].width, jp_font[font_size].height, fg, bg, jp_font[font_size].base_char, index, jp_font[font_size].fontdata, vm);
            x = x + jp_font[font_size].width;
            bits += 3;
        } else {
            // One byte character (example: English)
            index = find_utf8_1byte_character(utf8_1byte_fontdata(string[bits]), (unsigned char *)/*fontdata_1byte_index*/en_index[font_size].index_buf);
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

void display_cn_val(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char * vm, unsigned char * format, ...)
{
    unsigned char value[128];

    va_list parameter_pointer;

    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_cn_string(y, x, fg, bg, FONT_N1_PT, value, vm);
}

unsigned int string_valid_width(unsigned char font_size, unsigned char * string)
{
    unsigned char bits = 0;
    unsigned int valid_width = 0;
    unsigned char utf8_size = 0;
    unsigned int index = 0;

    while (string[bits] != '\0') {
        utf8_size = check_utf8_size(string, bits);

        if (utf8_size == 2) {
            valid_width = valid_width + cn_font[font_size].width;
            bits += 2;
        } else if (utf8_size == 3) {
            valid_width = valid_width + jp_font[font_size].width;
            bits += 3;
        } else {
            // valid_width = valid_width + font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata);
            index = find_utf8_1byte_character(utf8_1byte_fontdata(string[bits]), (unsigned char *)/*fontdata_1byte_index*/en_index[font_size].index_buf);
            valid_width = valid_width + en_font[font_size].widthdata[/*string[bits]*/index - en_font[font_size].base_char];
            bits++;            
        }
    }
    return valid_width;
}

unsigned int string_valid_height(unsigned char font_size, unsigned char * string)
{
    unsigned char utf8_size = 0;

    // Here use first character's height
    utf8_size = check_utf8_size(string, 0);

    if (utf8_size == 2)
        return cn_font[font_size].height;
    else if (utf8_size == 3)
        return jp_font[font_size].height;
    else
        return en_font[font_size].height;
}

void display_string_auto_place(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, unsigned char color, unsigned char font_size, unsigned char * string, unsigned char select, unsigned char * vm)
{
    unsigned char str_length = 0;
    unsigned char str_height = 0;

    unsigned int widget_y = widget[widget_num].set_y;
    unsigned int widget_x = widget[widget_num].set_x;
    unsigned int widget_w = widget[widget_num].width;
    unsigned int widget_h = widget[widget_num].height;

    unsigned int offset_y, offset_x;
    unsigned int last_y, last_x;

    str_length = string_valid_width(font_size, string);
    str_height = string_valid_height(font_size, string);

    /**
     * +---------------+---------------------------+
     * | align = 0     | yourself set string x,    |
     * | align = 1     | menu string auto center   |
     * | align = 2     | menu string auto left     |
     * | align = 3     | menu string auto right    |
     * +---------------+---------------------------+
     * | place row = 0 | only 1 display at center  |
     * | place row = 1 | only 2 display at line 1  |
     * | place row = 2 | only 2 display at line 2  |
     * | place row = 3 | only 3 display at line 1  |
     * | place row = 4 | only 3 display at line 2  |
     * | place row = 5 | only 3 display at line 3  |
     * | place row = 6 | only 4 display at line 1  |
     * | place row = 7 | only 4 display at line 2  |
     * | place row = 8 | only 4 display at line 3  |
     * | place row = 9 | only 4 display at line 4  |
     * +---------------+---------------------------+
     */
    if (align == MANUAL_ALIGN) {
        last_y = y;
        last_x = x;
    } else {
        switch (align) {
            case CENTER_ALIGN:
                offset_x = abs(widget_w - str_length) / 2;
                break;
            case LEFT_ALIGN:
                // (+3) left side stay 3 piexls
                offset_x = 0 + (3); 
                break;
            case RIGHT_ALIGN:
                // (-2) right side stay 2 piexls
                offset_x = abs(widget_w - str_length) / 2 * 2 - (2);
                break;
        }

        switch (row) {
            case LAYOUT_R11:
                offset_y = (widget_h - str_height) / 2;
                break;
            case LAYOUT_R21:
                // (+1) use to fine tuning the STRING_L2_1 offset_y
                offset_y = ((widget_h / 2 - str_height) / 2) + (1);
                break;
            case LAYOUT_R22:
                // (-1) use to fine tuning the STRING_L2_2 offset_y
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

        last_y = widget_y + offset_y;
        last_x = widget_x + offset_x;
    }

    if (select) {
        // display_solid_rect(last_y, last_x, str_length, str_height, WHITE, vm);
        display_bevel_rect(last_y, last_x, str_length, str_height, WHITE, 1, vm);
        color = BLACK;
    }
    display_cn_string(last_y, last_x, color, 0, font_size, string, vm);
}

void display_widget_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N1_PT, 
            string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N1_PT, 
            (unsigned char *)menu_content[string_num], select, vm);
    }
}

void display_mark_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N2_PT, 
            string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N2_PT, 
            (unsigned char *)menu_content[string_num], select, vm);
    }
}

void display_measure_value_unit_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N3_PT, 
            string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N3_PT, 
            (unsigned char *)menu_content[string_num], select, vm);
    }
}

void display_measure_value_content(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N4_PT, 
            (unsigned char *)string, select, vm);
    } else {
        display_string_auto_place(y, x, align, row, widget_num, color, FONT_N4_PT, 
            (unsigned char *)menu_content[string_num], select, vm);
    }
}

void display_character_selected_digit(int y, int x, int width, int height, unsigned int fg, unsigned int bg, unsigned char start_char, unsigned char character, const unsigned char * fontlib, unsigned char * vm)
{
    unsigned int total_byte = 0;
    unsigned long faddress = 0;
    unsigned int column = 0;

    unsigned int tx, ty;

    ty = y;
    tx = x;

    // How many bytes are needed for a character
    total_byte = (int)((width + 7) / 8) * height;
    character = character - start_char;
    faddress = character * total_byte;

    for (int i = 0; i < total_byte; i++) {
        for (int j = 0; j < 8; j++) {
            if (fontlib[faddress] & (0x80 >> j)) {
                display_pixel(ty, tx, fg, vm);
            } else {
                if (bg != 0) {
                    // display_pixel(ty, tx, bg, vm);
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

void display_cn_string_selected_digit(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, unsigned char font_size, unsigned char * string, unsigned char selected_digit, unsigned char * vm)
{
    unsigned int bits = 0;
    unsigned int index = 0;
    unsigned int color;

    unsigned char character_width;
    unsigned char character_height;

    while (string[bits] != '\0') {
        if (check_gbk_size(string[bits]) == 2) {
            // Simplified chinese
            index = find_gbk_2byte_character(gbk_2byte_fontdata(string[bits], string[bits + 1]), (unsigned char *)/*fontdata_2byte_index*/cn_index[font_size].index_buf);
            display_character_selected_digit(y + 1, x, cn_font[font_size].width, cn_font[font_size].height, fg, bg, cn_font[font_size].base_char, index, cn_font[font_size].fontdata, vm);
            x = x + cn_font[font_size].width;
            bits += 2;
        } else {
            // English
            // character_width = font_valid_width(en_font[font_size].width, en_font[font_size].height, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata);
            character_width = en_font[font_size].widthdata[string[bits] - en_font[font_size].base_char];
            character_height = string_valid_height(font_size, string);

            if ((string[bits] == '.') || (string[bits] == ',') || (string[bits] == ' ') || (string[bits] == ':') || (string[bits] == '-'))
                selected_digit++;

            if ((bits == selected_digit) && (string[bits] >= '0') && (string[bits] <= '9')) {
                // display_solid_rect(y, x, character_width, character_height, fg, vm);
                display_bevel_rect(y, x, character_width, character_height, fg, 1, vm);
                display_character_selected_digit(y, x, en_font[font_size].width, en_font[font_size].height, bg, bg, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata, vm);
            } else
                display_character_selected_digit(y, x, en_font[font_size].width, en_font[font_size].height, fg, bg, en_font[font_size].base_char, string[bits], en_font[font_size].fontdata, vm);

            x = x + character_width;
            bits++;
        }
    }
}

void display_string_auto_place_selected_digit(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, unsigned char color, unsigned char font_size, unsigned char * string, unsigned char select, unsigned char selected_digit, unsigned char * vm)
{
    unsigned char str_length = 0;
    unsigned char str_height = 0;

    unsigned int widget_y = widget[widget_num].set_y;
    unsigned int widget_x = widget[widget_num].set_x;
    unsigned int widget_w = widget[widget_num].width;
    unsigned int widget_h = widget[widget_num].height;

    unsigned int offset_y, offset_x;
    unsigned int last_y, last_x;

    str_length = string_valid_width(font_size, string);
    str_height = string_valid_height(font_size, string);

    /**
     * +---------------+---------------------------+
     * | align = 0     | yourself set string x,    |
     * | align = 1     | menu string auto center   |
     * | align = 2     | menu string auto left     |
     * | align = 3     | menu string auto right    |
     * +---------------+---------------------------+
     * | place row = 0 | only 1 display at center  |
     * | place row = 1 | only 2 display at line 1  |
     * | place row = 2 | only 2 display at line 2  |
     * | place row = 3 | only 3 display at line 1  |
     * | place row = 4 | only 3 display at line 2  |
     * | place row = 5 | only 3 display at line 3  |
     * | place row = 6 | only 4 display at line 1  |
     * | place row = 7 | only 4 display at line 2  |
     * | place row = 8 | only 4 display at line 3  |
     * | place row = 9 | only 4 display at line 4  |
     * +---------------+---------------------------+
     */
    if (align == MANUAL_ALIGN) {
        last_y = y;
        last_x = x;
    } else {
        switch (align) {
            case CENTER_ALIGN:
                offset_x = abs(widget_w - str_length) / 2;
                break;
            case LEFT_ALIGN:
                // (+3) left side stay 3 piexls
                offset_x = 0 + (3); 
                break;
            case RIGHT_ALIGN:
                // (-2) right side stay 2 piexls
                offset_x = abs(widget_w - str_length) / 2 * 2 - (2);
                break;
        }

        switch (row) {
            case LAYOUT_R11:
                offset_y = (widget_h - str_height) / 2;
                break;
            case LAYOUT_R21:
                // (+1) use to fine tuning the STRING_L2_1 offset_y
                offset_y = ((widget_h / 2 - str_height) / 2) + (1);
                break;
            case LAYOUT_R22:
                // (-1) use to fine tuning the STRING_L2_2 offset_y
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

        last_y = widget_y + offset_y;
        last_x = widget_x + offset_x;
    }

    if (select) {
        display_solid_rect(last_y, last_x, str_length, str_height, WHITE, vm);
        color = BLACK;
    }
    display_cn_string_selected_digit(last_y, last_x, color, 0, font_size, string, selected_digit, vm);
}

void display_main_measure_data_unit_content_selected_digit(unsigned int y, unsigned int x, unsigned char align, unsigned char row, unsigned int widget_num, const unsigned char * string, unsigned int string_num, unsigned char color, unsigned char select, unsigned char selected_digit, unsigned char * vm)
{
    if (string_num == TEMP_CONTENT) {
        display_string_auto_place_selected_digit(y, x, align, row, widget_num, color, FONT_N2_PT, 
            string, select, selected_digit, vm);
    } else {
        display_string_auto_place_selected_digit(y, x, align, row, widget_num, color, FONT_N2_PT, 
            (unsigned char *)menu_content[string_num], select, selected_digit, vm);
    }
}
