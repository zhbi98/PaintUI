/**
 * @file setting.h
 *
 */

#ifndef __SETTING_H__
#define __SETTING_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void setup_level1_menu(uint8_t key_event, uint8_t * vm);
void setup_level1_key_event(uint8_t key_event);
void setup_level1_key_event_enable(uint8_t key_event);

#endif
