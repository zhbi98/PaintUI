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
    .active = true,
    ._tick = 300,
    .stridx = TIPS_BATTERY_LOW_20,
  },

  {
    .active = true,
    ._tick = 0,
    .stridx = TIPS_BATTERY_LOW_10,
  },

  {
    .active = true,
    ._tick = 0,
    .stridx = TIPS_BATTERY_LOW_05,
  },

  {
    .active = true,
    ._tick = 0,
    .stridx = 3,
  },
};
