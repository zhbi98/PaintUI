
#include "display_show.h"

struct status_logo_pool_t logo_pool = {
    .phead = 0,
    .ptail = 0,
};

unsigned char get_buletooth_status()
{
    return true;
}

unsigned char get_lighting_status()
{
    return true;
}

void get_status_logo_active()
{
    if (get_buletooth_status())
        status_logo_input_pool(&logo_pool, BLUETOOTH, true);

    if (get_apo_time())
        status_logo_input_pool(&logo_pool, POWEROFF_TIMER, true);

    if (get_sound_status())
        status_logo_input_pool(&logo_pool, TRUMPET, true);

    if (get_lighting_status())
        status_logo_input_pool(&logo_pool, LIGHTING, true);
}

void display_area1_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_TFT_AREA1;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA1].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, GRAY, vm);
    get_status_logo_active();
}

void display_battery_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_BATTERY_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA1].show))
        return;

    // power 0% - 100%
    display_battery(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, WHITE, GRAY, 25, false, vm);
}

void display_buletooth_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_BLUETOOTH_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA1].show))
        return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, GRAY, vm);
    display_status_logo(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_power_off_timer_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_POWER_OFF_TIMER_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA1].show))
        return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, GRAY, vm);
    display_status_logo(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_trumpet_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_TRUMPET_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA2].show))
        return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_status_logo(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_lighting_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_LIGHTING_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA2].show))
        return;

    struct status_logo_t logo;
    if (status_logo_output_pool(&logo_pool, &logo) == false)
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, GRAY, vm);
    display_status_logo(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, GRAY, logo.name, logo.status, vm);
}

void display_real_time_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_REAL_TIME_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA1].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, GRAY, vm);
    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, widget_num, get_real_time(), TEMP_CONTENT, WHITE, UNSELECT, vm);
}

void display_area2_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_TFT_AREA2;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA2].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
}

void display_measure_mode_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_VALUE_MODE_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA3].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    if (true == 1)
        display_mark_content(widget[widget_num].set_y, widget[widget_num].set_x, MANUAL_ALIGN, LAYOUT_R11, widget_num, "MAX", TEMP_CONTENT, WHITE, UNSELECT, vm);
    else if (true == 2)
        display_mark_content(widget[widget_num].set_y, widget[widget_num].set_x, MANUAL_ALIGN, LAYOUT_R11, widget_num, "MIN", TEMP_CONTENT, WHITE, UNSELECT, vm);
    else if (true == 3)
        display_mark_content(widget[widget_num].set_y, widget[widget_num].set_x, MANUAL_ALIGN, LAYOUT_R11, widget_num, "AVG", TEMP_CONTENT, WHITE, UNSELECT, vm);
}

void display_recording_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_RECORDING_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA2].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    display_recording_mark(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, WHITE, RED, 1, vm);
}

void display_hold_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_HOLD_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA2].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    if (true)
        display_hold_mark(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, WHITE, RED, 1, vm);
}

void display_relative_value_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_RELATIVE_VALUE_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA2].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    if (true) {
        display_hollow_triangle(widget[widget_num].set_y + 2, widget[widget_num].set_x - 16, 16, 16, WHITE, vm);
        display_hollow_triangle(widget[widget_num].set_y + 3, widget[widget_num].set_x - 16 + 1, 14, 14, WHITE, vm);
        display_measure_value_unit_content(0, 0, RIGHT_ALIGN, LAYOUT_R11, widget_num, "-225.66mV", TEMP_CONTENT, WHITE, UNSELECT, vm);
        // display_measure_value_unit_content(widget[widget_num].set_y, widget[widget_num].set_x + widget[widget_num].width, MANUAL_ALIGN, LAYOUT_R11, widget_num, "V", TEMP_CONTENT, WHITE, UNSELECT, vm);
    }
}

void display_area3_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_TFT_AREA3;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA3].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
}

void display_measure_value_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_VALUE_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA3].show))
        return;

    static float measure_value = 225.55;
    unsigned char measure_string[8];
    static unsigned char speed;

    if (speed % 10 == 0) {
        if (measure_value < 255.55)
            measure_value += 1;
        else
            measure_value = 0.55;
    }
    speed++;
    sprintf(measure_string, "%06.2f", measure_value);

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    display_measure_value_content_dmm(86, 0, RIGHT_ALIGN, LAYOUT_R11, widget_num, measure_string, TEMP_CONTENT, WHITE, UNSELECT, vm);

    display_tips(26, 0, 320, WHITE, DARK_BLUE, FONT_14X14, &message_tips[0], vm);
    tips_timing(&message_tips[0]);
}

void display_measure_value_unit_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_VALUE_UNIT_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA3].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    display_status_logo(widget[widget_num].set_y - 10, widget[widget_num].set_x + 24, WHITE, BLACK, DC_DESC, 1, vm);
    display_measure_value_unit_content(widget[widget_num].set_y, widget[widget_num].set_x, RIGHT_ALIGN, LAYOUT_R11, widget_num, "mV", TEMP_CONTENT, WHITE, UNSELECT, vm);
}

void display_area4_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_TFT_AREA4;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA4].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
}

void display_measure_lo_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_LO_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA4].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    if (true)
        display_status_logo(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, BLACK, LO, 1, vm);
}

void display_measure_loz_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_LOZ_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA4].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
    if (true)
        display_status_logo(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, BLACK, LOZ, 1, vm);
}

void display_measure_ruler_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_RULER_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA4].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height + 15, BLACK, vm);
    if (true) {
        // display_ruler(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, BLACK, i, 0, 1, 1, vm);
        display_ruler_percent_mode(widget[widget_num].set_y, widget[widget_num].set_x, WHITE, BLACK, 60, 600, vm);
    }
}

void display_range_status_show(unsigned char * vm)
{
    unsigned int widget_num = MEASURE_RANGE_STATUS_AREA;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA3].show))
        return;

    if (false) {
        display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
        display_widget_content(widget[widget_num].set_y, widget[widget_num].set_x, MANUAL_ALIGN, LAYOUT_R11, widget_num, "AUTO", TEMP_CONTENT, WHITE, UNSELECT, vm);
    }
}

void display_area5_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_TFT_AREA5;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
}

void display_f1_menubar_area_show(unsigned char * vm)
{
    unsigned int widget_num = F1_MENUBAR_AREA;
    unsigned char color;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    if (widget[widget_num].pressed)
        color = DARK_GREEN;
    else
        color = GRAY;

    // display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, vm);
    display_bevel_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, 1, vm);
    // display f1 menu content
    display_menubar_content(F1_KEY_EVT, vm);
}

void display_f2_menubar_area_show(unsigned char * vm)
{
    unsigned int widget_num = F2_MENUBAR_AREA;
    unsigned char color;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    if (widget[widget_num].pressed)
        color = DARK_GREEN;
    else
        color = GRAY;

    // display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, vm);
    display_bevel_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, 1, vm);
    // display f2 menu content
    display_menubar_content(F2_KEY_EVT, vm);
}

void display_f3_menubar_area_show(unsigned char * vm)
{
    unsigned int widget_num = F3_MENUBAR_AREA;
    unsigned char color;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    if (widget[widget_num].pressed)
        color = DARK_GREEN;
    else
        color = GRAY;

    // display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, vm);
    display_bevel_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, 1, vm);
    // display f3 menu content
    display_menubar_content(F3_KEY_EVT, vm);
}

void display_f4_menubar_area_show(unsigned char * vm)
{
    unsigned int widget_num = F4_MENUBAR_AREA;
    unsigned char color;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    if (widget[widget_num].pressed)
        color = DARK_GREEN;
    else
        color = GRAY;

    // display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, vm);
    display_bevel_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, 1, vm);
    // display f4 menu content
    display_menubar_content(F4_KEY_EVT, vm);
}

void display_prev_menubar_area_show(unsigned char * vm)
{
    unsigned int widget_num = PREV_MENUBAR_AREA;
    unsigned char color;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    if (widget[widget_num].pressed)
        color = DARK_GREEN;
    else
        color = RED;

    if ((read_menubar_page() == 1)/* || (!widget[widget_num].show)*/)
        color = GRAY;

    // display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, vm);
    display_bevel_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, 1, vm);
    // display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, widget_num, "<", TEMP_CONTENT, WHITE, UNSELECT, vm);
    display_menubar_content(PREV_KEY_EVT, vm);
}

void display_next_menubar_area_show(unsigned char * vm)
{
    unsigned int widget_num = NEXT_MENUBAR_AREA;
    unsigned char color;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    if (widget[widget_num].pressed)
        color = DARK_GREEN;
    else
        color = RED;

    if ((read_menubar_page() == 2)/* || (!widget[widget_num].show)*/)
        color = GRAY;

    // display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, vm);
    display_bevel_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, color, 1, vm);
    // display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, widget_num, ">", TEMP_CONTENT, WHITE, UNSELECT, vm);
    display_menubar_content(NEXT_KEY_EVT, vm);
}

void display_setting_area2_show(unsigned char * vm)
{
    unsigned int widget_num = DISPLAY_SETTING_AREA2;

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    display_solid_rect(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, BLACK, vm);
}

void display_setting_list_show(unsigned char * vm)
{
    unsigned int widget_num = SETTING_LIST_AREA;

    #define LINE_GAP     5
    #define LIST_LINE0_Y (widget[widget_num].set_y + LINE_GAP * 0 + widget[widget_num].height * 0)
    #define LIST_LINE1_Y (widget[widget_num].set_y + LINE_GAP * 1 + widget[widget_num].height * 1)
    #define LIST_LINE2_Y (widget[widget_num].set_y + LINE_GAP * 2 + widget[widget_num].height * 2)
    #define LIST_LINE3_Y (widget[widget_num].set_y + LINE_GAP * 3 + widget[widget_num].height * 3)
    #define LIST_LINE4_Y (widget[widget_num].set_y + LINE_GAP * 4 + widget[widget_num].height * 4)
    #define LIST_LINE5_Y (widget[widget_num].set_y + LINE_GAP * 5 + widget[widget_num].height * 5)
    #define LIST_LINE6_Y (widget[widget_num].set_y + LINE_GAP * 6 + widget[widget_num].height * 6)
    #define LIST_LINE7_Y (widget[widget_num].set_y + LINE_GAP * 7 + widget[widget_num].height * 7)

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    display_setting_dock(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, RED, GRAY, 8, LINE_GAP, get_vpos_selected(), vm);

    unsigned char list_item_color[8];
    unsigned char selected[3];

    memset(list_item_color, WHITE, 8);
    list_item_color[get_vpos_selected()] = WHITE;
    // list items's name
    if (get_page_selected() == 0) {
        display_bookmark(LIST_LINE7_Y, widget[widget_num].set_x + 282, 34, 16, RED, 8, vm);
        display_mark_content(LIST_LINE7_Y + 1, widget[widget_num].set_x + 284, MANUAL_ALIGN, LAYOUT_R11, 0, list_content[LIST_1_2],         TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_SET_TIME],    TEMP_CONTENT, list_item_color[0], UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_SET_DATE],    TEMP_CONTENT, list_item_color[1], UNSELECT, vm);
        display_mark_content(LIST_LINE2_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_AUTO_SHTDWN], TEMP_CONTENT, list_item_color[2], UNSELECT, vm);
        display_mark_content(LIST_LINE3_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_MAX], TEMP_CONTENT, list_item_color[3], UNSELECT, vm);
        display_mark_content(LIST_LINE4_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_MIN], TEMP_CONTENT, list_item_color[4], UNSELECT, vm);
        display_mark_content(LIST_LINE5_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_COMPARE_TYPE],TEMP_CONTENT, list_item_color[5], UNSELECT, vm);
        display_mark_content(LIST_LINE6_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_RECORD_RATE], TEMP_CONTENT, list_item_color[6], UNSELECT, vm);
        display_mark_content(LIST_LINE7_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11,  0, list_content[LIST_MEMORY_MODE], TEMP_CONTENT, list_item_color[7], UNSELECT, vm);

        if (get_param_number() == 0) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_hour(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 20, MANUAL_ALIGN, LAYOUT_R11, 0, ":", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 28, MANUAL_ALIGN, LAYOUT_R11, 0, get_minute(), TEMP_CONTENT, WHITE, selected[1], vm);
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 48, MANUAL_ALIGN, LAYOUT_R11, 0, ":", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 56, MANUAL_ALIGN, LAYOUT_R11, 0, get_second(), TEMP_CONTENT, WHITE, selected[2], vm);

        if (get_param_number() == 1) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_year(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 40, MANUAL_ALIGN, LAYOUT_R11, 0, "-", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 48, MANUAL_ALIGN, LAYOUT_R11, 0, get_month(), TEMP_CONTENT, WHITE, selected[1], vm);
        display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 68, MANUAL_ALIGN, LAYOUT_R11, 0, "-", TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 76, MANUAL_ALIGN, LAYOUT_R11, 0, get_day(), TEMP_CONTENT, WHITE, selected[2], vm);

        if (get_param_number() == 2) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);

        switch (get_apo_time()) {
        case 0:
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "Off", TEMP_CONTENT, WHITE, selected[0], vm);
            break;
        case 1:
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "15", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 2:
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "30", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 3:
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "60", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 4:
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "120", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 5:
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "180", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        }

        if (get_param_number() == 3) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (selected[0]) {
            read_display_part_string(SETUP_COMP_MAX);
            display_main_measure_data_unit_content_selected_digit(LIST_LINE3_Y, widget[widget_num].set_x + widget[widget_num].width + 35, MANUAL_ALIGN, LAYOUT_R11, 0, value_regulator.display_buf[1], TEMP_CONTENT, WHITE, UNSELECT, read_cursor_position(), vm);
        } else {
            display_mark_content(LIST_LINE3_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_comp_max(), TEMP_CONTENT, WHITE, selected[0], vm);
        }

        if (get_param_number() == 4) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (selected[0]) {
            read_display_part_string(SETUP_COMP_MIN);
            display_main_measure_data_unit_content_selected_digit(LIST_LINE4_Y, widget[widget_num].set_x + widget[widget_num].width + 35, MANUAL_ALIGN, LAYOUT_R11, 0, value_regulator.display_buf[1], TEMP_CONTENT, WHITE, UNSELECT, read_cursor_position(), vm);
        } else {
            display_mark_content(LIST_LINE4_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_comp_min(), TEMP_CONTENT, WHITE, selected[0], vm);
        }

        if (get_param_number() == 5) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (get_comp_type() == 0)
            display_mark_content(LIST_LINE5_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "INNER", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE5_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OUTER", TEMP_CONTENT, WHITE, selected[0], vm);

        if (get_param_number() == 6) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        display_mark_content(LIST_LINE6_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_record_rate(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE6_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 17, MANUAL_ALIGN, LAYOUT_R11, 0, "s", TEMP_CONTENT, WHITE, UNSELECT, vm);

        if (get_param_number() == 7) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        if (get_memory_mode() == 0)
            display_mark_content(LIST_LINE7_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "FIX", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE7_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "COVER", TEMP_CONTENT, WHITE, selected[0], vm);
    }

    if (get_page_selected() == 1) {
        display_bookmark(LIST_LINE7_Y, widget[widget_num].set_x + 282, 34, 16, RED, 8, vm);
        display_mark_content(LIST_LINE7_Y + 1, widget[widget_num].set_x + 284, MANUAL_ALIGN, LAYOUT_R11, 0, list_content[LIST_2_2],            TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(LIST_LINE0_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_BACK_LIGHT],     TEMP_CONTENT, list_item_color[0], UNSELECT, vm);
        display_mark_content(LIST_LINE1_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_BACK_LIGHT_TIME],TEMP_CONTENT, list_item_color[1], UNSELECT, vm);
        display_mark_content(LIST_LINE2_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_SOUND],          TEMP_CONTENT, list_item_color[2], UNSELECT, vm);
        display_mark_content(LIST_LINE3_Y + 1, widget[widget_num].set_x + 18, MANUAL_ALIGN, LAYOUT_R11, 0,  list_content[LIST_COLOR],          TEMP_CONTENT, list_item_color[3], UNSELECT, vm);

        if (get_param_number() == 8) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, get_back_light(), TEMP_CONTENT, WHITE, selected[0], vm);
        display_mark_content(LIST_LINE0_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 26, MANUAL_ALIGN, LAYOUT_R11, 0, "%", TEMP_CONTENT, WHITE, UNSELECT, vm);

        if (get_param_number() == 9) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);

        switch (get_light_time()) {
        case 0:
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OFF", TEMP_CONTENT, WHITE, selected[0], vm);
            break;
        case 1:
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "15", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 2:
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "30", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 3:
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "60", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        case 4:
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "120", TEMP_CONTENT, WHITE, selected[0], vm);
            display_mark_content(LIST_LINE1_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 30, MANUAL_ALIGN, LAYOUT_R11, 0, "minute", TEMP_CONTENT, WHITE, UNSELECT, vm);
            break;
        }

        if (get_param_number() == 10) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        
        if (get_sound_status())
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "ON", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE2_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "OFF", TEMP_CONTENT, WHITE, selected[0], vm);
    
        if (get_param_number() == 11) {
            memset(selected, UNSELECT, 3);
            selected[get_hpos_selected()] = SELECTED;
        } else
            memset(selected, UNSELECT, 3);
        
        if (get_theme_color())
            display_mark_content(LIST_LINE3_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "LIGHT", TEMP_CONTENT, WHITE, selected[0], vm);
        else
            display_mark_content(LIST_LINE3_Y, widget[widget_num].set_x + widget[widget_num].width + 35 + 0, MANUAL_ALIGN, LAYOUT_R11, 0, "DARK", TEMP_CONTENT, WHITE, selected[0], vm);
    }
}

/*
struct set_item_t {
    unsigned char order_number;
    unsigned char * title;
    unsigned char param_number;
};

struct set_list_t {
    unsigned char start_pos;
    unsigned char end_pos;
    unsigned char current_pos;
    char cur_pos;
    // number of dock
    const unsigned char dock_number;
    // number of content entries required to be displayed
    const unsigned char content_number;
};

const struct set_item_t set_item[] = {
    {
        .order_number = 0,
        .title = "0:SET TIME",
        .param_number = 3,
    },

    {
        .order_number = 1,
        .title = "1:SET DATE",
        .param_number = 3,
    },

    {
        .order_number = 2,
        .title = "2:APO TIME",
        .param_number = 1,
    },

    {
        .order_number = 3,
        .title = "3:COMP TYPE",
        .param_number = 1,
    },

    {
        .order_number = 4,
        .title = "4:RECORD RATE",
        .param_number = 1,
    },

    {
        .order_number = 5,
        .title = "5:MEMORY MODE",
        .param_number = 1,
    },

    {
        .order_number = 6,
        .title = "6:BACK LIGHT",
        .param_number = 1,
    },

    {
        .order_number = 7,
        .title = "7:LIST TEST",
        .param_number = 1,
    },

    {
        .order_number = 8,
        .title = "8:LIST TEST",
        .param_number = 1,
    },
};

struct set_list_t set_list = {
    .start_pos      = 0,
    .end_pos        = 7,
    .current_pos    = 0,
    .cur_pos        = 0,
    .dock_number    = 8,
    .content_number = 9,
};

void display_setting_list_show(unsigned char * vm)
{
    unsigned int widget_num = SETTING_ITEMS_LIST_AREA;
    unsigned char list_name_y = 0;
    unsigned char array_y[] = {LIST_LINE0_Y, LIST_LINE1_Y, LIST_LINE2_Y, LIST_LINE3_Y, LIST_LINE4_Y, LIST_LINE5_Y, LIST_LINE6_Y, LIST_LINE7_Y};

    if (((!widget[widget_num].renew) && (!widget[widget_num].auto_renew)) || (!widget[DISPLAY_TFT_AREA5].show))
        return;

    // display dock
    display_setting_dock(widget[widget_num].set_y, widget[widget_num].set_x, widget[widget_num].width, widget[widget_num].height, RED, GRAY, 8, LINE_GAP, set_list.cur_pos, vm);
    // display scroll bar
    unsigned char scroll_bar_length = (set_list.dock_number * 22) * (set_list.dock_number * 22) / (set_list.content_number * 22);
    display_solid_rect(LIST_LINE0_Y + set_list.current_pos * (set_list.dock_number * 22 - scroll_bar_length) / set_list.content_number, 163, 2, scroll_bar_length, WHITE, vm);

    // display list content
    for (unsigned char index = set_list.start_pos; index <= set_list.end_pos; index++) {
        display_mark_content(array_y[list_name_y] + 1, widget[widget_num].set_x + 12,  MANUAL_ALIGN, LAYOUT_R11,  0, set_item[index].title, TEMP_CONTENT, WHITE, UNSELECT, vm);
        display_mark_content(array_y[list_name_y] + 1, widget[widget_num].set_x + 100,  MANUAL_ALIGN, LAYOUT_R11,  0, *get_function[list_name_y](), TEMP_CONTENT, WHITE, UNSELECT, vm);
        list_name_y++;
    }
}

void vpos_selected(char incr)
{
    set_list.cur_pos += incr;

    if (set_list.cur_pos > set_list.dock_number - 1) {
        set_list.cur_pos = set_list.dock_number - 1;

        if (set_list.end_pos < (set_list.content_number - 1)) {
            set_list.start_pos++;
            set_list.end_pos++;
        }
    }

    if (set_list.cur_pos < 0) {
        set_list.cur_pos = 0;

        if (set_list.start_pos > 0) {
            set_list.start_pos--;
            set_list.end_pos--;
        }
    }

    set_list.current_pos = set_list.start_pos + set_list.cur_pos;
    info("current_pos:%d", set_list.current_pos);
    // info("start_pos:%d", set_list.start_pos);
    // info("cur_pos:%d", set_list.cur_pos);
}

unsigned char get_vpos_selected()
{
    return set_list.current_pos;
}
*/
