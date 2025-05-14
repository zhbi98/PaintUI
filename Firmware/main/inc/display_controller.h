
#ifndef __DISPLAY_CONTROLLER_H__
#define __DISPLAY_CONTROLLER_H__

#include <stdbool.h>
#include <stdint.h>

#include "ili9341a.h"

#include "voltage_v.h"
#include "display_show.h"

#define FUNC_TYPE_MAX 16U
#define DEPTH_MAX  2U
#define WIDGET_NUM_MAX    40U

// This is tft region and write data driver interface
#define TFT_REGION_SETTING_DRV ili9341_display_region
#define TFT_WRITE_DATA_DRV     ili9341_write_data

/**
 * Device display Area
 */
typedef struct {
    uint16_t set_x;
    uint16_t set_y;
    uint16_t width;
    uint16_t height;
    bool valid;
    bool refer;
    bool pressed;
} dev_area_t;

/**
 * Device display Area
 */
typedef struct {
    uint8_t _func;
    uint8_t func;
    uint8_t _depth[FUNC_TYPE_MAX];
    uint8_t pressed[FUNC_TYPE_MAX][DEPTH_MAX];
    uint8_t page[FUNC_TYPE_MAX];
} dev_actbar_t;

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

typedef void key_event_interface(uint8_t key);
typedef void menu_content_interface(uint8_t key_event, uint8_t * vm);
typedef void display_show_interface(uint8_t * vm);

typedef void (* tft_region_setting)(uint32_t y, uint32_t x, uint32_t width, uint32_t height);
typedef void (* tft_write_data)(uint32_t data);

extern const key_event_interface * key_event_controller[][DEPTH_MAX];
extern const key_event_interface * key_event_enable[][DEPTH_MAX];
extern const menu_content_interface * display_menu_content[][DEPTH_MAX];
extern const display_show_interface * display_widget_show[];

extern dev_area_t _Area[];
extern dev_actbar_t menubar;

extern void widget_size_init();

extern void set_menubar_function(uint8_t function);
extern uint8_t read_menubar_function();

extern void set_menubar_level(uint8_t level);
extern uint8_t read_menu_level();

extern void set_menubar_page(uint8_t page);
extern uint8_t read_menubar_page();

extern void set_menubar_pressed(uint8_t menu_num);
extern uint8_t read_pressed_menubar();

extern void function_key_event(uint8_t key_event);
extern void function_key_event_enable(uint8_t key);

extern void display_menubar_content(uint8_t key_event, uint8_t * vm);
extern void menubar_pressed(uint8_t key_event);

extern void display_area1_flush(uint8_t * vm);
extern void display_area1_flush_enable();
extern void display_battery_flush(uint8_t * vm);
extern void battery_flush_enable();
extern void display_bluetooth_flush(uint8_t * vm);
extern void display_power_off_timer_flush(uint8_t * vm);
extern void display_trumpet_flush(uint8_t * vm);
extern void display_lighting_flush(uint8_t * vm);
extern void display_real_time_flush(uint8_t * vm);

extern void display_area2_flush(uint8_t * vm);
extern void display_area2_flush_enable();
extern void display_measure_value_mode_flush(uint8_t * vm);
extern void display_recording_flush(uint8_t * vm);
extern void display_hold_flush(uint8_t * vm);
extern void display_relative_value_flush(uint8_t * vm);

extern void display_area3_flush(uint8_t * vm);
extern void display_area3_flush_enable();
extern void display_measure_value_flush(uint8_t * vm);
extern void display_measure_value_unit_flush(uint8_t * vm);
extern void measure_value_flush_enable();

extern void display_area4_flush(uint8_t * vm);
extern void display_area4_flush_enable();
extern void display_measure_lo_flush(uint8_t * vm);
extern void display_measure_loz_flush(uint8_t * vm);
extern void display_measure_ruler_flush(uint8_t * vm);
extern void display_measure_range_status_flush(uint8_t * vm);

extern void display_area5_flush(uint8_t * vm);
extern void display_area5_flush_enable();
extern void display_f1_menubar_flush(uint8_t * vm);
extern void display_f2_menubar_flush(uint8_t * vm);
extern void display_f3_menubar_flush(uint8_t * vm);
extern void display_f4_menubar_flush(uint8_t * vm);
extern void display_prev_menubar_flush(uint8_t * vm);
extern void display_next_menubar_flush(uint8_t * vm);
extern void menubar_flush_enable();
static void measure_interface(uint8_t * vm);

extern void display_setting_area2_flush(uint8_t * vm);
extern void display_setting_area2_flush_enable();
extern void display_setting_list_flush(uint8_t * vm);
static void setting_interface(uint8_t * vm);

extern void display_flush(uint8_t * vm);

// This related to tft driver
extern void tft_clear(uint8_t color);
extern void tft_flush_area(uint8_t area_num, uint8_t * vm);
extern void tft_flush(uint8_t * vm);

#endif
