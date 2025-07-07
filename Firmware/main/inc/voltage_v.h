
#ifndef __VOLTAGE_V_H__
#define __VOLTAGE_V_H__

#include <stdbool.h>
#include "key_doing.h"
#include "display_controller.h"
#include "menu_str.h"
#include "log.h"

struct voltage_measure_t {
    unsigned char type;
};

enum voltage_type {
    VOLTAGE_DC = 0,
    VOLTAGE_AC = 1,
};

enum voltage_page {
    VOLTAGE_CENTER = 0,
    VOLTAGE_LEFT   = 1,
    VOLTAGE_RIGHT  = 2,
};

extern struct voltage_measure_t voltage_measure;

extern void voltage_level1_menu(unsigned char key_event, unsigned char * vm);
extern void voltage_level1_key_event(unsigned char key_event);
extern void voltage_level1_key_event_enable(unsigned char key_event);
extern void voltage_select();

#endif
