/**
 * @file display_controller.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "setting.h"
#include "display_controller.h"
#include "display_show.h"
#include "voltage_v.h"
#include "ili9341a.h"
#include "key.h"
#include "display.h"
#include "setup.h"

/**********************
 *      TYPEDEFS
 **********************/

typedef void (* tft_region_setting)(uint32_t y, uint32_t x, uint32_t width, uint32_t height);
typedef void (* tft_write_data)(uint32_t data);


/**********************
 *  STATIC VARIABLES
 **********************/

/*Activity DMM*/
static const key_event_interface * dmm_key_event_controller[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {volt_level1_key_event, NULL},
};

static const key_event_interface * dmm_key_event_enable[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {volt_level1_key_event_enable, NULL},
};

static const menu_content_interface * dmm_display_menu_content[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {volt_level1_menu, NULL},
};

/*Activity CTL*/
static const key_event_interface * ctl_key_event_controller[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {setup_level1_key_event, NULL},
};

static const key_event_interface * ctl_key_event_enable[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {setup_level1_key_event_enable, NULL},
};

static const menu_content_interface * ctl_display_menu_content[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {setup_level1_menu, NULL},
};

dev_area_t _Area[_Area_NUM_MAX] = {0};
dev_actbar_t _dmm_actbar = {0};
dev_actbar_t _ctl_actbar = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void _Area_init()
{
    _Area[DEV_TOPBAR_CONT].set_y = 0;
    _Area[DEV_TOPBAR_CONT].set_x = 0;
    _Area[DEV_TOPBAR_CONT].width = 320;
    _Area[DEV_TOPBAR_CONT].height = 24;
    _Area[DEV_TOPBAR_CONT].valid = true;
    _Area[DEV_TOPBAR_CONT].refer = true;

    _Area[DEV_BAT].set_y = 4;
    _Area[DEV_BAT].set_x = 12;
    _Area[DEV_BAT].width = 23;
    _Area[DEV_BAT].height = 13;
    _Area[DEV_BAT].valid = true;
    _Area[DEV_BAT].refer = true;
    
    _Area[DEV_BLE].set_y = 3;
    _Area[DEV_BLE].set_x = 43;
    _Area[DEV_BLE].width = 16;
    _Area[DEV_BLE].height = 16;
    _Area[DEV_BLE].valid = true;
    _Area[DEV_BLE].refer = true;
    
    _Area[DEV_POFF_TIM].set_y = 3;
    _Area[DEV_POFF_TIM].set_x = 67;
    _Area[DEV_POFF_TIM].width = 16;
    _Area[DEV_POFF_TIM].height = 16;
    _Area[DEV_POFF_TIM].valid = true;
    _Area[DEV_POFF_TIM].refer = true;
    
    _Area[DEV_TRUMPET].set_y = 3;
    _Area[DEV_TRUMPET].set_x = 91;
    _Area[DEV_TRUMPET].width = 16;
    _Area[DEV_TRUMPET].height = 16;
    _Area[DEV_TRUMPET].valid = true;
    _Area[DEV_TRUMPET].refer = true;
    
    _Area[DEV_LIGHTING].set_y = 3;
    _Area[DEV_LIGHTING].set_x = 115;
    _Area[DEV_LIGHTING].width = 16;
    _Area[DEV_LIGHTING].height = 16;
    _Area[DEV_LIGHTING].valid = true;
    _Area[DEV_LIGHTING].refer = true;
    
    _Area[DEV_REAL_TIM].set_y = 5;
    _Area[DEV_REAL_TIM].set_x = 194;
    _Area[DEV_REAL_TIM].width = 123;
    _Area[DEV_REAL_TIM].height = 12;
    _Area[DEV_REAL_TIM].valid = true;
    _Area[DEV_REAL_TIM].refer = true;

    _Area[DMM_ZONE_CONT].set_y = 24;
    _Area[DMM_ZONE_CONT].set_x = 0;
    _Area[DMM_ZONE_CONT].width = 320;
    _Area[DMM_ZONE_CONT].height = 54;
    _Area[DMM_ZONE_CONT].valid = true;
    _Area[DMM_ZONE_CONT].refer = true;

    _Area[DMM_RUN_STATE].set_y = 37;
    _Area[DMM_RUN_STATE].set_x = 16;
    _Area[DMM_RUN_STATE].width = 40;
    _Area[DMM_RUN_STATE].height = 20;
    _Area[DMM_RUN_STATE].valid = true;
    _Area[DMM_RUN_STATE].refer = true;
    
    _Area[DMM_REC].set_y = 35;
    _Area[DMM_REC].set_x = 157;
    _Area[DMM_REC].width = 99;
    _Area[DMM_REC].height = 18;
    _Area[DMM_REC].valid = true;
    _Area[DMM_REC].refer = true;
    
    _Area[DMM_HOLD].set_y = 35;
    _Area[DMM_HOLD].set_x = 259;
    _Area[DMM_HOLD].width = 47;
    _Area[DMM_HOLD].height = 18;
    _Area[DMM_HOLD].valid = true;
    _Area[DMM_HOLD].refer = true;
    
    _Area[DMM_REL_VAL].set_y = 58;
    _Area[DMM_REL_VAL].set_x = 182;
    _Area[DMM_REL_VAL].width = 124;
    _Area[DMM_REL_VAL].height = 23;
    _Area[DMM_REL_VAL].valid = true;
    _Area[DMM_REL_VAL].refer = true;

    _Area[DMM_RET_CONT].set_y = 78;
    _Area[DMM_RET_CONT].set_x = 0;
    _Area[DMM_RET_CONT].width = 320;
    _Area[DMM_RET_CONT].height = 84;
    _Area[DMM_RET_CONT].valid = true;
    _Area[DMM_RET_CONT].refer = true;

    _Area[DMM_RET_VAL].set_y = 83;
    _Area[DMM_RET_VAL].set_x = 15;
    _Area[DMM_RET_VAL].width = 250;
    _Area[DMM_RET_VAL].height = 70;
    _Area[DMM_RET_VAL].valid = true;
    _Area[DMM_RET_VAL].refer = true;
    
    _Area[DMM_RET_UNIT].set_y = 130;
    _Area[DMM_RET_UNIT].set_x = 266;
    _Area[DMM_RET_UNIT].width = 42;
    _Area[DMM_RET_UNIT].height = 19;
    _Area[DMM_RET_UNIT].valid = true;
    _Area[DMM_RET_UNIT].refer = true;
    
    _Area[DMM_MEA_LPF].set_y = 189;
    _Area[DMM_MEA_LPF].set_x = 5;
    _Area[DMM_MEA_LPF].width = 32;
    _Area[DMM_MEA_LPF].height = 15;
    _Area[DMM_MEA_LPF].valid = true;
    _Area[DMM_MEA_LPF].refer = true;
    
    _Area[DMM_LOZ].set_y = 189;
    _Area[DMM_LOZ].set_x = 293;
    _Area[DMM_LOZ].width = 32;
    _Area[DMM_LOZ].height = 12;
    _Area[DMM_LOZ].valid = true;
    _Area[DMM_LOZ].refer = true;

    _Area[DEV_ALERTS].set_y = 32;
    _Area[DEV_ALERTS].set_x = 0;
    _Area[DEV_ALERTS].width = 0;
    _Area[DEV_ALERTS].height = 0;
    _Area[DEV_ALERTS].valid = true;
    _Area[DEV_ALERTS].refer = true;

    _Area[DMM_BCHT_CONT].set_y = 162;
    _Area[DMM_BCHT_CONT].set_x = 0;
    _Area[DMM_BCHT_CONT].width = 320;
    _Area[DMM_BCHT_CONT].height = 53;
    _Area[DMM_BCHT_CONT].valid = true;
    _Area[DMM_BCHT_CONT].refer = true;

    _Area[DMM_BCHT].set_y = 170;
    _Area[DMM_BCHT].set_x = 29;
    _Area[DMM_BCHT].width = 240;
    _Area[DMM_BCHT].height = 20;
    _Area[DMM_BCHT].valid = true;
    _Area[DMM_BCHT].refer = true;
    
    _Area[DMM_RANGE_STATUS].set_y = 37;
    _Area[DMM_RANGE_STATUS].set_x = 16;
    _Area[DMM_RANGE_STATUS].width = 40;
    _Area[DMM_RANGE_STATUS].height = 8;
    _Area[DMM_RANGE_STATUS].valid = true;
    _Area[DMM_RANGE_STATUS].refer = true;

    _Area[DMM_ACTBAR_CONT].set_y = 215;
    _Area[DMM_ACTBAR_CONT].set_x = 0;
    _Area[DMM_ACTBAR_CONT].width = 320;
    _Area[DMM_ACTBAR_CONT].height = 24;
    _Area[DMM_ACTBAR_CONT].valid = true;
    _Area[DMM_ACTBAR_CONT].refer = true;

    _Area[DMM_F1_BTN].set_y = 215;
    _Area[DMM_F1_BTN].set_x = 21;
    _Area[DMM_F1_BTN].width = 68;
    _Area[DMM_F1_BTN].height = 24;
    _Area[DMM_F1_BTN].valid = true;
    _Area[DMM_F1_BTN].refer = true;
    
    _Area[DMM_F2_BTN].set_y = 215;
    _Area[DMM_F2_BTN].set_x = 91;
    _Area[DMM_F2_BTN].width = 68;
    _Area[DMM_F2_BTN].height = 24;
    _Area[DMM_F2_BTN].valid = true;
    _Area[DMM_F2_BTN].refer = true;
    
    _Area[DMM_F3_BTN].set_y = 215;
    _Area[DMM_F3_BTN].set_x = 161;
    _Area[DMM_F3_BTN].width = 68;
    _Area[DMM_F3_BTN].height = 24;
    _Area[DMM_F3_BTN].valid = true;
    _Area[DMM_F3_BTN].refer = true;
    
    _Area[DMM_F4_BTN].set_y = 215;
    _Area[DMM_F4_BTN].set_x = 231;
    _Area[DMM_F4_BTN].width = 68;
    _Area[DMM_F4_BTN].height = 24;
    _Area[DMM_F4_BTN].valid = true;
    _Area[DMM_F4_BTN].refer = true;
    
    _Area[DMM_PREV_BTN].set_y = 215;
    _Area[DMM_PREV_BTN].set_x = 0;
    _Area[DMM_PREV_BTN].width = 19;
    _Area[DMM_PREV_BTN].height = 24;
    _Area[DMM_PREV_BTN].valid = true;
    _Area[DMM_PREV_BTN].refer = true;
    
    _Area[DMM_NEXT_BTN].set_y = 215;
    _Area[DMM_NEXT_BTN].set_x = 301;
    _Area[DMM_NEXT_BTN].width = 19;
    _Area[DMM_NEXT_BTN].height = 24;
    _Area[DMM_NEXT_BTN].valid = true;
    _Area[DMM_NEXT_BTN].refer = true;

    _Area[CTL_TABV_CONT].set_y = 24;
    _Area[CTL_TABV_CONT].set_x = 0;
    _Area[CTL_TABV_CONT].width = 320;
    _Area[CTL_TABV_CONT].height = 191;
    _Area[CTL_TABV_CONT].valid = true;
    _Area[CTL_TABV_CONT].refer = true;

    _Area[CTL_TABV].set_y = 33;
    _Area[CTL_TABV].set_x = 3;
    _Area[CTL_TABV].width = 157;
    _Area[CTL_TABV].height = 17;
    _Area[CTL_TABV].valid = true;
    _Area[CTL_TABV].refer = true;

    _Area[CTL_ACTBAR_CONT].set_y = 215;
    _Area[CTL_ACTBAR_CONT].set_x = 0;
    _Area[CTL_ACTBAR_CONT].width = 320;
    _Area[CTL_ACTBAR_CONT].height = 24;
    _Area[CTL_ACTBAR_CONT].valid = true;
    _Area[CTL_ACTBAR_CONT].refer = true;

    _Area[CTL_F1_BTN].set_y = 215;
    _Area[CTL_F1_BTN].set_x = 21;
    _Area[CTL_F1_BTN].width = 68;
    _Area[CTL_F1_BTN].height = 24;
    _Area[CTL_F1_BTN].valid = true;
    _Area[CTL_F1_BTN].refer = true;
    
    _Area[CTL_F2_BTN].set_y = 215;
    _Area[CTL_F2_BTN].set_x = 91;
    _Area[CTL_F2_BTN].width = 68;
    _Area[CTL_F2_BTN].height = 24;
    _Area[CTL_F2_BTN].valid = true;
    _Area[CTL_F2_BTN].refer = true;
    
    _Area[CTL_F3_BTN].set_y = 215;
    _Area[CTL_F3_BTN].set_x = 161;
    _Area[CTL_F3_BTN].width = 68;
    _Area[CTL_F3_BTN].height = 24;
    _Area[CTL_F3_BTN].valid = true;
    _Area[CTL_F3_BTN].refer = true;
    
    _Area[CTL_F4_BTN].set_y = 215;
    _Area[CTL_F4_BTN].set_x = 231;
    _Area[CTL_F4_BTN].width = 68;
    _Area[CTL_F4_BTN].height = 24;
    _Area[CTL_F4_BTN].valid = true;
    _Area[CTL_F4_BTN].refer = true;
    
    _Area[CTL_PREV_BTN].set_y = 215;
    _Area[CTL_PREV_BTN].set_x = 0;
    _Area[CTL_PREV_BTN].width = 19;
    _Area[CTL_PREV_BTN].height = 24;
    _Area[CTL_PREV_BTN].valid = true;
    _Area[CTL_PREV_BTN].refer = true;
    
    _Area[CTL_NEXT_BTN].set_y = 215;
    _Area[CTL_NEXT_BTN].set_x = 301;
    _Area[CTL_NEXT_BTN].width = 19;
    _Area[CTL_NEXT_BTN].height = 24;
    _Area[CTL_NEXT_BTN].valid = true;
    _Area[CTL_NEXT_BTN].refer = true;
}

nt_activity_t activity = {
    .last_act = 0xFF,
    .cur_act = 0xFF,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void load_activity(uint8_t _activity)
{
    /*if (activity.last_act != activity.cur_act)
        activity.last_act = activity.cur_act;
    activity.cur_act = _activity;*/

    /*This makes it easy to 
    mount custom content*/
    switch(_activity) {
    case NT_ACT_DMM:
        if (activity.last_act != activity.cur_act)
            activity.last_act = activity.cur_act;
        activity.cur_act = NT_ACT_DMM;
        break;

    case NT_ACT_CTL:
        if (activity.last_act != activity.cur_act)
            activity.last_act = activity.cur_act;
        activity.cur_act = NT_ACT_CTL;
        break;
    }
}

uint8_t read_cur_activity()
{
    return activity.cur_act;
}

uint8_t read_last_activity()
{
    return activity.last_act;
}

void act_bar_set_func(dev_actbar_t * _actbar_p, uint8_t _func)
{
    if (_func == _actbar_p->func) return;

    _actbar_p->_func = _actbar_p->func;
    _actbar_p->func = _func;
}

uint8_t act_bar_get_func(dev_actbar_t * _actbar_p)
{
    return _actbar_p->func;
}

uint8_t act_bar_get_last_func(dev_actbar_t * _actbar_p)
{
    return _actbar_p->_func;
}

void act_bar_set_depth(dev_actbar_t * _actbar_p, uint8_t _depth)
{
    uint8_t func = act_bar_get_func(_actbar_p);
    _actbar_p->_depth[func] = _depth;
}

uint8_t act_bar_get_depth(dev_actbar_t * _actbar_p)
{
    uint8_t func = act_bar_get_func(_actbar_p);
    return _actbar_p->_depth[func];
}

void act_bar_set_page(dev_actbar_t * _actbar_p, uint8_t page)
{
    uint8_t func = act_bar_get_func(_actbar_p);
    _actbar_p->page[func] = page;
}

uint8_t act_bar_get_page(dev_actbar_t * _actbar_p)
{
    uint8_t func = act_bar_get_func(_actbar_p);
    return _actbar_p->page[func];
}

void act_bar_set_pressed(dev_actbar_t * _actbar_p, 
    uint8_t _idx)
{
    uint8_t func = act_bar_get_func(_actbar_p);
    uint8_t level = act_bar_get_depth(_actbar_p);
    _actbar_p->pressed[func][level] = _idx;
}

uint8_t act_bar_get_pressed(dev_actbar_t * _actbar_p)
{
    uint8_t func = act_bar_get_func(_actbar_p);
    uint8_t level = act_bar_get_depth(_actbar_p);
    return _actbar_p->pressed[func][level];
}

/*Activity DMM*/
void dmm_function_key_event(uint8_t key_event)
{
    uint8_t func = act_bar_get_func(&_dmm_actbar);
    uint8_t level = act_bar_get_depth(&_dmm_actbar);
    if (dmm_key_event_controller[func][level] != NULL)
    (*dmm_key_event_controller[func][level])(key_event);
}

void dmm_function_key_event_enable(uint8_t key)
{
    uint8_t func = act_bar_get_func(&_dmm_actbar);
    uint8_t level = act_bar_get_depth(&_dmm_actbar);
    if (dmm_key_event_enable[func][level] != NULL)
        (*dmm_key_event_enable[func][level])(key);
}

void dmm_display_actbar_content(uint8_t key_event, uint8_t * vm)
{
    uint8_t func = act_bar_get_func(&_dmm_actbar);
    uint8_t level = act_bar_get_depth(&_dmm_actbar);
    if (dmm_display_menu_content[func][level] != NULL)
        (*dmm_display_menu_content[func][level])(key_event, vm);
}

/*Activity CTL*/
void ctl_function_key_event(uint8_t key_event)
{
    uint8_t func = act_bar_get_func(&_ctl_actbar);
    uint8_t level = act_bar_get_depth(&_ctl_actbar);
    if (ctl_key_event_controller[func][level] != NULL)
    (*ctl_key_event_controller[func][level])(key_event);
}

void ctl_function_key_event_enable(uint8_t key)
{
    uint8_t func = act_bar_get_func(&_ctl_actbar);
    uint8_t level = act_bar_get_depth(&_ctl_actbar);
    if (ctl_key_event_enable[func][level] != NULL)
        (*ctl_key_event_enable[func][level])(key);
}

void ctl_display_actbar_content(uint8_t key_event, uint8_t * vm)
{
    uint8_t func = act_bar_get_func(&_ctl_actbar);
    uint8_t level = act_bar_get_depth(&_ctl_actbar);
    if (ctl_display_menu_content[func][level] != NULL)
        (*ctl_display_menu_content[func][level])(key_event, vm);
}

void actbar_btn_pressed(uint8_t key_event)
{
    if (!_Area[DMM_ACTBAR_CONT].valid) return;

    _Area[DMM_F1_BTN].pressed = false;
    _Area[DMM_F2_BTN].pressed = false;
    _Area[DMM_F3_BTN].pressed = false;
    _Area[DMM_F4_BTN].pressed = false;
    _Area[DMM_PREV_BTN].pressed = false;
    _Area[DMM_NEXT_BTN].pressed = false;

    switch (key_event) {
    case F1_KEY_EVT:
        _Area[DMM_F1_BTN].pressed = true;
        dmm_actbar_cont_flush_enable();
        break;
    case F2_KEY_EVT:
        _Area[DMM_F2_BTN].pressed = true;
        dmm_actbar_cont_flush_enable();
        break;
    case F3_KEY_EVT:
        _Area[DMM_F3_BTN].pressed = true;
        dmm_actbar_cont_flush_enable();
        break;
    case F4_KEY_EVT:
        _Area[DMM_F4_BTN].pressed = true;
        dmm_actbar_cont_flush_enable();
        break;
    case PREV_KEY_EVT:
        _Area[DMM_PREV_BTN].pressed = true;
        dmm_actbar_cont_flush_enable();
        break;
    case NEXT_KEY_EVT:
        _Area[DMM_NEXT_BTN].pressed = true;
        dmm_actbar_cont_flush_enable();
        break;
    case RELEASE:
        dmm_function_key_event_enable(F1_KEY_EVT);
        dmm_actbar_cont_flush_enable();
        break;
    }

    if (!_Area[CTL_ACTBAR_CONT].valid) return;

    _Area[CTL_F1_BTN].pressed = false;
    _Area[CTL_F2_BTN].pressed = false;
    _Area[CTL_F3_BTN].pressed = false;
    _Area[CTL_F4_BTN].pressed = false;
    _Area[CTL_PREV_BTN].pressed = false;
    _Area[CTL_NEXT_BTN].pressed = false;

    switch (key_event) {
    case F1_KEY_EVT:
        _Area[CTL_F1_BTN].pressed = true;
        ctl_actbar_cont_flush_enable();
        break;
    case F2_KEY_EVT:
        _Area[CTL_F2_BTN].pressed = true;
        ctl_actbar_cont_flush_enable();
        break;
    case F3_KEY_EVT:
        _Area[CTL_F3_BTN].pressed = true;
        ctl_actbar_cont_flush_enable();
        break;
    case F4_KEY_EVT:
        _Area[CTL_F4_BTN].pressed = true;
        ctl_actbar_cont_flush_enable();
        break;
    case PREV_KEY_EVT:
        _Area[CTL_PREV_BTN].pressed = true;
        ctl_actbar_cont_flush_enable();
        break;
    case NEXT_KEY_EVT:
        _Area[CTL_NEXT_BTN].pressed = true;
        ctl_actbar_cont_flush_enable();
        break;
    case RELEASE:
        ctl_function_key_event_enable(F1_KEY_EVT);
        ctl_actbar_cont_flush_enable();
        break;
    }
}

void dev_topbar_flush(uint8_t * vm)
{
    dev_topbar_cont_refer(vm);

    if (_Area[DEV_TOPBAR_CONT].refer) {
        _Area[DEV_BAT].refer = true;
        _Area[DEV_BLE].refer = true;
        _Area[DEV_POFF_TIM].refer = true;
        _Area[DEV_TRUMPET].refer = true;
        _Area[DEV_LIGHTING].refer = true;
        _Area[DEV_REAL_TIM].refer = true;
    }

    dev_battery_refer(vm);
    _Area[DEV_BAT].refer = false;

    dev_buletooth_refer(vm);
    _Area[DEV_BLE].refer = false;

    dev_poff_tim_refer(vm);
    _Area[DEV_POFF_TIM].refer = false;

    dev_trumpet_refer(vm);
    _Area[DEV_TRUMPET].refer = false;

    dev_lighting_refer(vm);
    _Area[DEV_LIGHTING].refer = false;

    dev_realtim_refer(vm);
    _Area[DEV_REAL_TIM].refer = false;
}

void dev_topbar_cont_flush_enable()
{
    if (_Area[DEV_TOPBAR_CONT].valid)
        _Area[DEV_TOPBAR_CONT].refer = true;
}

void dmm_zone_flush(uint8_t * vm)
{
    dmm_zone_cont_refer(vm);

    if (_Area[DMM_ZONE_CONT].refer) {
        _Area[DMM_RUN_STATE].refer = true;
        _Area[DMM_REC].refer = true;
        _Area[DMM_HOLD].refer = true;
        _Area[DMM_REL_VAL].refer = true;
        _Area[DEV_ALERTS].refer = true;
    }

    dmm_mea_mod_refer(vm);
    _Area[DMM_RUN_STATE].refer = false;

    dmm_rec_refer(vm);
    _Area[DMM_REC].refer = false;

    dmm_hold_state_refer(vm);
    _Area[DMM_HOLD].refer = false;

    dmm_rel_val_refer(vm);
    _Area[DMM_REL_VAL].refer = false;

    dev_alerts_refer(vm);
    _Area[DEV_ALERTS].refer = false;
}

void dmm_zone_cont_flush_enable()
{
    if (_Area[DMM_ZONE_CONT].valid)
        _Area[DMM_ZONE_CONT].refer = true;
}

void dmm_ret_flush(uint8_t * vm)
{
    dmm_ret_cont_refer(vm);

    if (_Area[DMM_RET_CONT].refer) {
        _Area[DMM_RET_VAL].refer = true;
        _Area[DMM_RET_UNIT].refer = true;
    }

    dmm_ret_val_refer(vm);
    _Area[DMM_RET_VAL].refer = false;

    dmm_ret_unit_refer(vm);
    _Area[DMM_RET_UNIT].refer = false;
}

void dmm_ret_cont_flush_enable()
{
    if (_Area[DMM_RET_CONT].valid)
        _Area[DMM_RET_CONT].refer = true;
}

void dmm_bcht_flush(uint8_t * vm)
{
    dmm_bcht_cont_refer(vm);

    if (_Area[DMM_BCHT_CONT].refer) {
        _Area[DMM_MEA_LPF].refer = true;
        _Area[DMM_LOZ].refer = true;
        _Area[DMM_BCHT].refer = true;
        _Area[DMM_RANGE_STATUS].refer = true;
    }

    dmm_mea_lpf_refer(vm);
    _Area[DMM_MEA_LPF].refer = false;

    dmm_loz_state_refer(vm);
    _Area[DMM_LOZ].refer = false;

    dmm_bcht_refer(vm);
    _Area[DMM_BCHT].refer = false;

    dmm_run_state_refer(vm);
    _Area[DMM_RANGE_STATUS].refer = false;
}

void dmm_bcht_cont_flush_enable()
{
    if (_Area[DMM_BCHT_CONT].valid)
        _Area[DMM_BCHT_CONT].refer = true;
}

void dmm_actbar_flush(uint8_t * vm)
{
    dmm_actbar_cont_fefer(vm);

    if (_Area[DMM_ACTBAR_CONT].refer) {
        _Area[DMM_F1_BTN].refer = true;
        _Area[DMM_F2_BTN].refer = true;
        _Area[DMM_F3_BTN].refer = true;
        _Area[DMM_F4_BTN].refer = true;
        _Area[DMM_PREV_BTN].refer = true;
        _Area[DMM_NEXT_BTN].refer = true;
    }

    dmm_f1_btn_refer(vm);
    _Area[DMM_F1_BTN].refer = false;

    dmm_f2_btn_refer(vm);
    _Area[DMM_F2_BTN].refer = false;

    dmm_f3_btn_refer(vm);
    _Area[DMM_F3_BTN].refer = false;

    dmm_f4_btn_refer(vm);
    _Area[DMM_F4_BTN].refer = false;

    dmm_prev_btn_refer(vm);
    _Area[DMM_PREV_BTN].refer = false;

    dmm_next_btn_refer(vm);
    _Area[DMM_NEXT_BTN].refer = false;
}

void dmm_actbar_cont_flush_enable()
{
    if (_Area[DMM_ACTBAR_CONT].valid)
        _Area[DMM_ACTBAR_CONT].refer = true;
}

static void dmm_activity(uint8_t * vm)
{
    dmm_zone_cont_flush_enable();
    dmm_ret_cont_flush_enable();
    dmm_bcht_cont_flush_enable();
    dmm_actbar_cont_flush_enable();

    dmm_zone_flush(vm);
    dmm_ret_flush(vm);
    dmm_bcht_flush(vm);
    dmm_actbar_flush(vm);
}

void ctl_tabv_flush(uint8_t * vm)
{
    ctl_tabv_cont_refer(vm);

    if (_Area[CTL_TABV_CONT].refer) {
        _Area[CTL_TABV].refer = true;
    }

    ctl_tabv_refer(vm);
    _Area[CTL_TABV].refer = false;
}

void ctl_tabv_cont_flush_enable()
{
    if (_Area[CTL_TABV_CONT].valid)
        _Area[CTL_TABV_CONT].refer = true;
}

void ctl_actbar_flush(uint8_t * vm)
{
    ctl_actbar_cont_fefer(vm);

    if (_Area[CTL_ACTBAR_CONT].refer) {
        _Area[CTL_F1_BTN].refer = true;
        _Area[CTL_F2_BTN].refer = true;
        _Area[CTL_F3_BTN].refer = true;
        _Area[CTL_F4_BTN].refer = true;
        _Area[CTL_PREV_BTN].refer = true;
        _Area[CTL_NEXT_BTN].refer = true;
    }

    ctl_f1_btn_refer(vm);
    _Area[CTL_F1_BTN].refer = false;

    ctl_f2_btn_refer(vm);
    _Area[CTL_F2_BTN].refer = false;

    ctl_f3_btn_refer(vm);
    _Area[CTL_F3_BTN].refer = false;

    ctl_f4_btn_refer(vm);
    _Area[CTL_F4_BTN].refer = false;

    ctl_prev_btn_refer(vm);
    _Area[CTL_PREV_BTN].refer = false;

    ctl_next_btn_refer(vm);
    _Area[CTL_NEXT_BTN].refer = false;
}

void ctl_actbar_cont_flush_enable()
{
    if (_Area[CTL_ACTBAR_CONT].valid) 
        _Area[CTL_ACTBAR_CONT].refer = true;
}

static void ctl_activity(uint8_t * vm)
{
    ctl_tabv_flush(vm);
    ctl_actbar_flush(vm);
}

void display_flush(uint8_t * vm)
{
    uint8_t _act = read_cur_activity();

    dev_topbar_cont_flush_enable();
    dev_topbar_flush(vm);

    switch (_act) {
    case NT_ACT_DMM:
        dmm_activity(vm);
        break;
    case NT_ACT_CTL:
        ctl_activity(vm);
        break;
    default:
        dmm_activity(vm);
        break;
    }
}

const tft_region_setting tft_region = \
    (const tft_region_setting)TFT_REGION_SETTING_DRV;
const tft_write_data tft_write = \
    (const tft_write_data)TFT_WRITE_DATA_DRV;

void tft_flush(uint8_t * vm)
{
    uint8_t _dark = _devset.display.dark * _COLOR_LAST;
    uint16_t * colorTrue = req_colorTrue();
    uint16_t colorVM = BLACK;

    tft_region(0, 0, TFT_WIDTH, TFT_HEIGHT);

    for (uint32_t y = 0; y < TFT_HEIGHT; y++) {
        for (uint32_t x = 0; x < TFT_WIDTH; x++) {
            colorVM = vm[y * TFT_WIDTH + x];
            tft_write(colorTrue[colorVM + _dark]);
        }
    }
}

void tft_clear(uint8_t color)
{
    uint16_t * colorTrue = req_colorTrue();
    uint32_t buf_size = 0;

    buf_size = TFT_WIDTH * TFT_HEIGHT;
    tft_region(0, 0, TFT_WIDTH, TFT_HEIGHT);

    for (uint32_t i = 0; i < buf_size; i++)
        tft_write(colorTrue[color]);
}
