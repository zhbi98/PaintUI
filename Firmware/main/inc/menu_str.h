/**
 * @file menu_str.h
 *
 */

#ifndef __MENU_STR_H__
#define __MENU_STR_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/**********************
 *      TYPEDEFS
 **********************/

enum {
	MENU_RANGE = 0,
    MENU_MAX_MIN,
    MENU_REL,
    MENU_HOLD,
    MENU_LEFT,
    MENU_RIGHT,
    MENU_UP,
    MENU_DOWN,
    MENU_ADD,
    MENU_MINUS,
    MENU_COMP,
    MENU_AC_DC,
    MENU_LO,
    MENU_LOZ,
    MENU_PEAK,
    MENU_DISPLAY,
    MENU_AUTO_SAVE,
    MENU_MANUAL_SAVE,
    MENU_VIEW_DATA,
    _MENU_LAST,
};

enum {
    LIST_1_2 = 0,
    LIST_SET_TIME,
    LIST_SET_DATE,
    LIST_AUTO_SHTDWN,
    LIST_COMPARE_MAX,
    LIST_COMPARE_MIN,
    LIST_COMPARE_TYPE,
    LIST_RECORD_RATE,
    LIST_MEMORY_MODE,
    LIST_2_2,
    LIST_BRIGHT,
    LIST_DISP_ON,
    LIST_SOUND,
    LIST_COLOR,
    _LIST_LAST,
};

enum {
    TIPS_BATTERY_LOW_20 = 0,
    TIPS_BATTERY_LOW_10,
    TIPS_BATTERY_LOW_05,
    _TIPS_LAST,
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern const uint8_t * const menu_content[];
extern const uint8_t * const list_content[];
extern const uint8_t * const tips_content[];

#endif /*__DISPLAY_MENU_CONTENT_H__*/
