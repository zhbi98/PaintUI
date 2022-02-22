
#include "display_controller.h"

struct module_t widget[WIDGET_NUM_MAX];
struct menubar_t menubar;

const key_event_interface * key_event_controller[FUNCTION_TYPE_MAX][MENUBAR_LEVEL_MAX] = {
    {voltage_level1_key_event,           0},
    {setting_level1_key_event,           0},
};

const key_event_interface * key_event_enable[FUNCTION_TYPE_MAX][MENUBAR_LEVEL_MAX] = {
    {voltage_level1_key_event_enable,    0},
    {setting_level1_key_event_enable,    0},
};

const menu_content_interface * display_menu_content[FUNCTION_TYPE_MAX][MENUBAR_LEVEL_MAX] = {
    {voltage_level1_menu,                0},
    {setting_level1_menu,                0},
};

const display_show_interface * display_widget_show[] = {
    display_area1_show,
    display_area2_show,
    display_area3_show,
    display_area4_show,
    display_area5_show,
    display_setting_area2_show,

    display_battery_show,
    display_buletooth_show,
    display_power_off_timer_show,
    display_trumpet_show,
    display_lighting_show,
    display_real_time_show,

    display_measure_mode_show,
    display_recording_show,
    display_hold_show,
    display_relative_value_show,

    display_measure_value_show,
    display_measure_value_unit_show,

    display_measure_lo_show,
    display_measure_loz_show,
    display_measure_ruler_show,
    display_range_status_show,

    display_f1_menubar_area_show,
    display_f2_menubar_area_show,
    display_f3_menubar_area_show,
    display_f4_menubar_area_show,
    display_prev_menubar_area_show,
    display_next_menubar_area_show,

    display_setting_list_show,
};

void widget_size_init()
{
    widget[DISPLAY_TFT_AREA1].set_y             = 0;
    widget[DISPLAY_TFT_AREA1].set_x             = 0;
    widget[DISPLAY_TFT_AREA1].width             = 320;
    widget[DISPLAY_TFT_AREA1].height            = 24;
    widget[DISPLAY_TFT_AREA1].show              = true;
    widget[DISPLAY_TFT_AREA1].renew             = true;
    
    widget[DISPLAY_TFT_AREA2].set_y             = 24;
    widget[DISPLAY_TFT_AREA2].set_x             = 0;
    widget[DISPLAY_TFT_AREA2].width             = 320;
    widget[DISPLAY_TFT_AREA2].height            = 54;
    widget[DISPLAY_TFT_AREA2].show              = true;
    widget[DISPLAY_TFT_AREA2].renew             = true;
    
    widget[DISPLAY_TFT_AREA3].set_y             = 78;
    widget[DISPLAY_TFT_AREA3].set_x             = 0;
    widget[DISPLAY_TFT_AREA3].width             = 320;
    widget[DISPLAY_TFT_AREA3].height            = 84;
    widget[DISPLAY_TFT_AREA3].show              = true;
    widget[DISPLAY_TFT_AREA3].renew             = true;
    
    widget[DISPLAY_TFT_AREA4].set_y             = 162;
    widget[DISPLAY_TFT_AREA4].set_x             = 0;
    widget[DISPLAY_TFT_AREA4].width             = 320;
    widget[DISPLAY_TFT_AREA4].height            = 53;
    widget[DISPLAY_TFT_AREA4].show              = true;
    widget[DISPLAY_TFT_AREA4].renew             = true;
    
    widget[DISPLAY_TFT_AREA5].set_y             = 215;
    widget[DISPLAY_TFT_AREA5].set_x             = 0;
    widget[DISPLAY_TFT_AREA5].width             = 320;
    widget[DISPLAY_TFT_AREA5].height            = 24;
    widget[DISPLAY_TFT_AREA5].show              = true;
    widget[DISPLAY_TFT_AREA5].renew             = true;
    
    widget[DISPLAY_SETTING_AREA2].set_y         = 24;
    widget[DISPLAY_SETTING_AREA2].set_x         = 0;
    widget[DISPLAY_SETTING_AREA2].width         = 320;
    widget[DISPLAY_SETTING_AREA2].height        = 191;
    widget[DISPLAY_SETTING_AREA2].show          = true;
    widget[DISPLAY_SETTING_AREA2].renew         = true;
    
    widget[DISPLAY_BATTERY_AREA].set_y          = 4;
    widget[DISPLAY_BATTERY_AREA].set_x          = 12;
    widget[DISPLAY_BATTERY_AREA].width          = 23;
    widget[DISPLAY_BATTERY_AREA].height         = 13;
    widget[DISPLAY_BATTERY_AREA].show           = true;
    widget[DISPLAY_BATTERY_AREA].renew          = true;
    
    widget[DISPLAY_BLUETOOTH_AREA].set_y        = 3;
    widget[DISPLAY_BLUETOOTH_AREA].set_x        = 43;
    widget[DISPLAY_BLUETOOTH_AREA].width        = 16;
    widget[DISPLAY_BLUETOOTH_AREA].height       = 16;
    widget[DISPLAY_BLUETOOTH_AREA].show         = true;
    widget[DISPLAY_BLUETOOTH_AREA].renew        = true;
    
    widget[DISPLAY_POWER_OFF_TIMER_AREA].set_y  = 3;
    widget[DISPLAY_POWER_OFF_TIMER_AREA].set_x  = 67;
    widget[DISPLAY_POWER_OFF_TIMER_AREA].width  = 16;
    widget[DISPLAY_POWER_OFF_TIMER_AREA].height = 16;
    widget[DISPLAY_POWER_OFF_TIMER_AREA].show   = true;
    widget[DISPLAY_POWER_OFF_TIMER_AREA].renew  = true;
    
    widget[DISPLAY_TRUMPET_AREA].set_y          = 3;
    widget[DISPLAY_TRUMPET_AREA].set_x          = 91;
    widget[DISPLAY_TRUMPET_AREA].width          = 16;
    widget[DISPLAY_TRUMPET_AREA].height         = 16;
    widget[DISPLAY_TRUMPET_AREA].show           = true;
    widget[DISPLAY_TRUMPET_AREA].renew          = true;
    
    widget[DISPLAY_LIGHTING_AREA].set_y         = 3;
    widget[DISPLAY_LIGHTING_AREA].set_x         = 115;
    widget[DISPLAY_LIGHTING_AREA].width         = 16;
    widget[DISPLAY_LIGHTING_AREA].height        = 16;
    widget[DISPLAY_LIGHTING_AREA].show          = true;
    widget[DISPLAY_LIGHTING_AREA].renew         = true;
    
    widget[DISPLAY_REAL_TIME_AREA].set_y        = 5;
    widget[DISPLAY_REAL_TIME_AREA].set_x        = 194;
    widget[DISPLAY_REAL_TIME_AREA].width        = 123;
    widget[DISPLAY_REAL_TIME_AREA].height       = 12;
    widget[DISPLAY_REAL_TIME_AREA].show         = true;
    widget[DISPLAY_REAL_TIME_AREA].renew        = true;
    
    widget[MEASURE_VALUE_MODE_AREA].set_y       = 37;
    widget[MEASURE_VALUE_MODE_AREA].set_x       = 16;
    widget[MEASURE_VALUE_MODE_AREA].width       = 40;
    widget[MEASURE_VALUE_MODE_AREA].height      = 20;
    widget[MEASURE_VALUE_MODE_AREA].show        = true;
    widget[MEASURE_VALUE_MODE_AREA].renew       = true;
    
    widget[DISPLAY_RECORDING_AREA].set_y        = 35;
    widget[DISPLAY_RECORDING_AREA].set_x        = 157;
    widget[DISPLAY_RECORDING_AREA].width        = 99;
    widget[DISPLAY_RECORDING_AREA].height       = 18;
    widget[DISPLAY_RECORDING_AREA].show         = true;
    widget[DISPLAY_RECORDING_AREA].renew        = true;
    
    widget[DISPLAY_HOLD_AREA].set_y             = 35;
    widget[DISPLAY_HOLD_AREA].set_x             = 259;
    widget[DISPLAY_HOLD_AREA].width             = 47;
    widget[DISPLAY_HOLD_AREA].height            = 18;
    widget[DISPLAY_HOLD_AREA].show              = true;
    widget[DISPLAY_HOLD_AREA].renew             = true;
    
    widget[MEASURE_RELATIVE_VALUE_AREA].set_y   = 58;
    widget[MEASURE_RELATIVE_VALUE_AREA].set_x   = 182;
    widget[MEASURE_RELATIVE_VALUE_AREA].width   = 124;
    widget[MEASURE_RELATIVE_VALUE_AREA].height  = 23;
    widget[MEASURE_RELATIVE_VALUE_AREA].show    = true;
    widget[MEASURE_RELATIVE_VALUE_AREA].renew   = true;
    
    widget[MEASURE_VALUE_AREA].set_y            = 83;
    widget[MEASURE_VALUE_AREA].set_x            = 15;
    widget[MEASURE_VALUE_AREA].width            = 250;
    widget[MEASURE_VALUE_AREA].height           = 70;
    widget[MEASURE_VALUE_AREA].show             = true;
    widget[MEASURE_VALUE_AREA].renew            = true;
    
    widget[MEASURE_VALUE_UNIT_AREA].set_y       = 130;
    widget[MEASURE_VALUE_UNIT_AREA].set_x       = 266;
    widget[MEASURE_VALUE_UNIT_AREA].width       = 42;
    widget[MEASURE_VALUE_UNIT_AREA].height      = 19;
    widget[MEASURE_VALUE_UNIT_AREA].show        = true;
    widget[MEASURE_VALUE_UNIT_AREA].renew       = true;
    
    widget[MEASURE_LO_AREA].set_y               = 189;
    widget[MEASURE_LO_AREA].set_x               = 5;
    widget[MEASURE_LO_AREA].width               = 32;
    widget[MEASURE_LO_AREA].height              = 15;
    widget[MEASURE_LO_AREA].show                = true;
    widget[MEASURE_LO_AREA].renew               = true;
    
    widget[MEASURE_LOZ_AREA].set_y              = 189;
    widget[MEASURE_LOZ_AREA].set_x              = 293;
    widget[MEASURE_LOZ_AREA].width              = 32;
    widget[MEASURE_LOZ_AREA].height             = 12;
    widget[MEASURE_LOZ_AREA].show               = true;
    widget[MEASURE_LOZ_AREA].renew              = true;
    
    widget[MEASURE_RULER_AREA].set_y            = 170;
    widget[MEASURE_RULER_AREA].set_x            = 29;
    widget[MEASURE_RULER_AREA].width            = 240;
    widget[MEASURE_RULER_AREA].height           = 20;
    widget[MEASURE_RULER_AREA].show             = true;
    widget[MEASURE_RULER_AREA].renew            = true;
    
    widget[MEASURE_RANGE_STATUS_AREA].set_y     = 37;
    widget[MEASURE_RANGE_STATUS_AREA].set_x     = 16;
    widget[MEASURE_RANGE_STATUS_AREA].width     = 40;
    widget[MEASURE_RANGE_STATUS_AREA].height    = 8;
    widget[MEASURE_RANGE_STATUS_AREA].show      = true;
    widget[MEASURE_RANGE_STATUS_AREA].renew     = true;
    
    widget[F1_MENUBAR_AREA].set_y               = 215;
    widget[F1_MENUBAR_AREA].set_x               = 21;
    widget[F1_MENUBAR_AREA].width               = 68;
    widget[F1_MENUBAR_AREA].height              = 24;
    widget[F1_MENUBAR_AREA].show                = true;
    widget[F1_MENUBAR_AREA].renew               = true;
    
    widget[F2_MENUBAR_AREA].set_y               = 215;
    widget[F2_MENUBAR_AREA].set_x               = 91;
    widget[F2_MENUBAR_AREA].width               = 68;
    widget[F2_MENUBAR_AREA].height              = 24;
    widget[F2_MENUBAR_AREA].show                = true;
    widget[F2_MENUBAR_AREA].renew               = true;
    
    widget[F3_MENUBAR_AREA].set_y               = 215;
    widget[F3_MENUBAR_AREA].set_x               = 161;
    widget[F3_MENUBAR_AREA].width               = 68;
    widget[F3_MENUBAR_AREA].height              = 24;
    widget[F3_MENUBAR_AREA].show                = true;
    widget[F3_MENUBAR_AREA].renew               = true;
    
    widget[F4_MENUBAR_AREA].set_y               = 215;
    widget[F4_MENUBAR_AREA].set_x               = 231;
    widget[F4_MENUBAR_AREA].width               = 68;
    widget[F4_MENUBAR_AREA].height              = 24;
    widget[F4_MENUBAR_AREA].show                = true;
    widget[F4_MENUBAR_AREA].renew               = true;
    
    widget[PREV_MENUBAR_AREA].set_y             = 215;
    widget[PREV_MENUBAR_AREA].set_x             = 0;
    widget[PREV_MENUBAR_AREA].width             = 19;
    widget[PREV_MENUBAR_AREA].height            = 24;
    widget[PREV_MENUBAR_AREA].show              = true;
    widget[PREV_MENUBAR_AREA].renew             = true;
    
    widget[NEXT_MENUBAR_AREA].set_y             = 215;
    widget[NEXT_MENUBAR_AREA].set_x             = 301;
    widget[NEXT_MENUBAR_AREA].width             = 19;
    widget[NEXT_MENUBAR_AREA].height            = 24;
    widget[NEXT_MENUBAR_AREA].show              = true;
    widget[NEXT_MENUBAR_AREA].renew             = true;
    
    widget[SETTING_LIST_AREA].set_y             = 33;
    widget[SETTING_LIST_AREA].set_x             = 3;
    widget[SETTING_LIST_AREA].width             = 157;
    widget[SETTING_LIST_AREA].height            = 17;
    widget[SETTING_LIST_AREA].show              = true;
    widget[SETTING_LIST_AREA].renew             = true;
}

void set_menubar_function(unsigned char function)
{
    menubar.menu_function = function;
    // F1_KEY_EVT placeholder parameter
    function_key_event_enable(F1_KEY_EVT);
}

unsigned char read_menubar_function()
{
    return menubar.menu_function;
}

void set_menubar_level(unsigned char level)
{
    unsigned char function = read_menubar_function();

    menubar.menu_level[function] = level;
}

unsigned char read_menubar_level()
{
    unsigned char function = read_menubar_function();

    return menubar.menu_level[function];
}

void set_menubar_page(unsigned char page)
{
    unsigned char function = read_menubar_function();

    menubar.menu_page[function] = page;
}

unsigned char read_menubar_page()
{
    unsigned char function = read_menubar_function();

    return menubar.menu_page[function];
}

void set_menubar_pressed(unsigned char menu_num)
{
    unsigned char function = read_menubar_function();
    unsigned char level = read_menubar_level();

    menubar.menu_selected[function][level] = menu_num;
}

unsigned char read_pressed_menubar()
{
    unsigned char function = read_menubar_function();
    unsigned char level = read_menubar_level();

    return menubar.menu_selected[function][level];
}

void function_key_event(unsigned char key_event)
{
    unsigned char function = read_menubar_function();
    unsigned char level = read_menubar_level();

    (*key_event_controller[function][level])(key_event);
}

void function_key_event_enable(unsigned char key)
{
    unsigned char function = read_menubar_function();
    unsigned char level = read_menubar_level();

    (*key_event_enable[function][level])(key);
}

void display_menubar_content(unsigned char key_event, unsigned char * vm)
{
    unsigned char function = read_menubar_function();
    unsigned char level = read_menubar_level();

    (*display_menu_content[function][level])(key_event, vm);
}

void menubar_pressed(unsigned char key_event)
{
    if (!widget[DISPLAY_TFT_AREA5].show)
        return;

    switch (key_event) {
        case F1_KEY_EVT:
            widget[F1_MENUBAR_AREA].pressed   = true;
            widget[F2_MENUBAR_AREA].pressed   = false;
            widget[F3_MENUBAR_AREA].pressed   = false;
            widget[F4_MENUBAR_AREA].pressed   = false;
            widget[PREV_MENUBAR_AREA].pressed = false;
            widget[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case F2_KEY_EVT:
            widget[F1_MENUBAR_AREA].pressed   = false;
            widget[F2_MENUBAR_AREA].pressed   = true;
            widget[F3_MENUBAR_AREA].pressed   = false;
            widget[F4_MENUBAR_AREA].pressed   = false;
            widget[PREV_MENUBAR_AREA].pressed = false;
            widget[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case F3_KEY_EVT:
            widget[F1_MENUBAR_AREA].pressed   = false;
            widget[F2_MENUBAR_AREA].pressed   = false;
            widget[F3_MENUBAR_AREA].pressed   = true;
            widget[F4_MENUBAR_AREA].pressed   = false;
            widget[PREV_MENUBAR_AREA].pressed = false;
            widget[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case F4_KEY_EVT:
            widget[F1_MENUBAR_AREA].pressed   = false;
            widget[F2_MENUBAR_AREA].pressed   = false;
            widget[F3_MENUBAR_AREA].pressed   = false;
            widget[F4_MENUBAR_AREA].pressed   = true;
            widget[PREV_MENUBAR_AREA].pressed = false;
            widget[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case PREV_KEY_EVT:
            widget[F1_MENUBAR_AREA].pressed   = false;
            widget[F2_MENUBAR_AREA].pressed   = false;
            widget[F3_MENUBAR_AREA].pressed   = false;
            widget[F4_MENUBAR_AREA].pressed   = false;
            widget[PREV_MENUBAR_AREA].pressed = true;
            widget[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case NEXT_KEY_EVT:
            widget[F1_MENUBAR_AREA].pressed   = false;
            widget[F2_MENUBAR_AREA].pressed   = false;
            widget[F3_MENUBAR_AREA].pressed   = false;
            widget[F4_MENUBAR_AREA].pressed   = false;
            widget[PREV_MENUBAR_AREA].pressed = false;
            widget[NEXT_MENUBAR_AREA].pressed = true;
            menubar_flush_enable();
            break;

        case RELEASE:
            function_key_event_enable(F1_KEY_EVT);
            widget[F1_MENUBAR_AREA].pressed   = false;
            widget[F2_MENUBAR_AREA].pressed   = false;
            widget[F3_MENUBAR_AREA].pressed   = false;
            widget[F4_MENUBAR_AREA].pressed   = false;
            widget[PREV_MENUBAR_AREA].pressed = false;
            widget[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;
    }
}

void display_area1_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_TFT_AREA1](vm);

    if (widget[DISPLAY_TFT_AREA1].renew || widget[DISPLAY_TFT_AREA1].auto_renew) {
        widget[DISPLAY_BATTERY_AREA].renew = true;
        widget[DISPLAY_BLUETOOTH_AREA].renew = true;
        widget[DISPLAY_POWER_OFF_TIMER_AREA].renew = true;
        widget[DISPLAY_TRUMPET_AREA].renew = true;
        widget[DISPLAY_LIGHTING_AREA].renew = true;
        widget[DISPLAY_REAL_TIME_AREA].renew = true;
    }

    display_battery_flush(vm);
    display_bluetooth_flush(vm);
    display_power_off_timer_flush(vm);
    display_trumpet_flush(vm);
    display_lighting_flush(vm);
    display_real_time_flush(vm);

    widget[DISPLAY_BATTERY_AREA].renew = false;
    widget[DISPLAY_BLUETOOTH_AREA].renew = false;
    widget[DISPLAY_POWER_OFF_TIMER_AREA].renew = false;
    widget[DISPLAY_TRUMPET_AREA].renew = false;
    widget[DISPLAY_LIGHTING_AREA].renew = false;
    widget[DISPLAY_REAL_TIME_AREA].renew = false;
}

void display_area1_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA1].show)
        widget[DISPLAY_TFT_AREA1].renew = true;
}

void display_battery_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_BATTERY_AREA](vm);
    widget[DISPLAY_BATTERY_AREA].renew = false;
}

void battery_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA1].show)
        widget[DISPLAY_BATTERY_AREA].renew = true;
}

void display_bluetooth_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_BLUETOOTH_AREA](vm);
    widget[DISPLAY_BLUETOOTH_AREA].renew = false;
}

void display_power_off_timer_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_POWER_OFF_TIMER_AREA](vm);
    widget[DISPLAY_POWER_OFF_TIMER_AREA].renew = false;
}

void display_trumpet_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_TRUMPET_AREA](vm);
    widget[DISPLAY_TRUMPET_AREA].renew = false;
}

void display_lighting_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_LIGHTING_AREA](vm);
    widget[DISPLAY_LIGHTING_AREA].renew = false;
}

void display_real_time_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_REAL_TIME_AREA](vm);
    widget[DISPLAY_REAL_TIME_AREA].renew = false;
}

void display_area2_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_TFT_AREA2](vm);

    if (widget[DISPLAY_TFT_AREA2].renew || widget[DISPLAY_TFT_AREA2].auto_renew) {
        widget[MEASURE_VALUE_MODE_AREA].renew = true;
        widget[DISPLAY_RECORDING_AREA].renew = true;
        widget[DISPLAY_HOLD_AREA].renew = true;
        widget[MEASURE_RELATIVE_VALUE_AREA].renew = true;
    }

    display_measure_value_mode_flush(vm);
    display_recording_flush(vm);
    display_hold_flush(vm);
    display_relative_value_flush(vm);

    widget[MEASURE_VALUE_MODE_AREA].renew = false;
    widget[DISPLAY_RECORDING_AREA].renew = false;
    widget[DISPLAY_HOLD_AREA].renew = false;
    widget[MEASURE_RELATIVE_VALUE_AREA].renew = false;
}

void display_area2_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA2].show)
        widget[DISPLAY_TFT_AREA2].renew = true;
}

void display_measure_value_mode_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_VALUE_MODE_AREA](vm);
    widget[MEASURE_VALUE_MODE_AREA].renew = false;
}

void display_recording_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_RECORDING_AREA](vm);
    widget[DISPLAY_RECORDING_AREA].renew = false;
}

void display_hold_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_HOLD_AREA](vm);
    widget[DISPLAY_HOLD_AREA].renew = false;
}

void display_relative_value_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_RELATIVE_VALUE_AREA](vm);
    widget[MEASURE_RELATIVE_VALUE_AREA].renew = false;
}

void display_area3_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_TFT_AREA3](vm);

    if (widget[DISPLAY_TFT_AREA3].renew || widget[DISPLAY_TFT_AREA3].auto_renew) {
        widget[MEASURE_VALUE_AREA].renew = true;
        widget[MEASURE_VALUE_UNIT_AREA].renew = true;
    }

    display_measure_value_flush(vm);
    display_measure_value_unit_flush(vm);

    widget[MEASURE_VALUE_AREA].renew = false;
    widget[MEASURE_VALUE_UNIT_AREA].renew = false;
}

void display_area3_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA3].show)
        widget[DISPLAY_TFT_AREA3].renew = true;
}

void display_measure_value_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_VALUE_AREA](vm);
    widget[MEASURE_VALUE_AREA].renew = false;
}

void measure_value_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA3].show)
        widget[MEASURE_VALUE_AREA].renew = true;
}

void display_measure_value_unit_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_VALUE_UNIT_AREA](vm);
    widget[MEASURE_VALUE_UNIT_AREA].renew = false;
}

void display_area4_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_TFT_AREA4](vm);

    if (widget[DISPLAY_TFT_AREA4].renew || widget[DISPLAY_TFT_AREA4].auto_renew) {
        widget[MEASURE_LO_AREA].renew = true;
        widget[MEASURE_LOZ_AREA].renew = true;
        widget[MEASURE_RULER_AREA].renew = true;
        widget[MEASURE_RANGE_STATUS_AREA].renew = true;
    }

    display_measure_lo_flush(vm);
    display_measure_loz_flush(vm);
    display_measure_ruler_flush(vm);
    display_measure_range_status_flush(vm);

    widget[MEASURE_LO_AREA].renew = false;
    widget[MEASURE_LOZ_AREA].renew = false;
    widget[MEASURE_RULER_AREA].renew = false;
    widget[MEASURE_RANGE_STATUS_AREA].renew = false;
}

void display_area4_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA4].show)
        widget[DISPLAY_TFT_AREA4].renew = true;
}

void display_measure_lo_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_LO_AREA](vm);
    widget[MEASURE_LO_AREA].renew = false;
}

void display_measure_loz_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_LOZ_AREA](vm);
    widget[MEASURE_LOZ_AREA].renew = false;
}

void display_measure_ruler_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_RULER_AREA](vm);
    widget[MEASURE_RULER_AREA].renew = false;
}

void display_measure_range_status_flush(unsigned char * vm)
{
    display_widget_show[MEASURE_RANGE_STATUS_AREA](vm);
    widget[MEASURE_RANGE_STATUS_AREA].renew = false;
}

void display_area5_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_TFT_AREA5](vm);

    if (widget[DISPLAY_TFT_AREA5].renew || widget[DISPLAY_TFT_AREA5].auto_renew) {
        widget[F1_MENUBAR_AREA].renew = true;
        widget[F2_MENUBAR_AREA].renew = true;
        widget[F3_MENUBAR_AREA].renew = true;
        widget[F4_MENUBAR_AREA].renew = true;
        widget[PREV_MENUBAR_AREA].renew = true;
        widget[NEXT_MENUBAR_AREA].renew = true;
    }

    display_f1_menubar_flush(vm);
    display_f2_menubar_flush(vm);
    display_f3_menubar_flush(vm);
    display_f4_menubar_flush(vm);
    display_prev_menubar_flush(vm);
    display_next_menubar_flush(vm);

    widget[F1_MENUBAR_AREA].renew = false;
    widget[F2_MENUBAR_AREA].renew = false;
    widget[F3_MENUBAR_AREA].renew = false;
    widget[F4_MENUBAR_AREA].renew = false;
    widget[PREV_MENUBAR_AREA].renew = false;
    widget[NEXT_MENUBAR_AREA].renew = false;
}

void display_area5_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA5].show)
        widget[DISPLAY_TFT_AREA5].renew = true;
}

void display_f1_menubar_flush(unsigned char * vm)
{
    display_widget_show[F1_MENUBAR_AREA](vm);
    widget[F1_MENUBAR_AREA].renew = false;
}

void display_f2_menubar_flush(unsigned char * vm)
{
    display_widget_show[F2_MENUBAR_AREA](vm);
    widget[F2_MENUBAR_AREA].renew = false;
}

void display_f3_menubar_flush(unsigned char * vm)
{
    display_widget_show[F3_MENUBAR_AREA](vm);
    widget[F3_MENUBAR_AREA].renew = false;
}

void display_f4_menubar_flush(unsigned char * vm)
{
    display_widget_show[F4_MENUBAR_AREA](vm);
    widget[F4_MENUBAR_AREA].renew = false;
}

void display_prev_menubar_flush(unsigned char * vm)
{
    display_widget_show[PREV_MENUBAR_AREA](vm);
    widget[PREV_MENUBAR_AREA].renew = false;
}

void display_next_menubar_flush(unsigned char * vm)
{
    display_widget_show[NEXT_MENUBAR_AREA](vm);
    widget[NEXT_MENUBAR_AREA].renew = false;
}

void menubar_flush_enable()
{
    if (widget[DISPLAY_TFT_AREA5].show)
        widget[DISPLAY_TFT_AREA5].renew = true;
}

static void measure_interface(unsigned char * vm)
{
    // -------- temp flush ---------
    display_area1_flush_enable();
    display_area2_flush_enable();
    display_area3_flush_enable();
    display_area4_flush_enable();
    // display_area5_flush_enable();
    // -----------------------------

    display_area1_flush(vm);
    display_area2_flush(vm);
    display_area3_flush(vm);
    display_area4_flush(vm);
    display_area5_flush(vm);

    // widget[DISPLAY_TFT_AREA1].renew = false;
    // widget[DISPLAY_TFT_AREA2].renew = false;
    // widget[DISPLAY_TFT_AREA3].renew = false;
    // widget[DISPLAY_TFT_AREA4].renew = false;
    // widget[DISPLAY_TFT_AREA5].renew = false;
    // widget[SETTING_PAGE_AREA].renew = false;
}

void display_setting_area2_flush(unsigned char * vm)
{
    display_widget_show[DISPLAY_SETTING_AREA2](vm);

    if (widget[DISPLAY_SETTING_AREA2].renew || widget[DISPLAY_SETTING_AREA2].auto_renew) {
        widget[SETTING_LIST_AREA].renew = true;
    }

    display_setting_list_flush(vm);

    widget[SETTING_LIST_AREA].renew = false;
}

void display_setting_area2_flush_enable()
{
    if (widget[DISPLAY_SETTING_AREA2].show)
        widget[DISPLAY_SETTING_AREA2].renew = true;
}

void display_setting_list_flush(unsigned char * vm)
{
    display_widget_show[SETTING_LIST_AREA](vm);
    widget[SETTING_LIST_AREA].renew = false;
}

static void setting_interface(unsigned char * vm)
{
    // -------- temp flush ---------
    display_area1_flush_enable();
    // display_area2_flush_enable();
    // display_area3_flush_enable();
    // display_area4_flush_enable();
    // display_area5_flush_enable();
    // -----------------------------

    display_area1_flush(vm);
    display_setting_area2_flush(vm);
    display_area5_flush(vm);

    // widget[DISPLAY_TFT_AREA1].renew = false;
    // widget[DISPLAY_TFT_AREA2].renew = false;
    // widget[DISPLAY_TFT_AREA3].renew = false;
    // widget[DISPLAY_TFT_AREA4].renew = false;
    // widget[DISPLAY_TFT_AREA5].renew = false;
    // widget[SETTING_PAGE_AREA].renew = false;
}

void display_flush(unsigned char * vm)
{
    switch (read_menubar_function()) {
        case DMM_SETTING:
            setting_interface(vm);
            break;
        default:
            measure_interface(vm);
            break;
    }
}

const tft_region_setting tft_region = (const tft_region_setting)TFT_REGION_SETTING_DRV;
const tft_write_data tft_write = (const tft_write_data)TFT_WRITE_DATA_DRV;

void tft_clear(unsigned char color)
{
    unsigned int buf_size;

    buf_size = TFT_WIDTH * TFT_HEIGHT;
    tft_region(0, 0, TFT_WIDTH, TFT_HEIGHT);

    for (unsigned int i = 0; i < buf_size; i++)
        tft_write(color_data[color]);
}

/**
 * +-----> x
 * |O
 * | tft
 * y
 * 
 * y * tft_width + x = index
 * -----------------------
 * y = (index - x) / tft_width;
 * x = index - (y * tft_width);
 * 
 * x = 0; // later x must clean
 * y = 0; // later y must clean
 * 
 * widget[PREV_MENUBAR_AREA].set_y  = 215;
 * widget[PREV_MENUBAR_AREA].set_x  = 4;
 * widget[PREV_MENUBAR_AREA].width  = 15;
 * widget[PREV_MENUBAR_AREA].height = 24;
 */

/**
 * +-----> x
 * |O
 * | tft
 * y
 * 
 * index = y * tft_width + x
 * offset = y * tft_width
 * -----------------------
 * tft_buf[index + offset]
 * 
 * widget[PREV_MENUBAR_AREA].set_y  = 215;
 * widget[PREV_MENUBAR_AREA].set_x  = 4;
 * widget[PREV_MENUBAR_AREA].width  = 15;
 * widget[PREV_MENUBAR_AREA].height = 24;
 */

void tft_flush_area(unsigned char area_num, unsigned char * vm)
{
    unsigned int area_y;
    unsigned int area_x;
    unsigned int area_width;
    unsigned int area_height;
    unsigned int area_yend;

    unsigned char color;
    unsigned char * arr;

    if (area_num == 0) {
        area_y      = widget[DISPLAY_TFT_AREA1].set_y;
        area_x      = widget[DISPLAY_TFT_AREA1].set_x;
        area_width  = widget[DISPLAY_TFT_AREA1].width;
        area_height = widget[DISPLAY_TFT_AREA1].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 1) {
        area_y      = widget[DISPLAY_TFT_AREA2].set_y;
        area_x      = widget[DISPLAY_TFT_AREA2].set_x;
        area_width  = widget[DISPLAY_TFT_AREA2].width;
        area_height = widget[DISPLAY_TFT_AREA2].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 2) {
        area_y      = widget[DISPLAY_TFT_AREA3].set_y;
        area_x      = widget[DISPLAY_TFT_AREA3].set_x;
        area_width  = widget[DISPLAY_TFT_AREA3].width;
        area_height = widget[DISPLAY_TFT_AREA3].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 3) {
        area_y      = widget[DISPLAY_TFT_AREA4].set_y;
        area_x      = widget[DISPLAY_TFT_AREA4].set_x;
        area_width  = widget[DISPLAY_TFT_AREA4].width;
        area_height = widget[DISPLAY_TFT_AREA4].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 4) {
        area_y      = widget[DISPLAY_TFT_AREA5].set_y;
        area_x      = widget[DISPLAY_TFT_AREA5].set_x;
        area_width  = widget[DISPLAY_TFT_AREA5].width;
        area_height = widget[DISPLAY_TFT_AREA5].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 5) {
        area_y      = widget[DISPLAY_SETTING_AREA2].set_y;
        area_x      = widget[DISPLAY_SETTING_AREA2].set_x;
        area_width  = widget[DISPLAY_SETTING_AREA2].width;
        area_height = widget[DISPLAY_SETTING_AREA2].height;
        area_yend   = area_y + area_height;
    }

    tft_region(area_y, area_x, area_width, area_height);

    unsigned char theme = equip.themecolor * COLOR_MAX;

    for (unsigned int y = area_y; y < area_yend; y++) {
        for (unsigned int x = 0; x < area_width; x++) {
            tft_write(color_data[vm[y * TFT_WIDTH + x] + theme]);
        }
    }
}

void tft_flush(unsigned char * vm)
{
    unsigned char current_function;
    current_function = read_menubar_function();

    if (widget[DISPLAY_TFT_AREA1].renew) {
        tft_flush_area(0, vm);
        widget[DISPLAY_TFT_AREA1].renew = false;
    }

    if (widget[DISPLAY_TFT_AREA2].renew && (current_function != DMM_SETTING)) {
        tft_flush_area(1, vm);
        widget[DISPLAY_TFT_AREA2].renew = false;
    }

    if (widget[DISPLAY_TFT_AREA3].renew && (current_function != DMM_SETTING)) {
        tft_flush_area(2, vm);
        widget[DISPLAY_TFT_AREA3].renew = false;
    }

    if (widget[DISPLAY_TFT_AREA4].renew && (current_function != DMM_SETTING)) {
        tft_flush_area(3, vm);
        widget[DISPLAY_TFT_AREA4].renew = false;
    }

    if (widget[DISPLAY_TFT_AREA5].renew) {
        tft_flush_area(4, vm);
        widget[DISPLAY_TFT_AREA5].renew = false;
    }

    if (widget[DISPLAY_SETTING_AREA2].renew && (current_function == DMM_SETTING)) {
        tft_flush_area(5, vm);
        widget[DISPLAY_SETTING_AREA2].renew = false;
    }
}
