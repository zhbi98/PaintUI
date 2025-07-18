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

/*********************
 *      DEFINES
 *********************/

/**
 * Characters susceptible to file 
 * encoding are uniformly 
 * defined in this file.
 */

#if !defined __DDEG__
#define __DDEG__ "°"
#endif

#if !defined __OUMU__
#define __OUMU__ "Ω"
#endif

#if !defined __DEG__
#define __DEG__ "℃"
#endif

/**********************
 *      TYPEDEFS
 **********************/

enum {
  MENU_RANGE = 0,
  MENU_MAX,
  MENU_REL,
  MENU_HOLD,
  MENU_COMP,
  MENU_ACDC,
  MENU_LO,
  MENU_LOZ,
  MENU_PEAK,
  MENU_DISP,
  MENU_REC,
  MENU_SAVE,
  MENU_LOG,
  MENU_LEFT,
  MENU_RIGHT,
  MENU_UP,
  MENU_DOWN,
  MENU_ADD,
  MENU_DEC,
  _MENU_LAST,
};

enum {
  LIST_1_2 = 0,
  LIST_SET_TIME,
  LIST_SET_DATE,
  LIST_APOFF,
  LIST_COMP_MAX,
  LIST_COMP_MIN,
  LIST_COMP_TYPE,
  LIST_REC_RATE,
  LIST_MEM_MODE,
  LIST_2_2,
  LIST_BRIGHT,
  LIST_DISP_ON,
  LIST_VOICE,
  LIST_DISP_MOD,
  _LIST_LAST,
};

enum {
  TIPS_BAT_LOW20 = 0,
  TIPS_BAT_LOW10,
  TIPS_BAT_LOW05,
  _TIPS_LAST,
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern const uint8_t * const menu_content[];
extern const uint8_t * const list_content[];
extern const uint8_t * const tips_content[];

#endif /*__DISPLAY_MENU_CONTENT_H__*/
