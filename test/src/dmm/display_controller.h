
#ifndef __DISPLAY_CONTROLLER_H__
#define __DISPLAY_CONTROLLER_H__

#include <stdbool.h>

#include "ili9341a.h"

#include "voltage_v.h"
#include "display_show.h"

#define FUNCTION_TYPE_MAX 16U
#define MENUBAR_LEVEL_MAX  2U
#define WIDGET_NUM_MAX    40U

// This is tft region and write data driver interface
#define TFT_REGION_SETTING_DRV ili9341_display_region
#define TFT_WRITE_DATA_DRV     ili9341_write_data

struct module_t {
    unsigned int set_x;
    unsigned int set_y;
    unsigned int width;
    unsigned int height;

    unsigned char show;
    unsigned char renew;
    unsigned char auto_renew;
    unsigned char pressed;
};

struct menubar_t {
    // What function is displayed
    // in the current menu
    unsigned char menu_function;
    // Which level of the menu of each function
    // is currently located
    unsigned char menu_level[FUNCTION_TYPE_MAX];
    // Which menu level of which function was pressed
    unsigned char menu_selected[FUNCTION_TYPE_MAX][MENUBAR_LEVEL_MAX];
    // Which page of that function is currently on
    unsigned char menu_page[FUNCTION_TYPE_MAX];
    unsigned char pressed;
};

enum widget_number {
    DISPLAY_TFT_AREA1,
    DISPLAY_TFT_AREA2,
    DISPLAY_TFT_AREA3,
    DISPLAY_TFT_AREA4,
    DISPLAY_TFT_AREA5,
    DISPLAY_SETTING_AREA2,

    // DISPLAY_TFT_AREA1
    DISPLAY_BATTERY_AREA,
    DISPLAY_BLUETOOTH_AREA,
    DISPLAY_POWER_OFF_TIMER_AREA,
    DISPLAY_TRUMPET_AREA,
    DISPLAY_LIGHTING_AREA,
    DISPLAY_REAL_TIME_AREA,

    // DISPLAY_TFT_AREA2
    MEASURE_VALUE_MODE_AREA,
    DISPLAY_RECORDING_AREA,
    DISPLAY_HOLD_AREA,
    MEASURE_RELATIVE_VALUE_AREA,

    // DISPLAY_TFT_AREA3
    MEASURE_VALUE_AREA,
    MEASURE_VALUE_UNIT_AREA,

    // DISPLAY_TFT_AREA4
    MEASURE_LO_AREA,
    MEASURE_LOZ_AREA,
    MEASURE_RULER_AREA,
    MEASURE_RANGE_STATUS_AREA,

    // DISPLAY_TFT_AREA5
    F1_MENUBAR_AREA,
    F2_MENUBAR_AREA,
    F3_MENUBAR_AREA,
    F4_MENUBAR_AREA,

    PREV_MENUBAR_AREA,
    NEXT_MENUBAR_AREA,

    // DISPLAY_SETTING_AREA2
    SETTING_LIST_AREA,
};

typedef void key_event_interface(unsigned char key);
typedef void menu_content_interface(unsigned char key_event, unsigned char * vm);
typedef void display_show_interface(unsigned char * vm);

typedef void (* tft_region_setting)(unsigned int y, unsigned int x, unsigned int width, unsigned int height);
typedef void (* tft_write_data)(unsigned int data);

extern const key_event_interface * key_event_controller[][MENUBAR_LEVEL_MAX];
extern const key_event_interface * key_event_enable[][MENUBAR_LEVEL_MAX];
extern const menu_content_interface * display_menu_content[][MENUBAR_LEVEL_MAX];
extern const display_show_interface * display_widget_show[];

extern struct module_t widget[];
extern struct menubar_t menubar;

extern void widget_size_init();

extern void set_menubar_function(unsigned char function);
extern unsigned char read_menubar_function();

extern void set_menubar_level(unsigned char level);
extern unsigned char read_menu_level();

extern void set_menubar_page(unsigned char page);
extern unsigned char read_menubar_page();

extern void set_menubar_pressed(unsigned char menu_num);
extern unsigned char read_pressed_menubar();

extern void function_key_event(unsigned char key_event);
extern void function_key_event_enable(unsigned char key);

extern void display_menubar_content(unsigned char key_event, unsigned char * vm);
extern void menubar_pressed(unsigned char key_event);

extern void display_area1_flush(unsigned char * vm);
extern void display_area1_flush_enable();
extern void display_battery_flush(unsigned char * vm);
extern void battery_flush_enable();
extern void display_bluetooth_flush(unsigned char * vm);
extern void display_power_off_timer_flush(unsigned char * vm);
extern void display_trumpet_flush(unsigned char * vm);
extern void display_lighting_flush(unsigned char * vm);
extern void display_real_time_flush(unsigned char * vm);

extern void display_area2_flush(unsigned char * vm);
extern void display_area2_flush_enable();
extern void display_measure_value_mode_flush(unsigned char * vm);
extern void display_recording_flush(unsigned char * vm);
extern void display_hold_flush(unsigned char * vm);
extern void display_relative_value_flush(unsigned char * vm);

extern void display_area3_flush(unsigned char * vm);
extern void display_area3_flush_enable();
extern void display_measure_value_flush(unsigned char * vm);
extern void display_measure_value_unit_flush(unsigned char * vm);
extern void measure_value_flush_enable();

extern void display_area4_flush(unsigned char * vm);
extern void display_area4_flush_enable();
extern void display_measure_lo_flush(unsigned char * vm);
extern void display_measure_loz_flush(unsigned char * vm);
extern void display_measure_ruler_flush(unsigned char * vm);
extern void display_measure_range_status_flush(unsigned char * vm);

extern void display_area5_flush(unsigned char * vm);
extern void display_area5_flush_enable();
extern void display_f1_menubar_flush(unsigned char * vm);
extern void display_f2_menubar_flush(unsigned char * vm);
extern void display_f3_menubar_flush(unsigned char * vm);
extern void display_f4_menubar_flush(unsigned char * vm);
extern void display_prev_menubar_flush(unsigned char * vm);
extern void display_next_menubar_flush(unsigned char * vm);
extern void menubar_flush_enable();
static void measure_interface(unsigned char * vm);

extern void display_setting_area2_flush(unsigned char * vm);
extern void display_setting_area2_flush_enable();
extern void display_setting_list_flush(unsigned char * vm);
static void setting_interface(unsigned char * vm);

extern void display_flush(unsigned char * vm);

// This related to tft driver
extern void tft_clear(unsigned char color);
extern void tft_flush_area(unsigned char area_num, unsigned char * vm);
extern void tft_flush(unsigned char * vm);

#endif
