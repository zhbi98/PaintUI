
#ifndef __SETTING_H__
#define __SETTING_H__

#include <stdbool.h>

#include "log.h"
#include "key.h"
#include "display_controller.h"
#include "display_menu_content.h"
#include "display_show.h"
#include "setup.h"

extern void setting_level1_menu(unsigned char key_event, unsigned char * vm);
extern void setting_level1_key_event(unsigned char key_event);
extern void setting_level1_key_event_enable(unsigned char key_event);

#endif
