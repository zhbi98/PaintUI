/**
 * @file alerts.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "menu_str.h"
#include "alerts.h"
#include "stdbool.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

dev_alerts_t alerts[5] = {
  {
    .msg_width = 50,
    .msg_high = 30,
    .active = true,
    ._time = 300,
    .stridx = TIPS_BATTERY_LOW_20,
  },

  {
    .msg_width = 50,
    .msg_high = 30,
    .active = true,
    ._time = 0,
    .stridx = TIPS_BATTERY_LOW_10,
  },

  {
    .msg_width = 50,
    .msg_high = 30,
    .active = true,
    ._time = 0,
    .stridx = TIPS_BATTERY_LOW_05,
  },

  {
    .msg_width = 50,
    .msg_high = 30,
    .active = true,
    ._time = 0,
    .stridx = 3,
  },
};
