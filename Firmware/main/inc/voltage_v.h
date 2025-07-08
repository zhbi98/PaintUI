
#ifndef __VOLTAGE_V_H__
#define __VOLTAGE_V_H__

#include <stdbool.h>
#include "key_doing.h"

typedef struct {
    uint8_t state;
} _volt_t;

enum {
    VOLT_DC = 0,
    VOLT_AC,
};

enum {
    VOLT_CENTER = 0,
    VOLT_LEFT,
    VOLT_RIGHT,
};

void volt_level1_menu(uint8_t key_event, uint8_t * vm);
void volt_level1_key_event(uint8_t key_event);
void volt_level1_key_event_enable(uint8_t key_event);
void volt_select();

#endif
