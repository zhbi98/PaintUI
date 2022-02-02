
#ifndef __FONTLIB_H__
#define __FONTLIB_H__

#include <stdio.h>

struct font_data_t {
    const unsigned char width;
    const unsigned char height;
    const unsigned char base_char;

    const unsigned char * fontdata;
    const unsigned char * widthdata;
};

struct font_index_t {
    const unsigned char * index_buf;
    const unsigned int buf_size;
};

enum font_size_type {
    FONT_12X16,
    FONT_32X51,
    FONT_20X20,
    FONT_14X14,
    FONT_SIZE_ALL
};

enum language_type {
    LANGUAGE_ENGLISH = 0,
    LANGUAGE_CHINESE = 1,
    LANGUAGE_JAPAN   = 2,
};

extern const unsigned char fontdata_cn12x12_3byte[];
extern const unsigned char fontdata_cn20x20_2byte[];
extern const unsigned char fontdata_cn20x20_3byte[];

extern const unsigned char fontdata_en12x16[];
extern const unsigned char fontdata_en32x51[];
extern const unsigned char fontdata_en20x20[];
extern const unsigned char fontdata_en14x14[];

extern const unsigned char widthdata_en12x16[];
extern const unsigned char widthdata_en32x51[];
extern const unsigned char widthdata_en20x20[];
extern const unsigned char widthdata_en14x14[];

extern const struct font_data_t en_font[];
extern const struct font_data_t cn_font[];
extern const struct font_data_t jp_font[];

extern struct font_data_t read_font_data(unsigned char font_type, unsigned char font_size);

extern const unsigned char fontdata_cn12x12_3byte_index[];
extern const unsigned char fontdata_cn20x20_2byte_index[];
extern const unsigned char fontdata_cn20x20_3byte_index[];

extern const struct font_index_t en_index[];
extern const struct font_index_t cn_index[];
extern const struct font_index_t jp_index[];

extern struct font_index_t read_font_index(unsigned char font_type, unsigned char font_size);

#endif
