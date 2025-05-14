
#include "display_controller.h"

dev_area_t _Area[WIDGET_NUM_MAX];
dev_actbar_t menubar;

const key_event_interface * key_event_controller[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {voltage_level1_key_event,        NULL},
    {setting_level1_key_event,        NULL},
};

const key_event_interface * key_event_enable[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {voltage_level1_key_event_enable, NULL},
    {setting_level1_key_event_enable, NULL},
};

const menu_content_interface * display_menu_content[FUNC_TYPE_MAX][DEPTH_MAX] = {
    {voltage_level1_menu,             NULL},
    {setting_level1_menu,             NULL},
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
    _Area[DISPLAY_TFT_AREA1].set_y             = 0;
    _Area[DISPLAY_TFT_AREA1].set_x             = 0;
    _Area[DISPLAY_TFT_AREA1].width             = 320;
    _Area[DISPLAY_TFT_AREA1].height            = 24;
    _Area[DISPLAY_TFT_AREA1].valid              = true;
    _Area[DISPLAY_TFT_AREA1].refer             = true;
    
    _Area[DISPLAY_TFT_AREA2].set_y             = 24;
    _Area[DISPLAY_TFT_AREA2].set_x             = 0;
    _Area[DISPLAY_TFT_AREA2].width             = 320;
    _Area[DISPLAY_TFT_AREA2].height            = 54;
    _Area[DISPLAY_TFT_AREA2].valid              = true;
    _Area[DISPLAY_TFT_AREA2].refer             = true;
    
    _Area[DISPLAY_TFT_AREA3].set_y             = 78;
    _Area[DISPLAY_TFT_AREA3].set_x             = 0;
    _Area[DISPLAY_TFT_AREA3].width             = 320;
    _Area[DISPLAY_TFT_AREA3].height            = 84;
    _Area[DISPLAY_TFT_AREA3].valid              = true;
    _Area[DISPLAY_TFT_AREA3].refer             = true;
    
    _Area[DISPLAY_TFT_AREA4].set_y             = 162;
    _Area[DISPLAY_TFT_AREA4].set_x             = 0;
    _Area[DISPLAY_TFT_AREA4].width             = 320;
    _Area[DISPLAY_TFT_AREA4].height            = 53;
    _Area[DISPLAY_TFT_AREA4].valid              = true;
    _Area[DISPLAY_TFT_AREA4].refer             = true;
    
    _Area[DISPLAY_TFT_AREA5].set_y             = 215;
    _Area[DISPLAY_TFT_AREA5].set_x             = 0;
    _Area[DISPLAY_TFT_AREA5].width             = 320;
    _Area[DISPLAY_TFT_AREA5].height            = 24;
    _Area[DISPLAY_TFT_AREA5].valid              = true;
    _Area[DISPLAY_TFT_AREA5].refer             = true;
    
    _Area[DISPLAY_SETTING_AREA2].set_y         = 24;
    _Area[DISPLAY_SETTING_AREA2].set_x         = 0;
    _Area[DISPLAY_SETTING_AREA2].width         = 320;
    _Area[DISPLAY_SETTING_AREA2].height        = 191;
    _Area[DISPLAY_SETTING_AREA2].valid          = true;
    _Area[DISPLAY_SETTING_AREA2].refer         = true;
    
    _Area[DISPLAY_BATTERY_AREA].set_y          = 4;
    _Area[DISPLAY_BATTERY_AREA].set_x          = 12;
    _Area[DISPLAY_BATTERY_AREA].width          = 23;
    _Area[DISPLAY_BATTERY_AREA].height         = 13;
    _Area[DISPLAY_BATTERY_AREA].valid           = true;
    _Area[DISPLAY_BATTERY_AREA].refer          = true;
    
    _Area[DISPLAY_BLUETOOTH_AREA].set_y        = 3;
    _Area[DISPLAY_BLUETOOTH_AREA].set_x        = 43;
    _Area[DISPLAY_BLUETOOTH_AREA].width        = 16;
    _Area[DISPLAY_BLUETOOTH_AREA].height       = 16;
    _Area[DISPLAY_BLUETOOTH_AREA].valid         = true;
    _Area[DISPLAY_BLUETOOTH_AREA].refer        = true;
    
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].set_y  = 3;
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].set_x  = 67;
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].width  = 16;
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].height = 16;
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].valid   = true;
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].refer  = true;
    
    _Area[DISPLAY_TRUMPET_AREA].set_y          = 3;
    _Area[DISPLAY_TRUMPET_AREA].set_x          = 91;
    _Area[DISPLAY_TRUMPET_AREA].width          = 16;
    _Area[DISPLAY_TRUMPET_AREA].height         = 16;
    _Area[DISPLAY_TRUMPET_AREA].valid           = true;
    _Area[DISPLAY_TRUMPET_AREA].refer          = true;
    
    _Area[DISPLAY_LIGHTING_AREA].set_y         = 3;
    _Area[DISPLAY_LIGHTING_AREA].set_x         = 115;
    _Area[DISPLAY_LIGHTING_AREA].width         = 16;
    _Area[DISPLAY_LIGHTING_AREA].height        = 16;
    _Area[DISPLAY_LIGHTING_AREA].valid          = true;
    _Area[DISPLAY_LIGHTING_AREA].refer         = true;
    
    _Area[DISPLAY_REAL_TIME_AREA].set_y        = 5;
    _Area[DISPLAY_REAL_TIME_AREA].set_x        = 194;
    _Area[DISPLAY_REAL_TIME_AREA].width        = 123;
    _Area[DISPLAY_REAL_TIME_AREA].height       = 12;
    _Area[DISPLAY_REAL_TIME_AREA].valid         = true;
    _Area[DISPLAY_REAL_TIME_AREA].refer        = true;
    
    _Area[MEASURE_VALUE_MODE_AREA].set_y       = 37;
    _Area[MEASURE_VALUE_MODE_AREA].set_x       = 16;
    _Area[MEASURE_VALUE_MODE_AREA].width       = 40;
    _Area[MEASURE_VALUE_MODE_AREA].height      = 20;
    _Area[MEASURE_VALUE_MODE_AREA].valid        = true;
    _Area[MEASURE_VALUE_MODE_AREA].refer       = true;
    
    _Area[DISPLAY_RECORDING_AREA].set_y        = 35;
    _Area[DISPLAY_RECORDING_AREA].set_x        = 157;
    _Area[DISPLAY_RECORDING_AREA].width        = 99;
    _Area[DISPLAY_RECORDING_AREA].height       = 18;
    _Area[DISPLAY_RECORDING_AREA].valid         = true;
    _Area[DISPLAY_RECORDING_AREA].refer        = true;
    
    _Area[DISPLAY_HOLD_AREA].set_y             = 35;
    _Area[DISPLAY_HOLD_AREA].set_x             = 259;
    _Area[DISPLAY_HOLD_AREA].width             = 47;
    _Area[DISPLAY_HOLD_AREA].height            = 18;
    _Area[DISPLAY_HOLD_AREA].valid              = true;
    _Area[DISPLAY_HOLD_AREA].refer             = true;
    
    _Area[MEASURE_RELATIVE_VALUE_AREA].set_y   = 58;
    _Area[MEASURE_RELATIVE_VALUE_AREA].set_x   = 182;
    _Area[MEASURE_RELATIVE_VALUE_AREA].width   = 124;
    _Area[MEASURE_RELATIVE_VALUE_AREA].height  = 23;
    _Area[MEASURE_RELATIVE_VALUE_AREA].valid    = true;
    _Area[MEASURE_RELATIVE_VALUE_AREA].refer   = true;
    
    _Area[MEASURE_VALUE_AREA].set_y            = 83;
    _Area[MEASURE_VALUE_AREA].set_x            = 15;
    _Area[MEASURE_VALUE_AREA].width            = 250;
    _Area[MEASURE_VALUE_AREA].height           = 70;
    _Area[MEASURE_VALUE_AREA].valid             = true;
    _Area[MEASURE_VALUE_AREA].refer            = true;
    
    _Area[MEASURE_VALUE_UNIT_AREA].set_y       = 130;
    _Area[MEASURE_VALUE_UNIT_AREA].set_x       = 266;
    _Area[MEASURE_VALUE_UNIT_AREA].width       = 42;
    _Area[MEASURE_VALUE_UNIT_AREA].height      = 19;
    _Area[MEASURE_VALUE_UNIT_AREA].valid        = true;
    _Area[MEASURE_VALUE_UNIT_AREA].refer       = true;
    
    _Area[MEASURE_LO_AREA].set_y               = 189;
    _Area[MEASURE_LO_AREA].set_x               = 5;
    _Area[MEASURE_LO_AREA].width               = 32;
    _Area[MEASURE_LO_AREA].height              = 15;
    _Area[MEASURE_LO_AREA].valid                = true;
    _Area[MEASURE_LO_AREA].refer               = true;
    
    _Area[MEASURE_LOZ_AREA].set_y              = 189;
    _Area[MEASURE_LOZ_AREA].set_x              = 293;
    _Area[MEASURE_LOZ_AREA].width              = 32;
    _Area[MEASURE_LOZ_AREA].height             = 12;
    _Area[MEASURE_LOZ_AREA].valid               = true;
    _Area[MEASURE_LOZ_AREA].refer              = true;
    
    _Area[MEASURE_RULER_AREA].set_y            = 170;
    _Area[MEASURE_RULER_AREA].set_x            = 29;
    _Area[MEASURE_RULER_AREA].width            = 240;
    _Area[MEASURE_RULER_AREA].height           = 20;
    _Area[MEASURE_RULER_AREA].valid             = true;
    _Area[MEASURE_RULER_AREA].refer            = true;
    
    _Area[MEASURE_RANGE_STATUS_AREA].set_y     = 37;
    _Area[MEASURE_RANGE_STATUS_AREA].set_x     = 16;
    _Area[MEASURE_RANGE_STATUS_AREA].width     = 40;
    _Area[MEASURE_RANGE_STATUS_AREA].height    = 8;
    _Area[MEASURE_RANGE_STATUS_AREA].valid      = true;
    _Area[MEASURE_RANGE_STATUS_AREA].refer     = true;
    
    _Area[F1_MENUBAR_AREA].set_y               = 215;
    _Area[F1_MENUBAR_AREA].set_x               = 21;
    _Area[F1_MENUBAR_AREA].width               = 68;
    _Area[F1_MENUBAR_AREA].height              = 24;
    _Area[F1_MENUBAR_AREA].valid                = true;
    _Area[F1_MENUBAR_AREA].refer               = true;
    
    _Area[F2_MENUBAR_AREA].set_y               = 215;
    _Area[F2_MENUBAR_AREA].set_x               = 91;
    _Area[F2_MENUBAR_AREA].width               = 68;
    _Area[F2_MENUBAR_AREA].height              = 24;
    _Area[F2_MENUBAR_AREA].valid                = true;
    _Area[F2_MENUBAR_AREA].refer               = true;
    
    _Area[F3_MENUBAR_AREA].set_y               = 215;
    _Area[F3_MENUBAR_AREA].set_x               = 161;
    _Area[F3_MENUBAR_AREA].width               = 68;
    _Area[F3_MENUBAR_AREA].height              = 24;
    _Area[F3_MENUBAR_AREA].valid                = true;
    _Area[F3_MENUBAR_AREA].refer               = true;
    
    _Area[F4_MENUBAR_AREA].set_y               = 215;
    _Area[F4_MENUBAR_AREA].set_x               = 231;
    _Area[F4_MENUBAR_AREA].width               = 68;
    _Area[F4_MENUBAR_AREA].height              = 24;
    _Area[F4_MENUBAR_AREA].valid                = true;
    _Area[F4_MENUBAR_AREA].refer               = true;
    
    _Area[PREV_MENUBAR_AREA].set_y             = 215;
    _Area[PREV_MENUBAR_AREA].set_x             = 0;
    _Area[PREV_MENUBAR_AREA].width             = 19;
    _Area[PREV_MENUBAR_AREA].height            = 24;
    _Area[PREV_MENUBAR_AREA].valid              = true;
    _Area[PREV_MENUBAR_AREA].refer             = true;
    
    _Area[NEXT_MENUBAR_AREA].set_y             = 215;
    _Area[NEXT_MENUBAR_AREA].set_x             = 301;
    _Area[NEXT_MENUBAR_AREA].width             = 19;
    _Area[NEXT_MENUBAR_AREA].height            = 24;
    _Area[NEXT_MENUBAR_AREA].valid              = true;
    _Area[NEXT_MENUBAR_AREA].refer             = true;
    
    _Area[SETTING_LIST_AREA].set_y             = 33;
    _Area[SETTING_LIST_AREA].set_x             = 3;
    _Area[SETTING_LIST_AREA].width             = 157;
    _Area[SETTING_LIST_AREA].height            = 17;
    _Area[SETTING_LIST_AREA].valid              = true;
    _Area[SETTING_LIST_AREA].refer             = true;
}

void set_menubar_function(uint8_t function)
{
    menubar.func = function;
    // F1_KEY_EVT placeholder parameter
    function_key_event_enable(F1_KEY_EVT);
}

uint8_t read_menubar_function()
{
    return menubar.func;
}

void set_menubar_level(uint8_t level)
{
    uint8_t function = read_menubar_function();

    menubar._depth[function] = level;
}

uint8_t read_menubar_level()
{
    uint8_t function = read_menubar_function();

    return menubar._depth[function];
}

void set_menubar_page(uint8_t page)
{
    uint8_t function = read_menubar_function();

    menubar.page[function] = page;
}

uint8_t read_menubar_page()
{
    uint8_t function = read_menubar_function();

    return menubar.page[function];
}

void set_menubar_pressed(uint8_t menu_num)
{
    uint8_t function = read_menubar_function();
    uint8_t level = read_menubar_level();

    menubar.pressed[function][level] = menu_num;
}

uint8_t read_pressed_menubar()
{
    uint8_t function = read_menubar_function();
    uint8_t level = read_menubar_level();

    return menubar.pressed[function][level];
}

void function_key_event(uint8_t key_event)
{
    uint8_t function = read_menubar_function();
    uint8_t level = read_menubar_level();

    (*key_event_controller[function][level])(key_event);
}

void function_key_event_enable(uint8_t key)
{
    uint8_t function = read_menubar_function();
    uint8_t level = read_menubar_level();

    (*key_event_enable[function][level])(key);
}

void display_menubar_content(uint8_t key_event, uint8_t * vm)
{
    uint8_t function = read_menubar_function();
    uint8_t level = read_menubar_level();

    (*display_menu_content[function][level])(key_event, vm);
}

void menubar_pressed(uint8_t key_event)
{
    if (!_Area[DISPLAY_TFT_AREA5].valid)
        return;

    switch (key_event) {
        case F1_KEY_EVT:
            _Area[F1_MENUBAR_AREA].pressed   = true;
            _Area[F2_MENUBAR_AREA].pressed   = false;
            _Area[F3_MENUBAR_AREA].pressed   = false;
            _Area[F4_MENUBAR_AREA].pressed   = false;
            _Area[PREV_MENUBAR_AREA].pressed = false;
            _Area[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case F2_KEY_EVT:
            _Area[F1_MENUBAR_AREA].pressed   = false;
            _Area[F2_MENUBAR_AREA].pressed   = true;
            _Area[F3_MENUBAR_AREA].pressed   = false;
            _Area[F4_MENUBAR_AREA].pressed   = false;
            _Area[PREV_MENUBAR_AREA].pressed = false;
            _Area[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case F3_KEY_EVT:
            _Area[F1_MENUBAR_AREA].pressed   = false;
            _Area[F2_MENUBAR_AREA].pressed   = false;
            _Area[F3_MENUBAR_AREA].pressed   = true;
            _Area[F4_MENUBAR_AREA].pressed   = false;
            _Area[PREV_MENUBAR_AREA].pressed = false;
            _Area[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case F4_KEY_EVT:
            _Area[F1_MENUBAR_AREA].pressed   = false;
            _Area[F2_MENUBAR_AREA].pressed   = false;
            _Area[F3_MENUBAR_AREA].pressed   = false;
            _Area[F4_MENUBAR_AREA].pressed   = true;
            _Area[PREV_MENUBAR_AREA].pressed = false;
            _Area[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case PREV_KEY_EVT:
            _Area[F1_MENUBAR_AREA].pressed   = false;
            _Area[F2_MENUBAR_AREA].pressed   = false;
            _Area[F3_MENUBAR_AREA].pressed   = false;
            _Area[F4_MENUBAR_AREA].pressed   = false;
            _Area[PREV_MENUBAR_AREA].pressed = true;
            _Area[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;

        case NEXT_KEY_EVT:
            _Area[F1_MENUBAR_AREA].pressed   = false;
            _Area[F2_MENUBAR_AREA].pressed   = false;
            _Area[F3_MENUBAR_AREA].pressed   = false;
            _Area[F4_MENUBAR_AREA].pressed   = false;
            _Area[PREV_MENUBAR_AREA].pressed = false;
            _Area[NEXT_MENUBAR_AREA].pressed = true;
            menubar_flush_enable();
            break;

        case RELEASE:
            function_key_event_enable(F1_KEY_EVT);
            _Area[F1_MENUBAR_AREA].pressed   = false;
            _Area[F2_MENUBAR_AREA].pressed   = false;
            _Area[F3_MENUBAR_AREA].pressed   = false;
            _Area[F4_MENUBAR_AREA].pressed   = false;
            _Area[PREV_MENUBAR_AREA].pressed = false;
            _Area[NEXT_MENUBAR_AREA].pressed = false;
            menubar_flush_enable();
            break;
    }
}

void display_area1_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_TFT_AREA1](vm);

    if (_Area[DISPLAY_TFT_AREA1].refer) {
        _Area[DISPLAY_BATTERY_AREA].refer = true;
        _Area[DISPLAY_BLUETOOTH_AREA].refer = true;
        _Area[DISPLAY_POWER_OFF_TIMER_AREA].refer = true;
        _Area[DISPLAY_TRUMPET_AREA].refer = true;
        _Area[DISPLAY_LIGHTING_AREA].refer = true;
        _Area[DISPLAY_REAL_TIME_AREA].refer = true;
    }

    display_battery_flush(vm);
    display_bluetooth_flush(vm);
    display_power_off_timer_flush(vm);
    display_trumpet_flush(vm);
    display_lighting_flush(vm);
    display_real_time_flush(vm);

    _Area[DISPLAY_BATTERY_AREA].refer = false;
    _Area[DISPLAY_BLUETOOTH_AREA].refer = false;
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].refer = false;
    _Area[DISPLAY_TRUMPET_AREA].refer = false;
    _Area[DISPLAY_LIGHTING_AREA].refer = false;
    _Area[DISPLAY_REAL_TIME_AREA].refer = false;
}

void display_area1_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA1].valid)
        _Area[DISPLAY_TFT_AREA1].refer = true;
}

void display_battery_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_BATTERY_AREA](vm);
    _Area[DISPLAY_BATTERY_AREA].refer = false;
}

void battery_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA1].valid)
        _Area[DISPLAY_BATTERY_AREA].refer = true;
}

void display_bluetooth_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_BLUETOOTH_AREA](vm);
    _Area[DISPLAY_BLUETOOTH_AREA].refer = false;
}

void display_power_off_timer_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_POWER_OFF_TIMER_AREA](vm);
    _Area[DISPLAY_POWER_OFF_TIMER_AREA].refer = false;
}

void display_trumpet_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_TRUMPET_AREA](vm);
    _Area[DISPLAY_TRUMPET_AREA].refer = false;
}

void display_lighting_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_LIGHTING_AREA](vm);
    _Area[DISPLAY_LIGHTING_AREA].refer = false;
}

void display_real_time_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_REAL_TIME_AREA](vm);
    _Area[DISPLAY_REAL_TIME_AREA].refer = false;
}

void display_area2_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_TFT_AREA2](vm);

    if (_Area[DISPLAY_TFT_AREA2].refer) {
        _Area[MEASURE_VALUE_MODE_AREA].refer = true;
        _Area[DISPLAY_RECORDING_AREA].refer = true;
        _Area[DISPLAY_HOLD_AREA].refer = true;
        _Area[MEASURE_RELATIVE_VALUE_AREA].refer = true;
    }

    display_measure_value_mode_flush(vm);
    display_recording_flush(vm);
    display_hold_flush(vm);
    display_relative_value_flush(vm);

    _Area[MEASURE_VALUE_MODE_AREA].refer = false;
    _Area[DISPLAY_RECORDING_AREA].refer = false;
    _Area[DISPLAY_HOLD_AREA].refer = false;
    _Area[MEASURE_RELATIVE_VALUE_AREA].refer = false;
}

void display_area2_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA2].valid)
        _Area[DISPLAY_TFT_AREA2].refer = true;
}

void display_measure_value_mode_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_VALUE_MODE_AREA](vm);
    _Area[MEASURE_VALUE_MODE_AREA].refer = false;
}

void display_recording_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_RECORDING_AREA](vm);
    _Area[DISPLAY_RECORDING_AREA].refer = false;
}

void display_hold_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_HOLD_AREA](vm);
    _Area[DISPLAY_HOLD_AREA].refer = false;
}

void display_relative_value_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_RELATIVE_VALUE_AREA](vm);
    _Area[MEASURE_RELATIVE_VALUE_AREA].refer = false;
}

void display_area3_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_TFT_AREA3](vm);

    if (_Area[DISPLAY_TFT_AREA3].refer) {
        _Area[MEASURE_VALUE_AREA].refer = true;
        _Area[MEASURE_VALUE_UNIT_AREA].refer = true;
    }

    display_measure_value_flush(vm);
    display_measure_value_unit_flush(vm);

    _Area[MEASURE_VALUE_AREA].refer = false;
    _Area[MEASURE_VALUE_UNIT_AREA].refer = false;
}

void display_area3_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA3].valid)
        _Area[DISPLAY_TFT_AREA3].refer = true;
}

void display_measure_value_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_VALUE_AREA](vm);
    _Area[MEASURE_VALUE_AREA].refer = false;
}

void measure_value_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA3].valid)
        _Area[MEASURE_VALUE_AREA].refer = true;
}

void display_measure_value_unit_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_VALUE_UNIT_AREA](vm);
    _Area[MEASURE_VALUE_UNIT_AREA].refer = false;
}

void display_area4_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_TFT_AREA4](vm);

    if (_Area[DISPLAY_TFT_AREA4].refer) {
        _Area[MEASURE_LO_AREA].refer = true;
        _Area[MEASURE_LOZ_AREA].refer = true;
        _Area[MEASURE_RULER_AREA].refer = true;
        _Area[MEASURE_RANGE_STATUS_AREA].refer = true;
    }

    display_measure_lo_flush(vm);
    display_measure_loz_flush(vm);
    display_measure_ruler_flush(vm);
    display_measure_range_status_flush(vm);

    _Area[MEASURE_LO_AREA].refer = false;
    _Area[MEASURE_LOZ_AREA].refer = false;
    _Area[MEASURE_RULER_AREA].refer = false;
    _Area[MEASURE_RANGE_STATUS_AREA].refer = false;
}

void display_area4_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA4].valid)
        _Area[DISPLAY_TFT_AREA4].refer = true;
}

void display_measure_lo_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_LO_AREA](vm);
    _Area[MEASURE_LO_AREA].refer = false;
}

void display_measure_loz_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_LOZ_AREA](vm);
    _Area[MEASURE_LOZ_AREA].refer = false;
}

void display_measure_ruler_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_RULER_AREA](vm);
    _Area[MEASURE_RULER_AREA].refer = false;
}

void display_measure_range_status_flush(uint8_t * vm)
{
    display_widget_show[MEASURE_RANGE_STATUS_AREA](vm);
    _Area[MEASURE_RANGE_STATUS_AREA].refer = false;
}

void display_area5_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_TFT_AREA5](vm);

    if (_Area[DISPLAY_TFT_AREA5].refer) {
        _Area[F1_MENUBAR_AREA].refer = true;
        _Area[F2_MENUBAR_AREA].refer = true;
        _Area[F3_MENUBAR_AREA].refer = true;
        _Area[F4_MENUBAR_AREA].refer = true;
        _Area[PREV_MENUBAR_AREA].refer = true;
        _Area[NEXT_MENUBAR_AREA].refer = true;
    }

    display_f1_menubar_flush(vm);
    display_f2_menubar_flush(vm);
    display_f3_menubar_flush(vm);
    display_f4_menubar_flush(vm);
    display_prev_menubar_flush(vm);
    display_next_menubar_flush(vm);

    _Area[F1_MENUBAR_AREA].refer = false;
    _Area[F2_MENUBAR_AREA].refer = false;
    _Area[F3_MENUBAR_AREA].refer = false;
    _Area[F4_MENUBAR_AREA].refer = false;
    _Area[PREV_MENUBAR_AREA].refer = false;
    _Area[NEXT_MENUBAR_AREA].refer = false;
}

void display_area5_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA5].valid)
        _Area[DISPLAY_TFT_AREA5].refer = true;
}

void display_f1_menubar_flush(uint8_t * vm)
{
    display_widget_show[F1_MENUBAR_AREA](vm);
    _Area[F1_MENUBAR_AREA].refer = false;
}

void display_f2_menubar_flush(uint8_t * vm)
{
    display_widget_show[F2_MENUBAR_AREA](vm);
    _Area[F2_MENUBAR_AREA].refer = false;
}

void display_f3_menubar_flush(uint8_t * vm)
{
    display_widget_show[F3_MENUBAR_AREA](vm);
    _Area[F3_MENUBAR_AREA].refer = false;
}

void display_f4_menubar_flush(uint8_t * vm)
{
    display_widget_show[F4_MENUBAR_AREA](vm);
    _Area[F4_MENUBAR_AREA].refer = false;
}

void display_prev_menubar_flush(uint8_t * vm)
{
    display_widget_show[PREV_MENUBAR_AREA](vm);
    _Area[PREV_MENUBAR_AREA].refer = false;
}

void display_next_menubar_flush(uint8_t * vm)
{
    display_widget_show[NEXT_MENUBAR_AREA](vm);
    _Area[NEXT_MENUBAR_AREA].refer = false;
}

void menubar_flush_enable()
{
    if (_Area[DISPLAY_TFT_AREA5].valid)
        _Area[DISPLAY_TFT_AREA5].refer = true;
}

static void measure_interface(uint8_t * vm)
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

    // _Area[DISPLAY_TFT_AREA1].refer = false;
    // _Area[DISPLAY_TFT_AREA2].refer = false;
    // _Area[DISPLAY_TFT_AREA3].refer = false;
    // _Area[DISPLAY_TFT_AREA4].refer = false;
    // _Area[DISPLAY_TFT_AREA5].refer = false;
    // _Area[SETTING_PAGE_AREA].refer = false;
}

void display_setting_area2_flush(uint8_t * vm)
{
    display_widget_show[DISPLAY_SETTING_AREA2](vm);

    if (_Area[DISPLAY_SETTING_AREA2].refer) {
        _Area[SETTING_LIST_AREA].refer = true;
    }

    display_setting_list_flush(vm);

    _Area[SETTING_LIST_AREA].refer = false;
}

void display_setting_area2_flush_enable()
{
    if (_Area[DISPLAY_SETTING_AREA2].valid)
        _Area[DISPLAY_SETTING_AREA2].refer = true;
}

void display_setting_list_flush(uint8_t * vm)
{
    display_widget_show[SETTING_LIST_AREA](vm);
    _Area[SETTING_LIST_AREA].refer = false;
}

static void setting_interface(uint8_t * vm)
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

    // _Area[DISPLAY_TFT_AREA1].refer = false;
    // _Area[DISPLAY_TFT_AREA2].refer = false;
    // _Area[DISPLAY_TFT_AREA3].refer = false;
    // _Area[DISPLAY_TFT_AREA4].refer = false;
    // _Area[DISPLAY_TFT_AREA5].refer = false;
    // _Area[SETTING_PAGE_AREA].refer = false;
}

void display_flush(uint8_t * vm)
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

void tft_clear(uint8_t color)
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
 * _Area[PREV_MENUBAR_AREA].set_y  = 215;
 * _Area[PREV_MENUBAR_AREA].set_x  = 4;
 * _Area[PREV_MENUBAR_AREA].width  = 15;
 * _Area[PREV_MENUBAR_AREA].height = 24;
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
 * _Area[PREV_MENUBAR_AREA].set_y  = 215;
 * _Area[PREV_MENUBAR_AREA].set_x  = 4;
 * _Area[PREV_MENUBAR_AREA].width  = 15;
 * _Area[PREV_MENUBAR_AREA].height = 24;
 */

void tft_flush_area(uint8_t area_num, uint8_t * vm)
{
    unsigned int area_y;
    unsigned int area_x;
    unsigned int area_width;
    unsigned int area_height;
    unsigned int area_yend;

    uint8_t color;
    uint8_t * arr;

    if (area_num == 0) {
        area_y      = _Area[DISPLAY_TFT_AREA1].set_y;
        area_x      = _Area[DISPLAY_TFT_AREA1].set_x;
        area_width  = _Area[DISPLAY_TFT_AREA1].width;
        area_height = _Area[DISPLAY_TFT_AREA1].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 1) {
        area_y      = _Area[DISPLAY_TFT_AREA2].set_y;
        area_x      = _Area[DISPLAY_TFT_AREA2].set_x;
        area_width  = _Area[DISPLAY_TFT_AREA2].width;
        area_height = _Area[DISPLAY_TFT_AREA2].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 2) {
        area_y      = _Area[DISPLAY_TFT_AREA3].set_y;
        area_x      = _Area[DISPLAY_TFT_AREA3].set_x;
        area_width  = _Area[DISPLAY_TFT_AREA3].width;
        area_height = _Area[DISPLAY_TFT_AREA3].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 3) {
        area_y      = _Area[DISPLAY_TFT_AREA4].set_y;
        area_x      = _Area[DISPLAY_TFT_AREA4].set_x;
        area_width  = _Area[DISPLAY_TFT_AREA4].width;
        area_height = _Area[DISPLAY_TFT_AREA4].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 4) {
        area_y      = _Area[DISPLAY_TFT_AREA5].set_y;
        area_x      = _Area[DISPLAY_TFT_AREA5].set_x;
        area_width  = _Area[DISPLAY_TFT_AREA5].width;
        area_height = _Area[DISPLAY_TFT_AREA5].height;
        area_yend   = area_y + area_height;
    } else if (area_num == 5) {
        area_y      = _Area[DISPLAY_SETTING_AREA2].set_y;
        area_x      = _Area[DISPLAY_SETTING_AREA2].set_x;
        area_width  = _Area[DISPLAY_SETTING_AREA2].width;
        area_height = _Area[DISPLAY_SETTING_AREA2].height;
        area_yend   = area_y + area_height;
    }

    tft_region(area_y, area_x, area_width, area_height);

    uint8_t theme = equip.themecolor * COLOR_MAX;

    for (unsigned int y = area_y; y < area_yend; y++) {
        for (unsigned int x = 0; x < area_width; x++) {
            tft_write(color_data[vm[y * TFT_WIDTH + x] + theme]);
        }
    }
}

void tft_flush(uint8_t * vm)
{
    uint8_t current_function;
    current_function = read_menubar_function();

    if (_Area[DISPLAY_TFT_AREA1].refer) {
        tft_flush_area(0, vm);
        _Area[DISPLAY_TFT_AREA1].refer = false;
    }

    if (_Area[DISPLAY_TFT_AREA2].refer && (current_function != DMM_SETTING)) {
        tft_flush_area(1, vm);
        _Area[DISPLAY_TFT_AREA2].refer = false;
    }

    if (_Area[DISPLAY_TFT_AREA3].refer && (current_function != DMM_SETTING)) {
        tft_flush_area(2, vm);
        _Area[DISPLAY_TFT_AREA3].refer = false;
    }

    if (_Area[DISPLAY_TFT_AREA4].refer && (current_function != DMM_SETTING)) {
        tft_flush_area(3, vm);
        _Area[DISPLAY_TFT_AREA4].refer = false;
    }

    if (_Area[DISPLAY_TFT_AREA5].refer) {
        tft_flush_area(4, vm);
        _Area[DISPLAY_TFT_AREA5].refer = false;
    }

    if (_Area[DISPLAY_SETTING_AREA2].refer && (current_function == DMM_SETTING)) {
        tft_flush_area(5, vm);
        _Area[DISPLAY_SETTING_AREA2].refer = false;
    }
}
