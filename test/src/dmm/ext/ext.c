
#include "display_string.h"
#include "ext.h"

void textarea_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, 
    uint8_t font_size, uint8_t * string, uint8_t * vm)
{
    const uint8_t * cn_index_p = (uint8_t *)cn_index[font_size].index_buf;
    const uint8_t * jp_index_p = (uint8_t *)jp_index[font_size].index_buf;
    const uint8_t * en_index_p = (uint8_t *)en_index[font_size].index_buf;

    const uint8_t * cn_font_p = cn_font[font_size].fontdata;
    const uint8_t * jp_font_p = jp_font[font_size].fontdata;
    const uint8_t * en_font_p = en_font[font_size].fontdata;

    uint32_t cn_base_ofs = cn_font[font_size].base_char;
    uint32_t jp_base_ofs = jp_font[font_size].base_char;
    uint32_t en_base_ofs = en_font[font_size].base_char;

    uint32_t bits = 0;
    uint32_t index = 0;
    uint8_t utf8_size = 0;

    uint16_t string_high = 0;
    uint8_t fetch_string[8] = {0};
    uint8_t fetch_len = 0;
    uint8_t fetch = 0;

    uint8_t inv_val = 0;

    uint16_t string_xstart = x;
    uint8_t fg_origin = fg;

    while (string[bits] != '\0') {
        utf8_size = check_utf8_size(string, bits);

        if (utf8_size == 2) {
            /*Simplified chinese*/
            index = find_utf8_2byte_character(
                utf8_2byte_fontdata(string[bits], 
                    string[bits + 1]), cn_index_p);

            display_character(y, x, 
                cn_font[font_size].width, 
                cn_font[font_size].height, 
                fg, bg, 
                cn_base_ofs, index, 
                cn_font_p, 
                vm);

            x = x + cn_font[font_size].width;
            bits += 2;
        } else if (utf8_size == 3) {
            /*Simplified chinese*/
            index = find_utf8_3byte_character(
                utf8_3byte_fontdata(string[bits], 
                    string[bits + 1], 
                    string[bits + 2]), 
                    jp_index_p);

            display_character(y, x, 
                jp_font[font_size].width, 
                jp_font[font_size].height, 
                fg, bg, 
                jp_base_ofs, index, 
                jp_font_p, vm);

            x = x + jp_font[font_size].width;
            bits += 3;
        } else {
            /*English*/
            uint8_t val = string[bits];

            if (val == '\n') {
                string_high = string_valid_height(
                    font_size, string);
                y += string_high;
                x = string_xstart;
                bits++;
                continue;
            } else if (val == '\r') {
                x = string_xstart;
                bits++;
                continue;
            } else if (val == '#') {
                if (fetch == 0) {
                    memset(fetch_string, '\0', 8);
                    inv_val = 0;
                    fetch_len = 0;
                    fetch = 1;
                    bits++;
                    continue;
                } else if (fetch == 2) {
                    fg = fg_origin;
                    fetch = 0;
                    bits++;
                    continue;
                } else if (inv_val) {
                    fg = fg_origin;
                    inv_val = 0;
                    fetch = 0;
                    bits++;
                    continue;
                }
            }

            if ((fetch == 1) && (!inv_val)) {
                if (val != ' ') {
                    fetch_string[fetch_len] = string[bits];
                    fetch_len++;

                    if (fetch_len > 6) {
                        inv_val = 1;
                    }

                    bits++;
                    continue;
                } else if (val == ' ') {
                    for (uint8_t i = 0; i < 6; i++) {
                        if (fetch_string[i] < '0' || 
                            fetch_string[i] > '9') {
                            inv_val = 1;
                            continue;
                        }
                    }

                    fg = atoi(fetch_string);

                    if (fg > 0xFF) {
                        inv_val = 1;
                        continue;
                    }

                    fetch = 2;
                    bits++;
                    continue;
                }
            }

            index = find_utf8_1byte_character(
                string[bits], en_index_p);

            display_character(y, x, 
                en_font[font_size].width, 
                en_font[font_size].height, 
                fg, bg, 
                en_base_ofs, index, 
                en_font_p, vm);

            x = x + en_font[font_size]\
                .widthdata[index - en_base_ofs];
            bits++;
        }
    }
}
