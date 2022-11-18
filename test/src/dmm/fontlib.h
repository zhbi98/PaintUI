
#ifndef __FONTLIB_H__
#define __FONTLIB_H__

#include <stdio.h>

struct font_data_t {
    const unsigned char     width;
    const unsigned char    height;
    const unsigned char base_char;

    const unsigned char *  fontdata;
    const unsigned char * widthdata;
};

struct font_index_t {
    const unsigned char * index_buf;
    const unsigned int buf_size;
};

// Font size unit point
enum font_size_type {
    FONT_N1_PT  = 0,
    FONT_N2_PT  = 1,
    FONT_N3_PT  = 2,
    FONT_N4_PT  = 3,
    FONT_MAX_PT = 4,
};

enum language_type {
    LANGUAGE_EN = 0,
    LANGUAGE_CH = 1,
    LANGUAGE_JP = 2,
};

enum utf_byte_length {
    EN_CHAR_BYTE = 1,
    CN_CHAR_BYTE = 2,
    JP_CHAR_BYTE = 3,
};

extern const unsigned char  fontdata_en_N1[];
extern const unsigned char  fontdata_en_N2[];
extern const unsigned char  fontdata_en_N3[];
extern const unsigned char  fontdata_en_N4[];

extern const unsigned char widthdata_en_N1[];
extern const unsigned char widthdata_en_N2[];
extern const unsigned char widthdata_en_N3[];
extern const unsigned char widthdata_en_N4[];

extern const unsigned char fontdata_cn_N3[];

extern const unsigned char fontdata_jp_N1[];
extern const unsigned char fontdata_jp_N3[];

extern const struct font_data_t en_font[];
extern const struct font_data_t cn_font[];
extern const struct font_data_t jp_font[];

extern struct font_data_t read_font_data(unsigned char font_type, unsigned char font_size);

extern const unsigned char fontdata_en_N1_index[];
extern const unsigned char fontdata_en_N2_index[];
extern const unsigned char fontdata_en_N3_index[];
extern const unsigned char fontdata_en_N4_index[];

extern const unsigned char fontdata_cn_N3_index[];

extern const unsigned char fontdata_jp_N1_index[];
extern const unsigned char fontdata_jp_N3_index[];

extern const struct font_index_t en_index[];
extern const struct font_index_t cn_index[];
extern const struct font_index_t jp_index[];

extern struct font_index_t read_font_index(unsigned char font_type, unsigned char font_size);

#endif
