
#ifndef __SETTING_H__
#define __SETTING_H__

#include <stdbool.h>

#include "log.h"
#include "key.h"
#include "display_controller.h"
#include "menu_str.h"
#include "display_show.h"
#include "setup.h"

extern void setting_level1_menu(uint8_t key_event, uint8_t * vm);
extern void setting_level1_key_event(uint8_t key_event);
extern void setting_level1_key_event_enable(uint8_t key_event);

#endif
