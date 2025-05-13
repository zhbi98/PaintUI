
#ifndef __DISPLAY_SHOW_H__
#define __DISPLAY_SHOW_H__

#include <math.h>
#include <stdbool.h>

#include "logo_manager.h"
#include "display.h"
#include "display_string.h"
#include "display_controller.h"

#include "log.h"
#include "regulator.h"
#include "setup.h"
#include "setting.h"

extern struct status_logo_pool_t logo_pool;

extern void get_status_logo_active();

extern void display_area1_show(unsigned char * vm);
extern void display_battery_show(unsigned char * vm);
extern void display_buletooth_show(unsigned char * vm);
extern void display_power_off_timer_show(unsigned char * vm);
extern void display_trumpet_show(unsigned char * vm);
extern void display_lighting_show(unsigned char * vm);
extern void display_real_time_show(unsigned char * vm);

extern void display_area2_show(unsigned char * vm);
extern void display_measure_mode_show(unsigned char * vm);
extern void display_recording_show(unsigned char * vm);
extern void display_hold_show(unsigned char * vm);
extern void display_relative_value_show(unsigned char * vm);

extern void display_area3_show(unsigned char * vm);
extern void display_measure_value_show(unsigned char * vm);
extern void display_measure_value_unit_show(unsigned char * vm);

extern void display_area4_show(unsigned char * vm);
extern void display_measure_lo_show(unsigned char * vm);
extern void display_measure_loz_show(unsigned char * vm);
extern void display_measure_ruler_show(unsigned char * vm);
extern void display_range_status_show(unsigned char * vm);

extern void display_area5_show(unsigned char * vm);
extern void display_f1_menubar_area_show(unsigned char * vm);
extern void display_f2_menubar_area_show(unsigned char * vm);
extern void display_f3_menubar_area_show(unsigned char * vm);
extern void display_f4_menubar_area_show(unsigned char * vm);
extern void display_prev_menubar_area_show(unsigned char * vm);
extern void display_next_menubar_area_show(unsigned char * vm);

extern void display_setting_area2_show(unsigned char * vm);
extern void display_setting_list_show(unsigned char * vm);

#endif
