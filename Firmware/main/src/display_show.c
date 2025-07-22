/**
 * @file display_show.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <math.h>

#include "idenMang.h"
#include "display.h"
#include "display_string.h"
#include "display_controller.h"

#include "log.h"
#include "regulator.h"
#include "setup.h"

#include "display_show.h"
#include "menu_str.h"
#include "fontlib.h"
#include "key.h"

/*********************
 *      DEFINES
 *********************/

#define _DATE_  "%04d/%02d/%02d"
#define _DATE2_ "%02d/%02d/%04d"
#define _TIME_  "%02d:%02d:%02d"

/**********************
 *  STATIC VARIABLES
 **********************/

static _iden_mang_t iden_qq = {.phead = 0, .ptail = 0,};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void dev_iden_qq_refer()
{
    if (1) iden_qq_ins(&iden_qq, SYM_BLE, true);
    if (lv_apoff_get_val()) iden_qq_ins(&iden_qq, SYM_POFF, true);
    if (lv_voice_get_state_val()) iden_qq_ins(&iden_qq, SYM_TRUMPET, true);
    if (1) iden_qq_ins(&iden_qq, SYM_LIGHTING, true);
}

void dev_topbar_cont_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_TOPBAR_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);

    dev_iden_qq_refer();
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

    _iden_t logo = {0};
    if (iden_qq_remove(&iden_qq, &logo) == false) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);

    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.state, vm);
}

void dev_poff_tim_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_POFF_TIM;

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    _iden_t logo = {0};
    if (iden_qq_remove(&iden_qq, &logo) == false) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.state, vm);
}

void dev_trumpet_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_TRUMPET;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    _iden_t logo = {0};
    if (iden_qq_remove(&iden_qq, &logo) == false)
        return;

    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.state, vm);
}

void dev_lighting_refer(uint8_t * vm)
{
    uint16_t _area_idx = DEV_LIGHTING;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    _iden_t logo = {0};
    if (iden_qq_remove(&iden_qq, &logo) == false)
        return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, GRAY, logo.name, logo.state, vm);
}

void dev_realtim_refer(uint8_t * vm)
{
    uint32_t _area_idx = DEV_REAL_TIM;
    uint8_t _act = read_cur_activity();
    uint8_t opt_idx = lv_tab_get_opti_id();

    if ((!_Area[_area_idx].refer) || (!_Area[DEV_TOPBAR_CONT].valid)) return;

    uint8_t tran = lv_date_tran_get_val();

    uint16_t year = lv_date_year_get_val();
    uint8_t month = lv_date_month_get_val();
    uint8_t day = lv_date_day_get_val();

    uint8_t hour = lv_time_hour_get_val();
    uint8_t min = lv_time_min_get_val();
    uint8_t sec = lv_time_sec_get_val();

    if (
        (_act != NT_ACT_CTL) || 
        ((opt_idx != DEV_DATE) && 
            (opt_idx != DEV_TIM))
    ) {
        year = 0/*get_rtc_year()*/ + 2000;
        month = 1/*get_rtc_month()*/;
        day = 1/*get_rtc_day()*/;

        hour = 5/*get_rtc_hour()*/;
        min = 5/*get_rtc_minute()*/;
        sec = 5/*get_rtc_second()*/;
    }

    uint8_t _date_p[10 + 1] = {0};
    uint8_t _time_p[8 + 1] = {0};

    memset(_date_p, '\0', sizeof(uint8_t) * 11);

    if (!tran) {
        snprintf(_date_p, 11, _DATE_, 
            year, month, day);
    } else {
        snprintf(_date_p, 11, _DATE2_, 
            day, month, year);
    }

    memset(_time_p, '\0', sizeof(uint8_t) * 9);

    snprintf(_time_p, 9, _TIME_, 
        hour, min, sec);

    display_N1string(4, 192, ALIGN_SPECIFY, 
        LAYOUT_R11, _area_idx, _date_p, 
        _MENU_LAST, WHITE, INVE_NONE, vm);

    display_N1string(4, 192 + 75, ALIGN_SPECIFY, 
        LAYOUT_R11, _area_idx, _time_p, 
        _MENU_LAST, WHITE, INVE_NONE, vm);
}

void dev_alerts_refer(unsigned char * vm)
{
    uint16_t _area_idx = DEV_ALERTS;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;

    alerts_refer(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        TFT_WIDTH, WHITE, GRAY, FONT_N2_PT, &alerts[0], vm);
    alerts_tick_work(&alerts[0]);
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
    if (alerts_is_active(alerts, 5)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);

    if (true == 1) display_N2string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        ALIGN_SPECIFY, LAYOUT_R11, _area_idx, "Max", _MENU_LAST, WHITE, INVE_NONE, vm);
    else if (true == 2) display_N2string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        ALIGN_SPECIFY, LAYOUT_R11, _area_idx, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
    else if (true == 3) display_N2string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        ALIGN_SPECIFY, LAYOUT_R11, _area_idx, "Avg", _MENU_LAST, WHITE, INVE_NONE, vm);
}

void dmm_rec_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_REC;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;
    if (alerts_is_active(alerts, 5)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, RED, vm);
    display_N2string(_Area[_area_idx].set_y + 2, _Area[_area_idx].set_x + 2, 
        ALIGN_SPECIFY, LAYOUT_R11, 0, "RECORDING", _MENU_LAST, WHITE, INVE_NONE, vm);
}

void dmm_hold_state_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_HOLD;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;
    if (alerts_is_active(alerts, 5)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (1) {
        display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
            _Area[_area_idx].width, _Area[_area_idx].height, RED, vm);
        display_N2string(_Area[_area_idx].set_y + 2, _Area[_area_idx].set_x + 2, 
            ALIGN_SPECIFY, LAYOUT_R11, 0, "HOLD", _MENU_LAST, WHITE, INVE_NONE, vm);
    }
}

void dmm_rel_val_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_REL_VAL;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ZONE_CONT].valid)) return;
    if (alerts_is_active(alerts, 5)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);

    if (1) {
        display_hollow_triangle(_Area[_area_idx].set_y + 2, _Area[_area_idx].set_x - 16, 16, 16, WHITE, vm);
        display_hollow_triangle(_Area[_area_idx].set_y + 3, _Area[_area_idx].set_x - 16 + 1, 14, 14, WHITE, vm);
        display_N3string(0, 0, ALIGN_RIGHT, LAYOUT_R11, _area_idx, 
            "-225.66mV", _MENU_LAST, WHITE, INVE_NONE, vm);
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

    static uint8_t refer = 0;
    static float _value = 0.0f;
    uint8_t _str[12] = {0};

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    refer++;
    if (refer % 10 == 0) {
        _value += 1.0f;
    }

    if (_value > 999.0f) _value = 0.0f;

    sprintf(_str, "%06.2f", _value);
    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_N4string(86, 0, ALIGN_RIGHT, LAYOUT_R11, 
        _area_idx, _str, _MENU_LAST, WHITE, INVE_NONE, vm);
}

void dmm_ret_unit_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_RET_UNIT;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_RET_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_sym(_Area[_area_idx].set_y - 10, _Area[_area_idx].set_x + 24, 
        WHITE, BLACK, SYM_DC, 1, vm);
    display_N3string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        ALIGN_RIGHT, LAYOUT_R11, _area_idx, "mV", _MENU_LAST, WHITE, INVE_NONE, vm);
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
        WHITE, BLACK, SYM_LO, 1, vm);
}

void dmm_loz_state_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_LOZ;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_BCHT_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (1) display_sym(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        WHITE, BLACK, SYM_LOZ, 1, vm);
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
    if (alerts_is_active(alerts, 5)) return;

    if (0) {
        display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
            _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
        display_N1string(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
            ALIGN_SPECIFY, LAYOUT_R11, _area_idx, "Auto", _MENU_LAST, WHITE, INVE_NONE, vm);
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
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F1_KEY_EVT, vm);
}

void dmm_f2_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F2_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F2_KEY_EVT, vm);
}

void dmm_f3_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F3_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F3_KEY_EVT, vm);
}

void dmm_f4_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_F4_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(F4_KEY_EVT, vm);
}

void dmm_prev_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_PREV_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    dmm_display_actbar_content(PREV_KEY_EVT, vm);
}

void dmm_next_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = DMM_NEXT_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
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

#define ROW_SPAC  5U
#define LIST_Y(x) (_Area[_area_idx].set_y + \
    (_Area[_area_idx].height + ROW_SPAC) * (x))

void ctl_tabv_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_TABV;
    uint8_t itemcolor[8] = {0};
    uint8_t inverse[3] = {0};

    if ((!_Area[_area_idx].refer) || (!_Area[DMM_ACTBAR_CONT].valid)) return;

    if (lv_tab_get_page_id() == 0) display_dock(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, RED, GRAY, 8, ROW_SPAC, lv_tab_get_line_id(), vm);
    else display_dock(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, RED, GRAY, 4, ROW_SPAC, lv_tab_get_line_id(), vm);

    memset(itemcolor, WHITE, 8);
    itemcolor[lv_tab_get_line_id()] = WHITE;

    if (lv_tab_get_page_id() == 0) {
        display_N2string(LIST_Y(0) + 1, _Area[_area_idx].set_x + 284, ALIGN_SPECIFY, LAYOUT_R11, 0, list_content[LIST_1_2],         _MENU_LAST, WHITE, INVE_NONE, vm);
        display_N2string(LIST_Y(0) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_SET_TIME],    _MENU_LAST, itemcolor[0], INVE_NONE, vm);
        display_N2string(LIST_Y(1) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_SET_DATE],    _MENU_LAST, itemcolor[1], INVE_NONE, vm);
        display_N2string(LIST_Y(2) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_APOFF], _MENU_LAST, itemcolor[2], INVE_NONE, vm);
        display_N2string(LIST_Y(3) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_COMP_MAX], _MENU_LAST, itemcolor[3], INVE_NONE, vm);
        display_N2string(LIST_Y(4) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_COMP_MIN], _MENU_LAST, itemcolor[4], INVE_NONE, vm);
        display_N2string(LIST_Y(5) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_COMP_TYPE],_MENU_LAST, itemcolor[5], INVE_NONE, vm);
        display_N2string(LIST_Y(6) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_REC_RATE], _MENU_LAST, itemcolor[6], INVE_NONE, vm);
        display_N2string(LIST_Y(7) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11,  0, list_content[LIST_MEM_MODE], _MENU_LAST, itemcolor[7], INVE_NONE, vm);

        if (lv_tab_get_opti_id() == 0) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%02d", lv_time_hour_get_val());

        display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[0], vm);
        display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 20, ALIGN_SPECIFY, LAYOUT_R11, 0, ":", _MENU_LAST, WHITE, INVE_NONE, vm);
        
        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%02d", lv_time_min_get_val());

        display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 28, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[1], vm);
        display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 48, ALIGN_SPECIFY, LAYOUT_R11, 0, ":", _MENU_LAST, WHITE, INVE_NONE, vm);
        
        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%02d", lv_time_sec_get_val());

        display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 56, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[2], vm);

        if (lv_tab_get_opti_id() == 1) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%04d", lv_date_year_get_val());

        display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[0], vm);
        display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 40, ALIGN_SPECIFY, LAYOUT_R11, 0, "-", _MENU_LAST, WHITE, INVE_NONE, vm);
        
        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%02d", lv_date_month_get_val());

        display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 48, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[1], vm);
        display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 68, ALIGN_SPECIFY, LAYOUT_R11, 0, "-", _MENU_LAST, WHITE, INVE_NONE, vm);

        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%02d", lv_date_day_get_val());

        display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 76, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[2], vm);

        if (lv_tab_get_opti_id() == 2) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        switch (lv_apoff_get_val()) {
        case 0:
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Off", _MENU_LAST, WHITE, inverse[0], vm);
            break;
        case 1:
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "10", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 2:
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "20", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 3:
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "30", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 4:
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "60", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 5:
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "90", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        }

        if (lv_tab_get_opti_id() == 3) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%d", lv_comp_get_max_val());

        if (inverse[0]) {
            regu_disp_get_str(DEV_COMP_MAX);
            _display_cn_string(LIST_Y(3), _Area[_area_idx].set_x + _Area[_area_idx].width + 35, WHITE, BLACK, FONT_N2_PT, regu.refer[1], regu_cursor_get_pos(), vm);
        } else display_N2string(LIST_Y(3), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[0], vm);

        if (lv_tab_get_opti_id() == 4) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%d", lv_comp_get_min_val());

        if (inverse[0]) {
            regu_disp_get_str(DEV_COMP_MIN);
            _display_cn_string(LIST_Y(4), _Area[_area_idx].set_x + _Area[_area_idx].width + 35, WHITE, BLACK, FONT_N2_PT, regu.refer[1], regu_cursor_get_pos(), vm);
        } else display_N2string(LIST_Y(4), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[0], vm);

        if (lv_tab_get_opti_id() == 5) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        if (lv_comp_get_type_val() == 0) display_N2string(LIST_Y(5), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Inner", _MENU_LAST, WHITE, inverse[0], vm);
        else display_N2string(LIST_Y(5), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Outer", _MENU_LAST, WHITE, inverse[0], vm);

        if (lv_tab_get_opti_id() == 6) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        memset(_devset.dispstr, '\0', 32);
        sprintf(_devset.dispstr, "%d s", lv_record_get_rate_val());
        display_N2string(LIST_Y(6), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, _devset.dispstr, _MENU_LAST, WHITE, inverse[0], vm);

        if (lv_tab_get_opti_id() == 7) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        if (lv_mem_get_val() == 0) display_N2string(LIST_Y(7), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Fix", _MENU_LAST, WHITE, inverse[0], vm);
        else display_N2string(LIST_Y(7), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Cover", _MENU_LAST, WHITE, inverse[0], vm);
    }

    if (lv_tab_get_page_id() == 1) {
        display_N2string(LIST_Y(0) + 1, _Area[_area_idx].set_x + 284, ALIGN_SPECIFY, LAYOUT_R11, 0, list_content[LIST_2_2],     _MENU_LAST, WHITE, INVE_NONE, vm);
        display_N2string(LIST_Y(0) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11, 0,  list_content[LIST_BRIGHT],  _MENU_LAST, itemcolor[0], INVE_NONE, vm);
        display_N2string(LIST_Y(1) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11, 0,  list_content[LIST_DISP_ON], _MENU_LAST, itemcolor[1], INVE_NONE, vm);
        display_N2string(LIST_Y(2) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11, 0,  list_content[LIST_VOICE],   _MENU_LAST, itemcolor[2], INVE_NONE, vm);
        display_N2string(LIST_Y(3) + 1, _Area[_area_idx].set_x + 18, ALIGN_SPECIFY, LAYOUT_R11, 0,  list_content[LIST_DISP_MOD],   _MENU_LAST, itemcolor[3], INVE_NONE, vm);

        if (lv_tab_get_opti_id() == 8) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        switch (lv_bright_get_val()) {
        case 0:
            display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Auto", _MENU_LAST, WHITE, inverse[0], vm);
            break;
        case 1:
            display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Low", _MENU_LAST, WHITE, inverse[0], vm);
            break;
        case 2:
            display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Mid", _MENU_LAST, WHITE, inverse[0], vm);
            break;
        case 3:
            display_N2string(LIST_Y(0), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "High", _MENU_LAST, WHITE, inverse[0], vm);
            break;
        }

        if (lv_tab_get_opti_id() == 9) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);

        switch (lv_dispoff_get_val()) {
        case 0:
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Off", _MENU_LAST, WHITE, inverse[0], vm);
            break;
        case 1:
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "15", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 2:
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "30", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 3:
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "60", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        case 4:
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "90", _MENU_LAST, WHITE, inverse[0], vm);
            display_N2string(LIST_Y(1), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 25, ALIGN_SPECIFY, LAYOUT_R11, 0, "Min", _MENU_LAST, WHITE, INVE_NONE, vm);
            break;
        }

        if (lv_tab_get_opti_id() == 10) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);
        
        if (lv_voice_get_state_val()) display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "On", _MENU_LAST, WHITE, inverse[0], vm);
        else display_N2string(LIST_Y(2), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Off", _MENU_LAST, WHITE, inverse[0], vm);
    
        if (lv_tab_get_opti_id() == 11) {
            memset(inverse, INVE_NONE, 3);
            inverse[lv_tab_get_hidx()] = INVE_EN;
        } else memset(inverse, INVE_NONE, 3);
        
        if (lv_dark_get_val()) display_N2string(LIST_Y(3), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Light", _MENU_LAST, WHITE, inverse[0], vm);
        else display_N2string(LIST_Y(3), _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, ALIGN_SPECIFY, LAYOUT_R11, 0, "Dark", _MENU_LAST, WHITE, inverse[0], vm);
    }
}

void ctl_actbar_cont_fefer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_ACTBAR_CONT;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void ctl_f1_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_F1_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F1_KEY_EVT, vm);
}

void ctl_f2_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_F2_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F2_KEY_EVT, vm);
}

void ctl_f3_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_F3_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F3_KEY_EVT, vm);
}

void ctl_f4_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_F4_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = GRAY;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(F4_KEY_EVT, vm);
}

void ctl_prev_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_PREV_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(PREV_KEY_EVT, vm);
}

void ctl_next_btn_refer(uint8_t * vm)
{
    uint16_t _area_idx = CTL_NEXT_BTN;
    uint8_t color = WHITE;

    if ((!_Area[_area_idx].refer) || (!_Area[CTL_ACTBAR_CONT].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GRAY;
    else color = RED;

    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, 
        _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    ctl_display_actbar_content(NEXT_KEY_EVT, vm);
}
