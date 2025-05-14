
#include "display_show.h"

struct status_logo_pool_t logo_pool = {.phead = 0, .ptail = 0,};

uint8_t get_buletooth_status()
{
    return true;
}

uint8_t get_lighting_status()
{
    return true;
}

void get_status_logo_active()
{
    if (get_buletooth_status()) status_logo_input_pool(&logo_pool, BLUETOOTH, true);
    if (get_apo_time()) status_logo_input_pool(&logo_pool, POWEROFF_TIMER, true);
    if (get_sound_status()) status_logo_input_pool(&logo_pool, TRUMPET, true);
    if (get_lighting_status()) status_logo_input_pool(&logo_pool, LIGHTING, true);
}

void display_area1_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_TFT_AREA1;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA1].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    get_status_logo_active();
}

void display_battery_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_BATTERY_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA1].valid)) return;

    // power 0% - 100%
    display_battery(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, WHITE, GRAY, 25, false, vm);
}

void display_buletooth_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_BLUETOOTH_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA1].valid)) return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_status_logo(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_power_off_timer_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_POWER_OFF_TIMER_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA1].valid)) return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_status_logo(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_trumpet_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_TRUMPET_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA2].valid)) return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_status_logo(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_lighting_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_LIGHTING_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA2].valid)) return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_status_logo(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_real_time_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_REAL_TIME_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA1].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, GRAY, vm);
    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, _area_idx, get_real_time(), TEMP_CONTENT, WHITE, UNSELECT, vm);
}

void display_area2_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_TFT_AREA2;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA2].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void display_measure_mode_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_VALUE_MODE_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA3].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (true == 1)
        display_mark_content(_Area[_area_idx].set_y, _Area[_area_idx].set_x, MANUAL_ALIGN, LAYOUT_R11, _area_idx, "MAX", TEMP_CONTENT, WHITE, UNSELECT, vm);
    else if (true == 2)
        display_mark_content(_Area[_area_idx].set_y, _Area[_area_idx].set_x, MANUAL_ALIGN, LAYOUT_R11, _area_idx, "MIN", TEMP_CONTENT, WHITE, UNSELECT, vm);
    else if (true == 3)
        display_mark_content(_Area[_area_idx].set_y, _Area[_area_idx].set_x, MANUAL_ALIGN, LAYOUT_R11, _area_idx, "AVG", TEMP_CONTENT, WHITE, UNSELECT, vm);
}

void display_recording_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_RECORDING_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA2].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_recording_mark(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, WHITE, RED, 1, vm);
}

void display_hold_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_HOLD_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA2].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (true)
        display_hold_mark(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, WHITE, RED, 1, vm);
}

void display_relative_value_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_RELATIVE_VALUE_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA2].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (true) {
        display_hollow_triangle(_Area[_area_idx].set_y + 2, _Area[_area_idx].set_x - 16, 16, 16, WHITE, vm);
        display_hollow_triangle(_Area[_area_idx].set_y + 3, _Area[_area_idx].set_x - 16 + 1, 14, 14, WHITE, vm);
        display_measure_value_unit_content(0, 0, RIGHT_ALIGN, LAYOUT_R11, _area_idx, "-225.66mV", TEMP_CONTENT, WHITE, UNSELECT, vm);
        // display_measure_value_unit_content(_Area[_area_idx].set_y, _Area[_area_idx].set_x + _Area[_area_idx].width, MANUAL_ALIGN, LAYOUT_R11, _area_idx, "V", TEMP_CONTENT, WHITE, UNSELECT, vm);
    }
}

void display_area3_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_TFT_AREA3;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA3].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void display_measure_value_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_VALUE_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA3].valid)) return;

    static float measure_value = 225.55;
    uint8_t measure_string[8];
    static uint8_t speed;

    if (speed % 10 == 0) {
        if (measure_value < 255.55) measure_value += 1;
        else measure_value = 0.55;
    }
    speed++;
    sprintf(measure_string, "%06.2f", measure_value);

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_measure_value_content(86, 0, RIGHT_ALIGN, LAYOUT_R11, _area_idx, measure_string, TEMP_CONTENT, WHITE, UNSELECT, vm);

    display_tips(26, 0, 320, WHITE, DARK_BLUE, FONT_N2_PT, &message_tips[0], vm);
    tips_timing(&message_tips[0]);
}

void display_measure_value_unit_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_VALUE_UNIT_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA3].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    display_status_logo(_Area[_area_idx].set_y - 10, _Area[_area_idx].set_x + 24, WHITE, BLACK, DC_DESC, 1, vm);
    display_measure_value_unit_content(_Area[_area_idx].set_y, _Area[_area_idx].set_x, RIGHT_ALIGN, LAYOUT_R11, _area_idx, "mV", TEMP_CONTENT, WHITE, UNSELECT, vm);
}

void display_area4_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_TFT_AREA4;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA4].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void display_measure_lo_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_LO_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA4].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (true)
        display_status_logo(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, BLACK, LO, 1, vm);
}

void display_measure_loz_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_LOZ_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA4].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
    if (true)
        display_status_logo(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, BLACK, LOZ, 1, vm);
}

void display_measure_ruler_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_RULER_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA4].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height + 15, BLACK, vm);
    if (true) {
        // display_ruler(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, BLACK, i, 0, 1, 1, vm);
        display_ruler_percent_mode(_Area[_area_idx].set_y, _Area[_area_idx].set_x, WHITE, BLACK, 60, 600, vm);
    }
}

void display_range_status_show(uint8_t * vm)
{
    uint16_t _area_idx = MEASURE_RANGE_STATUS_AREA;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA3].valid)) return;

    if (false) {
        display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
        display_widget_content(_Area[_area_idx].set_y, _Area[_area_idx].set_x, MANUAL_ALIGN, LAYOUT_R11, _area_idx, "AUTO", TEMP_CONTENT, WHITE, UNSELECT, vm);
    }
}

void display_area5_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_TFT_AREA5;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void display_f1_menubar_area_show(uint8_t * vm)
{
    uint16_t _area_idx = F1_MENUBAR_AREA;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    // display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, vm);
    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    // display f1 menu content
    display_menubar_content(F1_KEY_EVT, vm);
}

void display_f2_menubar_area_show(uint8_t * vm)
{
    uint16_t _area_idx = F2_MENUBAR_AREA;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    // display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, vm);
    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    // display f2 menu content
    display_menubar_content(F2_KEY_EVT, vm);
}

void display_f3_menubar_area_show(uint8_t * vm)
{
    uint16_t _area_idx = F3_MENUBAR_AREA;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    // display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, vm);
    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    // display f3 menu content
    display_menubar_content(F3_KEY_EVT, vm);
}

void display_f4_menubar_area_show(uint8_t * vm)
{
    uint16_t _area_idx = F4_MENUBAR_AREA;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = GRAY;

    // display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, vm);
    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    // display f4 menu content
    display_menubar_content(F4_KEY_EVT, vm);
}

void display_prev_menubar_area_show(uint8_t * vm)
{
    uint16_t _area_idx = PREV_MENUBAR_AREA;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = RED;

    if ((read_menubar_page() == 1)/* || (!_Area[_area_idx].valid)*/) color = GRAY;

    // display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, vm);
    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    // display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, _area_idx, "<", TEMP_CONTENT, WHITE, UNSELECT, vm);
    display_menubar_content(PREV_KEY_EVT, vm);
}

void display_next_menubar_area_show(uint8_t * vm)
{
    uint16_t _area_idx = NEXT_MENUBAR_AREA;
    uint8_t color;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    if (_Area[_area_idx].pressed) color = DARK_GREEN;
    else color = RED;

    if ((read_menubar_page() == 2)/* || (!_Area[_area_idx].valid)*/) color = GRAY;

    // display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, vm);
    display_bevel_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, color, 1, vm);
    // display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, _area_idx, ">", TEMP_CONTENT, WHITE, UNSELECT, vm);
    display_menubar_content(NEXT_KEY_EVT, vm);
}

void display_setting_area2_show(uint8_t * vm)
{
    uint16_t _area_idx = DISPLAY_SETTING_AREA2;

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    display_solid_rect(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, BLACK, vm);
}

void display_setting_list_show(uint8_t * vm)
{
    uint16_t _area_idx = SETTING_LIST_AREA;

    #define LINE_GAP     5
    #define LIST_LINE0_Y (_Area[_area_idx].set_y + LINE_GAP * 0 + _Area[_area_idx].height * 0)
    #define LIST_LINE1_Y (_Area[_area_idx].set_y + LINE_GAP * 1 + _Area[_area_idx].height * 1)
    #define LIST_LINE2_Y (_Area[_area_idx].set_y + LINE_GAP * 2 + _Area[_area_idx].height * 2)
    #define LIST_LINE3_Y (_Area[_area_idx].set_y + LINE_GAP * 3 + _Area[_area_idx].height * 3)
    #define LIST_LINE4_Y (_Area[_area_idx].set_y + LINE_GAP * 4 + _Area[_area_idx].height * 4)
    #define LIST_LINE5_Y (_Area[_area_idx].set_y + LINE_GAP * 5 + _Area[_area_idx].height * 5)
    #define LIST_LINE6_Y (_Area[_area_idx].set_y + LINE_GAP * 6 + _Area[_area_idx].height * 6)
    #define LIST_LINE7_Y (_Area[_area_idx].set_y + LINE_GAP * 7 + _Area[_area_idx].height * 7)

    if ((!_Area[_area_idx].refer) || (!_Area[DISPLAY_TFT_AREA5].valid)) return;

    display_setting_dock(_Area[_area_idx].set_y, _Area[_area_idx].set_x, _Area[_area_idx].width, _Area[_area_idx].height, RED, GRAY, 8, LINE_GAP, get_vpos_selected(), vm);

    uint8_t list_item_color[8];
    uint8_t selected[3];

    memset(list_item_color, WHITE, 8);
    list_item_color[get_vpos_selected()] = WHITE;
    // list items's name
    if (get_page_selected() == 0) {
        display_bookmark(LIST_LINE7_Y, _Area[_area_idx].set_x + 282, 34, 16, RED, 8, vm);
        display_mark_content(LIST_LINE7_Y + 1, _Area[_area_idx].set_x + 284, MANUAL_ALIGN, LAYOUT_R11, 0, list_content[LIST_1_2],         TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_SET_TIME],    TEMP_CONTENT, list_item_color[0], UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_SET_DATE],    TEMP_CONTENT, list_item_color[1], UNSELECT, vm);
        display_mark_content(LIST_LINE2_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_AUTO_SHTDWN], TEMP_CONTENT, list_item_color[2], UNSELECT, vm);
        display_mark_content(LIST_LINE3_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_MAX], TEMP_CONTENT, list_item_color[3], UNSELECT, vm);
        display_mark_content(LIST_LINE4_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_MIN], TEMP_CONTENT, list_item_color[4], UNSELECT, vm);
        display_mark_content(LIST_LINE5_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_TYPE],TEMP_CONTENT, list_item_color[5], UNSELECT, vm);
        display_mark_content(LIST_LINE6_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_RECORD_RATE], TEMP_CONTENT, list_item_color[6], UNSELECT, vm);
        display_mark_content(LIST_LINE7_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_MEMORY_MODE], TEMP_CONTENT, list_item_color[7], UNSELECT, vm);

        if (get_param_number() == 0) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_hour(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 20, MANUAL_ALIGN, LAYOUT_R11, 0, ":", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 28, MANUAL_ALIGN, LAYOUT_R11, 0, get_minute(), TEMP_CONTENT, WHITE, selected[1], vm);
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 48, MANUAL_ALIGN, LAYOUT_R11, 0, ":", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 56, MANUAL_ALIGN, LAYOUT_R11, 0, get_second(), TEMP_CONTENT, WHITE, selected[2], vm);

        if (get_param_number() == 1) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_year(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 40, MANUAL_ALIGN, LAYOUT_R11, 0, "-", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 48, MANUAL_ALIGN, LAYOUT_R11, 0, get_month(), TEMP_CONTENT, WHITE, selected[1], vm);
        display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 68, MANUAL_ALIGN, LAYOUT_R11, 0, "-", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 76, MANUAL_ALIGN, LAYOUT_R11, 0, get_day(), TEMP_CONTENT, WHITE, selected[2], vm);

        if (get_param_number() == 2) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);

        switch (get_apo_time()) {
        case 0:
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "Off", TEMP_CONTENT, WHITE, selected[0], vm);
            break;
        case 1:
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "15", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 2:
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "30", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 3:
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "60", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 4:
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "120", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 5:
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "180", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        }

        if (get_param_number() == 3) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (selected[0]) {
            read_display_part_string(SETUP_COMP_MAX);
            display_main_measure_data_unit_content_selected_digit(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35, MANUAL_ALIGN, LAYOUT_R11, 0, value_regulator.display_buf[1], TEMP_CONTENT, WHITE, UNSELECT, read_cursor_position(), vm);
        } else {
            display_mark_content(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_comp_max(), TEMP_CONTENT, WHITE, selected[0], vm);
        }

        if (get_param_number() == 4) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (selected[0]) {
            read_display_part_string(SETUP_COMP_MIN);
            display_main_measure_data_unit_content_selected_digit(LIST_LINE4_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35, MANUAL_ALIGN, LAYOUT_R11, 0, value_regulator.display_buf[1], TEMP_CONTENT, WHITE, UNSELECT, read_cursor_position(), vm);
        } else {
            display_mark_content(LIST_LINE4_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_comp_min(), TEMP_CONTENT, WHITE, selected[0], vm);
        }

        if (get_param_number() == 5) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (get_comp_type() == 0)
            display_mark_content(LIST_LINE5_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "INNER", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE5_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OUTER", TEMP_CONTENT, WHITE, selected[0], vm);

        if (get_param_number() == 6) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        display_mark_content(LIST_LINE6_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_record_rate(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE6_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 17, MANUAL_ALIGN, LAYOUT_R11, 0, "s", TEMP_CONTENT, WHITE, UNSELECT, vm);

        if (get_param_number() == 7) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (get_memory_mode() == 0)
            display_mark_content(LIST_LINE7_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "FIX", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE7_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "COVER", TEMP_CONTENT, WHITE, selected[0], vm);
    }

    if (get_page_selected() == 1) {
        display_bookmark(LIST_LINE7_Y, _Area[_area_idx].set_x + 282, 34, 16, RED, 8, vm);
        display_mark_content(LIST_LINE7_Y + 1, _Area[_area_idx].set_x + 284, MANUAL_ALIGN, LAYOUT_R11, 0, list_content[LIST_2_2],            TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_BACK_LIGHT],     TEMP_CONTENT, list_item_color[0], UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_BACK_LIGHT_TIME],TEMP_CONTENT, list_item_color[1], UNSELECT, vm);
        display_mark_content(LIST_LINE2_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_SOUND],          TEMP_CONTENT, list_item_color[2], UNSELECT, vm);
        display_mark_content(LIST_LINE3_Y + 1, _Area[_area_idx].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_COLOR],          TEMP_CONTENT, list_item_color[3], UNSELECT, vm);

        if (get_param_number() == 8) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_back_light(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE0_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 26, MANUAL_ALIGN, LAYOUT_R11, 0, "%", TEMP_CONTENT, WHITE, UNSELECT, vm);

        if (get_param_number() == 9) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);

        switch (get_light_time()) {
        case 0:
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OFF", TEMP_CONTENT, WHITE, selected[0], vm);
            break;
        case 1:
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "15", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 2:
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "30", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 3:
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "60", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 4:
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "120", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        }

        if (get_param_number() == 10) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        
        if (get_sound_status())
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "ON", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE2_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OFF", TEMP_CONTENT, WHITE, selected[0], vm);
    
        if (get_param_number() == 11) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        
        if (get_theme_color())
            display_mark_content(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "LIGHT", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE3_Y, _Area[_area_idx].set_x + _Area[_area_idx].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "DARK", TEMP_CONTENT, WHITE, selected[0], vm);
    }
}
