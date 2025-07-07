
#ifndef __DISPLAY_CONTROLLER_H__
#define __DISPLAY_CONTROLLER_H__

#include <stdbool.h>
#include <stdint.h>

#include "ili9341a.h"

#include "voltage_v.h"
#include "display_show.h"

#define FUNC_TYPE_MAX 16U
#define DEPTH_MAX  2U
#define _Area_NUM_MAX    40U

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

/**
 * Device display Area
 */
enum {
    DEV_TOPBAR_CONT = 0,
    DEV_BAT,
    DEV_BLE,
    DEV_POFF_TIM,
    DEV_TRUMPET,
    DEV_LIGHTING,
    DEV_REAL_TIM,

    DMM_ZONE_CONT,
    DMM_RUN_STATE,
    DMM_REC,
    DMM_HOLD,
    DMM_REL_VAL,

    DMM_RET_CONT,
    DMM_RET_VAL,
    DMM_RET_UNIT,

    DMM_BCHT_CONT,
    DMM_MEA_LPF,
    DMM_LOZ,
    DMM_BCHT,
    DMM_RANGE_STATUS,

    DMM_ACTBAR_CONT,
    DMM_F1_BTN,
    DMM_F2_BTN,
    DMM_F3_BTN,
    DMM_F4_BTN,
    DMM_PREV_BTN,
    DMM_NEXT_BTN,

    CTL_TABV_CONT,
    CTL_TABV,
    CTL_ACTBAR_CONT,
    CTL_F1_BTN,
    CTL_F2_BTN,
    CTL_F3_BTN,
    CTL_F4_BTN,
    CTL_PREV_BTN,
    CTL_NEXT_BTN,
};

typedef uint16_t nt_area_idx_t;

/**
 * NT activity type
 */
enum {
    NT_ACT_DMM = '0',
    NT_ACT_CTL = '1',
};

typedef uint8_t nt_act_type_t;

/**
 * Construct a activity type
 */
typedef struct {
    uint8_t last_act;
    uint8_t cur_act;
} nt_activity_t;

typedef void key_event_interface(uint8_t key);
typedef void menu_content_interface(uint8_t key_event, uint8_t * vm);
typedef void display_show_interface(uint8_t * vm);

typedef void (* tft_region_setting)(uint32_t y, uint32_t x, uint32_t width, uint32_t height);
typedef void (* tft_write_data)(uint32_t data);

extern const key_event_interface * key_event_controller[][DEPTH_MAX];
extern const key_event_interface * key_event_enable[][DEPTH_MAX];
extern const menu_content_interface * menu_str[][DEPTH_MAX];

extern dev_area_t _Area[_Area_NUM_MAX];
extern dev_actbar_t _dmm_actbar;
extern dev_actbar_t _ctl_actbar;

void _Area_init();
void load_activity(uint8_t _activity);
uint8_t read_cur_activity();
uint8_t read_last_activity();
void act_bar_set_func(dev_actbar_t * _actbar_p, uint8_t _func);
uint8_t act_bar_get_func(dev_actbar_t * _actbar_p);
uint8_t act_bar_get_last_func(dev_actbar_t * _actbar_p);
void act_bar_set_depth(dev_actbar_t * _actbar_p, uint8_t _depth);
uint8_t act_bar_get_depth(dev_actbar_t * _actbar_p);
void act_bar_set_page(dev_actbar_t * _actbar_p, uint8_t page);
uint8_t act_bar_get_page(dev_actbar_t * _actbar_p);
void act_bar_set_pressed(dev_actbar_t * _actbar_p, uint8_t _idx);
uint8_t act_bar_get_pressed(dev_actbar_t * _actbar_p);
void dmm_function_key_event(uint8_t key_event);
void dmm_function_key_event_enable(uint8_t key);
void dmm_display_actbar_content(uint8_t key_event, uint8_t * vm);
void actbar_btn_pressed(uint8_t key_event);
void dev_topbar_flush(uint8_t * vm);
void dev_topbar_cont_flush_enable();
void dmm_zone_flush(uint8_t * vm);
void dmm_zone_cont_flush_enable();
void dmm_ret_flush(uint8_t * vm);
void dmm_ret_cont_flush_enable();
void dmm_bcht_flush(uint8_t * vm);
void dmm_bcht_cont_flush_enable();
void dmm_actbar_flush(uint8_t * vm);
void dmm_actbar_cont_flush_enable();
void ctl_tabv_flush(uint8_t * vm);
void ctl_tabv_cont_flush_enable();
void display_flush(uint8_t * vm);
void tft_clear(uint8_t color);
void tft_flush_area(uint8_t area_num, uint8_t * vm);
void tft_flush(uint8_t * vm);

#endif
