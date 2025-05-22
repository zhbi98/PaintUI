
#ifndef __FONTLIB_H__
#define __FONTLIB_H__

#include <stdio.h>
#include <stdint.h>

typedef struct {
    const uint8_t * fontdata;
    const uint8_t * widthdata;
    const uint8_t width;
    const uint8_t height;
    const uint8_t base_char;
} font_data_t;

typedef struct {
    const uint8_t * index_buf;
    const uint32_t buf_size;
} font_index_t;

// Font size unit point
enum {
    FONT_N1_PT = 0,
    FONT_N2_PT,
    FONT_N3_PT,
    FONT_N4_PT,
    FONT_MAX_PT,
};

typedef uint8_t font_size_t;

enum {
    LANGUAGE_EN = 0,
    LANGUAGE_CH,
    LANGUAGE_JP,
};

typedef uint8_t language_t;

enum {
    EN_CHAR_BYTE = 1,
    CN_CHAR_BYTE,
    JP_CHAR_BYTE,
};

typedef uint8_t utf_byte_t;

extern const uint8_t  fontdata_en_N1[];
extern const uint8_t  fontdata_en_N2[];
extern const uint8_t  fontdata_en_N3[];
extern const uint8_t  fontdata_en_N4[];

extern const uint8_t widthdata_en_N1[];
extern const uint8_t widthdata_en_N2[];
extern const uint8_t widthdata_en_N3[];
extern const uint8_t widthdata_en_N4[];

extern const uint8_t fontdata_cn_N3[];

extern const uint8_t fontdata_jp_N1[];
extern const uint8_t fontdata_jp_N3[];

extern const font_data_t en_font[];
extern const font_data_t cn_font[];
extern const font_data_t jp_font[];

extern const uint8_t fontdata_en_N1_index[];
extern const uint8_t fontdata_en_N2_index[];
extern const uint8_t fontdata_en_N3_index[];
extern const uint8_t fontdata_en_N4_index[];

extern const uint8_t fontdata_cn_N3_index[];

extern const uint8_t fontdata_jp_N1_index[];
extern const uint8_t fontdata_jp_N3_index[];

extern const font_index_t en_index[];
extern const font_index_t cn_index[];
extern const font_index_t jp_index[];

font_data_t read_font_data(uint8_t font_type, uint8_t font_size);
font_index_t read_font_index(uint8_t font_type, uint8_t font_size);

#endif
