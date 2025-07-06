
#include "display_show.h"
#include "fontlib.h"

struct status_logo_pool_t logo_pool = {.phead = 0, .ptail = 0,};

static void logo_state_refer()
{
    if (1) status_logo_input_pool(&logo_pool, BLUETOOTH, true);
    if (get_apo_time()) status_logo_input_pool(&logo_pool, POWEROFF_TIMER, true);
    if (get_sound_status()) status_logo_input_pool(&logo_pool, TRUMPET, true);
    if (1) status_logo_input_pool(&logo_pool, LIGHTING, true);
}

void dev_topbar_cont_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_TOPBAR_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);

    logo_state_refer();
}

void dev_battery_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_BAT;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    display_battery(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, WHITE, GRAY, 25, false, vm);
}

void dev_buletooth_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_BLE;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    struct status_logo_t logo = {0};
    if (status_logo_output_pool(&logo_pool, &logo) == false) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);

    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.status, vm);
}

void dev_poff_tim_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_POFF_TIM;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    struct status_logo_t logo = {0};
    if (status_logo_output_pool(&logo_pool, &logo) == false) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.status, vm);
}

void dev_trumpet_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_TRUMPET;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    struct status_logo_t logo = {0};
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.status, vm);
}

void dev_lighting_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_LIGHTING;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    struct status_logo_t logo = {0};
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.status, vm);
}

void dev_realtim_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_REAL_TIM;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_N1string(0, 0, CENTER_ALIGN, LAYOUT_R11, _area_idx, 
        get_real_time(), _MENU_LAST, WHITE, UNSELECT, vm);
}

void dmm_zone_cont_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_ZONE_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void dmm_mea_mod_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_RUN_STATE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);

    if (true == 1) display_N2string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        MANUAL_ALIGN, LAYOUT_R11, _area_idx, "MAX", _MENU_LAST, WHITE, UNSELECT, vm);
    else if (true == 2) display_N2string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        MANUAL_ALIGN, LAYOUT_R11, _area_idx, "MIN", _MENU_LAST, WHITE, UNSELECT, vm);
    else if (true == 3) display_N2string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        MANUAL_ALIGN, LAYOUT_R11, _area_idx, "AVG", _MENU_LAST, WHITE, UNSELECT, vm);
}

void dmm_rec_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_REC;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_recording_mark(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, WHITE, RED, 1, vm);
}

void dmm_hold_state_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_HOLD;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (1) display_hold_mark(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, WHITE, RED, 1, vm);
}

void dmm_rel_val_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_REL_VAL;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);

    if (1) {
        display_hollow_triangle(_Area[_area_idx].set_y + 2, _Area[_area_idx].set_x - 16, 16, 16, WHITE, vm);
        display_hollow_triangle(_Area[_area_idx].set_y + 3, _Area[_area_idx].set_x - 16 + 1, 14, 14, WHITE, vm);
        display_N3string(0, 0, RIGHT_ALIGN, LAYOUT_R11, _area_idx, 
            "-225.66mV", _MENU_LAST, WHITE, UNSELECT, vm);
    }
}

void dmm_ret_cont_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_RET_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void dmm_ret_val_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_RET_VAL;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    static float measure_value = 225.55;
    uint8_t measure_string[8];
    static uint8_t speed;

    if (speed % 10 == 0) {
        if (measure_value < 255.55) measure_value += 1;
        else measure_value = 0.55;
    }
    speed++;
    sprintf(measure_string, "%06.2f", measure_value);

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_N4string(86, 0, RIGHT_ALIGN, LAYOUT_R11, 
        _area_idx, measure_string, _MENU_LAST, WHITE, UNSELECT, vm);

    display_tips(26, 0, 320, WHITE, DARK_BLUE, FONT_N2_PT, &message_tips[0], vm);
    tips_timing(&message_tips[0]);
}

void dmm_ret_unit_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_RET_UNIT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_sym(_Area[_area_idx].set_y - 10, _Area[_area_idx].set_x + 24, 
        WHITE, BLACK, DC_DESC, 1, vm);
    display_N3string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        RIGHT_ALIGN, LAYOUT_R11, _area_idx, "mV", _MENU_LAST, WHITE, UNSELECT, vm);
}

void dmm_bcht_cont_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_BCHT_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_BCHT_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void dmm_mea_lpf_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_LOZ;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_BCHT_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (1) display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, BLACK, LO, 1, vm);
}

void dmm_loz_state_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_LOZ;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_BCHT_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (1) display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, BLACK, LOZ, 1, vm);
}

void dmm_bcht_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_BCHT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_BCHT_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height + 15, BLACK, vm);
    if (1) display_barchart(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, BLACK, 60, 600, vm);
}

void dmm_run_state_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_RANGE_STATUS;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    if (0) {
        display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
            _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
        display_N1string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
            MANUAL_ALIGN, LAYOUT_R11, _area_idx, "AUTO", _MENU_LAST, WHITE, UNSELECT, vm);
    }
}

void dmm_actbar_cont_fefer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_ACTBAR_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void dmm_f1_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F1_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F1_KEY_EVT, vm);
}

void dmm_f2_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F2_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F2_KEY_EVT, vm);
}

void dmm_f3_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F3_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F3_KEY_EVT, vm);
}

void dmm_f4_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F4_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F4_KEY_EVT, vm);
}

void dmm_prev_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_PREV_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(PREV_KEY_EVT, vm);
}

void dmm_next_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_NEXT_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(NEXT_KEY_EVT, vm);
}

void ctl_tabv_cont_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_TABV_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

#define LINE_GAP     5
#define LIST_LINE0_Y (_Area[_area_idx].set_y + LINE_GAP * 0 + _Area[_area_idx].height * 0)
#define LIST_LINE1_Y (_Area[_area_idx].set_y + LINE_GAP * 1 + _Area[_area_idx].height * 1)
#define LIST_LINE2_Y (_Area[_area_idx].set_y + LINE_GAP * 2 + _Area[_area_idx].height * 2)
#define LIST_LINE3_Y (_Area[_area_idx].set_y + LINE_GAP * 3 + _Area[_area_idx].height * 3)
#define LIST_LINE4_Y (_Area[_area_idx].set_y + LINE_GAP * 4 + _Area[_area_idx].height * 4)
#define LIST_LINE5_Y (_Area[_area_idx].set_y + LINE_GAP * 5 + _Area[_area_idx].height * 5)
#define LIST_LINE6_Y (_Area[_area_idx].set_y + LINE_GAP * 6 + _Area[_area_idx].height * 6)
#define LIST_LINE7_Y (_Area[_area_idx].set_y + LINE_GAP * 7 + _Area[_area_idx].height * 7)

void ctl_tabv_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_TABV;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    display_dock(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, RED, GRAY, 8, LINE_GAP, get_vpos_selected(), vm);

    uint8_t list_item_color[8];
    uint8_t selected[3];

    memset(list_item_color, WHITE, 8);
    list_item_color[get_vpos_selected()] = WHITE;

    if (get_page_selected() == 0) {
        display_bookmark(LIST_LINE7_Y, _Area[_area_idx].set_x + 282, 34, 16, RED, 8, vm);
        display_N2string(LIST_LINE7_Y + 1, _Area[_area_idx].set_x + 284, MANUAL_ALIGN, LAYOUT_R11, 0, list_content[LIST_1_2],         _MENU_LAST, WHITE, UNSELECT, vm);
        display_N2string(LIST_LINE0_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_SET_TIME],    _MENU_LAST, list_item_color[0], UNSELECT, vm);
        display_N2string(LIST_LINE1_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_SET_DATE],    _MENU_LAST, list_item_color[1], UNSELECT, vm);
        display_N2string(LIST_LINE2_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_AUTO_SHTDWN], _MENU_LAST, list_item_color[2], UNSELECT, vm);
        display_N2string(LIST_LINE3_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_MAX], _MENU_LAST, list_item_color[3], UNSELECT, vm);
        display_N2string(LIST_LINE4_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_MIN], _MENU_LAST, list_item_color[4], UNSELECT, vm);
        display_N2string(LIST_LINE5_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_TYPE],_MENU_LAST, list_item_color[5], UNSELECT, vm);
        display_N2string(LIST_LINE6_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_RECORD_RATE], _MENU_LAST, list_item_color[6], UNSELECT, vm);
        display_N2string(LIST_LINE7_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_MEMORY_MODE], _MENU_LAST, list_item_color[7], UNSELECT, vm);

        if (get_param_number() == 0) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_hour(), _MENU_LAST, WHITE, selected[0], vm);
        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 20, MANUAL_ALIGN, LAYOUT_R11, 0, ":", _MENU_LAST, WHITE, UNSELECT, vm);
        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 28, MANUAL_ALIGN, LAYOUT_R11, 0, get_minute(), _MENU_LAST, WHITE, selected[1], vm);
        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 48, MANUAL_ALIGN, LAYOUT_R11, 0, ":", _MENU_LAST, WHITE, UNSELECT, vm);
        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 56, MANUAL_ALIGN, LAYOUT_R11, 0, get_second(), _MENU_LAST, WHITE, selected[2], vm);

        if (get_param_number() == 1) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_year(), _MENU_LAST, WHITE, selected[0], vm);
        display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 40, MANUAL_ALIGN, LAYOUT_R11, 0, "-", _MENU_LAST, WHITE, UNSELECT, vm);
        display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 48, MANUAL_ALIGN, LAYOUT_R11, 0, get_month(), _MENU_LAST, WHITE, selected[1], vm);
        display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 68, MANUAL_ALIGN, LAYOUT_R11, 0, "-", _MENU_LAST, WHITE, UNSELECT, vm);
        display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 76, MANUAL_ALIGN, LAYOUT_R11, 0, get_day(), _MENU_LAST, WHITE, selected[2], vm);

        if (get_param_number() == 2) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        switch (get_apo_time()) {
        case 0:
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "Off", _MENU_LAST, WHITE, selected[0], vm);
            break;
        case 1:
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "15", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 2:
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "30", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 3:
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "60", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 4:
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "120", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 5:
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "180", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        }

        if (get_param_number() == 3) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        if (selected[0]) {
            read_display_part_string(SETUP_COMP_MAX);
            _display_cn_string(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35, WHITE, BLACK, FONT_N2_PT, value_regulator.display_buf[1], read_cursor_position(), vm);
        } else display_N2string(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_comp_max(), _MENU_LAST, WHITE, selected[0], vm);

        if (get_param_number() == 4) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        if (selected[0]) {
            read_display_part_string(SETUP_COMP_MIN);
            _display_cn_string(LIST_LINE4_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35, WHITE, BLACK, FONT_N2_PT, value_regulator.display_buf[1], read_cursor_position(), vm);
        } else display_N2string(LIST_LINE4_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_comp_min(), _MENU_LAST, WHITE, selected[0], vm);

        if (get_param_number() == 5) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        if (get_comp_type() == 0) display_N2string(LIST_LINE5_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "INNER", _MENU_LAST, WHITE, selected[0], vm);
        else display_N2string(LIST_LINE5_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OUTER", _MENU_LAST, WHITE, selected[0], vm);

        if (get_param_number() == 6) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        display_N2string(LIST_LINE6_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_record_rate(), _MENU_LAST, WHITE, selected[0], vm);
        display_N2string(LIST_LINE6_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 17, MANUAL_ALIGN, LAYOUT_R11, 0, "s", _MENU_LAST, WHITE, UNSELECT, vm);

        if (get_param_number() == 7) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        if (get_memory_mode() == 0) display_N2string(LIST_LINE7_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "FIX", _MENU_LAST, WHITE, selected[0], vm);
        else display_N2string(LIST_LINE7_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "COVER", _MENU_LAST, WHITE, selected[0], vm);
    }

    if (get_page_selected() == 1) {
        display_bookmark(LIST_LINE7_Y, _Area[_area_idx].set_x + 282, 34, 16, RED, 8, vm);
        display_N2string(LIST_LINE7_Y + 1, _Area[_area_idx].set_x + 284, MANUAL_ALIGN, LAYOUT_R11, 0, list_content[LIST_2_2],            _MENU_LAST, WHITE, UNSELECT, vm);
        display_N2string(LIST_LINE0_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_BACK_LIGHT],     _MENU_LAST, list_item_color[0], UNSELECT, vm);
        display_N2string(LIST_LINE1_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_BACK_LIGHT_TIME],_MENU_LAST, list_item_color[1], UNSELECT, vm);
        display_N2string(LIST_LINE2_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_SOUND],          _MENU_LAST, list_item_color[2], UNSELECT, vm);
        display_N2string(LIST_LINE3_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_COLOR],          _MENU_LAST, list_item_color[3], UNSELECT, vm);

        if (get_param_number() == 8) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);
        
        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_back_light(), _MENU_LAST, WHITE, selected[0], vm);
        display_N2string(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 26, MANUAL_ALIGN, LAYOUT_R11, 0, "%", _MENU_LAST, WHITE, UNSELECT, vm);

        if (get_param_number() == 9) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);

        switch (get_light_time()) {
        case 0:
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OFF", _MENU_LAST, WHITE, selected[0], vm);
            break;
        case 1:
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "15", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 2:
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "30", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 3:
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "60", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        case 4:
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "120", _MENU_LAST, WHITE, selected[0], vm);
            display_N2string(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", _MENU_LAST, WHITE, UNSELECT, vm);
            break;
        }

        if (get_param_number() == 10) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);
        
        if (get_sound_status()) display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "ON", _MENU_LAST, WHITE, selected[0], vm);
        else display_N2string(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OFF", _MENU_LAST, WHITE, selected[0], vm);
    
        if (get_param_number() == 11) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else memset(selected, UNSELECT, 3);
        
        if (get_theme_color()) display_N2string(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "LIGHT", _MENU_LAST, WHITE, selected[0], vm);
        else display_N2string(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "DARK", _MENU_LAST, WHITE, selected[0], vm);
    }
}

void ctl_actbar_cont_fefer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_ACTBAR_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void ctl_f1_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F1_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F1_KEY_EVT, vm);
}

void ctl_f2_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F2_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F2_KEY_EVT, vm);
}

void ctl_f3_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F3_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F3_KEY_EVT, vm);
}

void ctl_f4_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F4_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F4_KEY_EVT, vm);
}

void ctl_prev_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_PREV_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(PREV_KEY_EVT, vm);
}

void ctl_next_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_NEXT_BTN;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(NEXT_KEY_EVT, vm);
}
