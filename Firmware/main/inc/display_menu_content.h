
#ifndef __DISPLAY_MENU_CONTENT_H__
#define __DISPLAY_MENU_CONTENT_H__

#include <stdint.h>

enum {
	MENU_RANGE       = 0,
    MENU_MAX_MIN     = 1,
    MENU_REL         = 2,
    MENU_HOLD        = 3,
    MENU_LEFT        = 4,
    MENU_RIGHT       = 5,
    MENU_UP          = 6,
    MENU_DOWN        = 7,
    MENU_ADD         = 8,
    MENU_MINUS       = 9,
    MENU_COMP        = 10,
    MENU_AC_DC       = 11,
    MENU_LO          = 12,
    MENU_LOZ         = 13,
    MENU_PEAK        = 14,
    MENU_DISPLAY     = 15,
    MENU_AUTO_SAVE   = 16,
    MENU_MANUAL_SAVE = 17,
    MENU_VIEW_DATA   = 18,

    TEMP_CONTENT     = 512,
};

enum {
    LIST_1_2             = 0,
    LIST_SET_TIME        = 1,
    LIST_SET_DATE        = 2,
    LIST_AUTO_SHTDWN     = 3,
    LIST_COMPARE_MAX     = 4,
    LIST_COMPARE_MIN     = 5,
    LIST_COMPARE_TYPE    = 6,
    LIST_RECORD_RATE     = 7,
    LIST_MEMORY_MODE     = 8,
    LIST_2_2             = 9,
    LIST_BACK_LIGHT      = 10,
    LIST_BACK_LIGHT_TIME = 11,
    LIST_SOUND           = 12,
    LIST_COLOR           = 13,
};

enum {
    TIPS_BATTERY_LOW_20 = 0,
    TIPS_BATTERY_LOW_10 = 1,
    TIPS_BATTERY_LOW_05 = 2,
};

extern const uint8_t * const menu_content[];
extern const uint8_t * const list_content[];
extern const uint8_t * const tips_content[];

#endif
