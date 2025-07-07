/**
 * @file key_doing.h
 *
 */

#ifndef __KEY_DOING_H__
#define __KEY_DOING_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/**********************
 *      TYPEDEFS
 **********************/

enum {
  DMM_VOLTAGE_V,
  _DMM_LAST,
};

typedef uint8_t dmm_actbar_func_t;

enum {
  CTL_DEF =  0,
  _CTL_LAST,
};

typedef uint8_t ctl_actbar_func_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void key_event_doing();

#endif /*__KEY_CONTEOLLER_H__*/
