
#include "setup.h"

struct equip_param_t equip = {
    {
        .hour     = 8,
        .minute   = 16,
        .second   = 0,
    },

    {
        .year     = 2021,
        .month    = 10,
        .day      = 26,
    },

    .apo_time     = 1,
    .comp_max     = 2010,
    .comp_min     = 2020,
    .comp_type    = 0,
    .record_rate  = 10,
    .memory_mode  = 0,
    .back_light   = 10,
    .light_time   = 1,
    .sound_status = true,
    .themecolor   = 0,
};

struct set_item_list list = {
    .vpos         = 0,
    .hpos         = 0,
    .page         = 0,
    .param_number = 0,
    .subitem      = {3, 3, 1, 1, 1,1, 1, 1, 1, 1, 1},
};

void vpos_selected(char incr)
{
    list.param_number += incr;

    if (list.param_number < PARAM_DOCK_MAX)
        page_selected(0);
    else
        page_selected(1);

    if (list.param_number > PARAM_NUM_MAX - 1) {
        list.param_number = 0;
        page_selected(0);
    }
    if (list.param_number < 0) {
        list.param_number = PARAM_NUM_MAX - 1; 
        page_selected(1);
    }

    list.vpos = list.param_number % PARAM_DOCK_MAX;
    hpos_selected(0);
}

unsigned char get_vpos_selected()
{
    return list.vpos;
}

unsigned char get_param_number()
{
    return list.param_number;
}

void hpos_selected(char incr)
{
    list.hpos += incr;
    if (list.hpos > list.subitem[get_param_number()] - 1)
        list.hpos = 0;
    if (list.hpos < 0)
        list.hpos = list.subitem[get_param_number()] - 1;
}

unsigned char get_hpos_selected()
{
    return list.hpos;
}

void page_selected(char incr)
{
    list.page = incr;
}

unsigned char get_page_selected()
{
    return list.page;
}

void set_equip_time(char incr)
{
    if (get_param_number() != SETUP_RTC_TIME)
        return;
    if (get_hpos_selected() == 0) {
        equip.time.hour += incr;
        if (equip.time.hour > HOUR_MAX)
            equip.time.hour = HOUR_MIN;
        if (equip.time.hour < HOUR_MIN)
            equip.time.hour = HOUR_MAX;
    }

    if (get_hpos_selected() == 1) {
        equip.time.minute += incr;
        if (equip.time.minute > MINUTE_MAX)
            equip.time.minute = MINUTE_MIN;
        if (equip.time.minute < MINUTE_MIN)
            equip.time.minute = MINUTE_MAX;
    }

    if (get_hpos_selected() == 2) {
        equip.time.second += incr;
        if (equip.time.second > SECOND_MAX)
            equip.time.second = SECOND_MIN;
        if (equip.time.second < SECOND_MIN)
            equip.time.second = SECOND_MAX;
    }
}

void set_equip_date(char incr)
{
    if (get_param_number() != SETUP_RTC_DATE)
        return;
    if (get_hpos_selected() == 0) {
        equip.date.year += incr;
        if (equip.date.year > YEAR_MAX)
            equip.date.year = YEAR_MIN;
        if (equip.date.year < YEAR_MIN)
            equip.date.year = YEAR_MAX;
    }

    if (get_hpos_selected() == 1) {
        equip.date.month += incr;
        if (equip.date.month > MONTH_MAX)
            equip.date.month = MONTH_MIN;
        if (equip.date.month < MONTH_MIN)
            equip.date.month = MONTH_MAX;

        if (equip.date.day > check_month_day(equip.date.year, equip.date.month))
            equip.date.day = DAY_MIN;
        if (equip.date.day < DAY_MIN)
            equip.date.day = check_month_day(equip.date.year, equip.date.month);
    }

    if (get_hpos_selected() == 2) {
        equip.date.day += incr;
        if (equip.date.day > check_month_day(equip.date.year, equip.date.month))
            equip.date.day = DAY_MIN;
        if (equip.date.day < DAY_MIN)
            equip.date.day = check_month_day(equip.date.year, equip.date.month);
    }
}

void set_apo_time(char incr)
{
    if (get_param_number() != SETUP_APO_TIME)
        return;
    equip.apo_time += incr;
    if (equip.apo_time > 5)
        equip.apo_time = 0;
    if (equip.apo_time < 0)
        equip.apo_time = 5;
}

void set_comp_type(char incr)
{
    if (get_param_number() != SETUP_COMP_TYPE)
        return;
    equip.comp_type += incr;
    if (equip.comp_type > 1)
        equip.comp_type = 0;
    if (equip.comp_type < 0)
        equip.comp_type = 1;
}

void set_record_rate(char incr)
{
    if (get_param_number() != SETUP_RECORD_RATE)
        return;
    equip.record_rate += incr;
    if (equip.record_rate > 10)
        equip.record_rate = 1;
    if (equip.record_rate < 1)
        equip.record_rate = 10;
}

void set_memory_mode(char incr)
{
    if (get_param_number() != SETUP_MEMORY_MODE)
        return;
    equip.memory_mode += incr;
    if (equip.memory_mode > 1)
        equip.memory_mode = 0;
    if (equip.memory_mode < 0)
        equip.memory_mode = 1;
}

void set_back_light(char incr)
{
    if (get_param_number() != SETUP_BACK_LIGHT)
        return;
    equip.back_light += incr;
    if (equip.back_light > 10)
        equip.back_light = 1;
    if (equip.back_light < 1)
        equip.back_light = 10;
}

void set_light_time(char incr)
{
    if (get_param_number() != SETUP_LIGHT_TIME)
        return;
    equip.light_time += incr;
    if (equip.light_time > 4)
        equip.light_time = 0;
    if (equip.light_time < 0)
        equip.light_time = 4;
}

void set_sound_status(char incr)
{
    if (get_param_number() != SETUP_SOUND)
        return;
    equip.sound_status += incr;
    if (equip.sound_status > 1)
        equip.sound_status = 0;
    if (equip.sound_status < 0)
        equip.sound_status = 1;
}

void set_theme_color(char incr)
{
    if (get_param_number() != SETUP_THEMECOLOR)
        return;
    equip.themecolor += incr;
    if (equip.themecolor > 1)
        equip.themecolor = 0;
    if (equip.themecolor < 0)
        equip.themecolor = 1;
}

unsigned char * get_hour()
{
    sprintf(equip.display, "%02d", equip.time.hour);
    return equip.display;
}

unsigned char * get_minute()
{
    sprintf(equip.display, "%02d", equip.time.minute);
    return equip.display;
}

unsigned char * get_second()
{
    sprintf(equip.display, "%02d", equip.time.second);
    return equip.display;
}

unsigned char * get_year()
{
    sprintf(equip.display, "%04d", equip.date.year);
    return equip.display;
}

unsigned char * get_month()
{
    sprintf(equip.display, "%02d", equip.date.month);
    return equip.display;
}

unsigned char * get_day()
{
    sprintf(equip.display, "%02d", equip.date.day);
    return equip.display;
}

unsigned char * get_real_time()
{
    /**
     * if (read_menubar_function() != DMM_SETTING) {
     *     equip.time.hour   = get_rtc_hour();
     *     equip.time.minute = get_rtc_minute();
     *     equip.time.second = get_rtc_second();
     *     equip.date.year   = get_rtc_year() + RTC_BASE;
     *     equip.date.month  = get_rtc_month();
     *     equip.date.day    = get_rtc_day();
     * } else if (
     *     (read_menubar_function() == DMM_SETTING) && (
     *     (get_param_number() != SETUP_RTC_TIME) && 
     *     (get_param_number() != SETUP_RTC_DATE))
     * ) {
     *     sprintf(equip.display, TIME_FORMAT,
     *         get_rtc_year() + RTC_BASE,
     *         get_rtc_month(),
     *         get_rtc_day(),
     *         get_rtc_hour(),
     *         get_rtc_minute(),
     *         get_rtc_second());
     *
     *     return equip.display;
     * }
     */

    sprintf(equip.display, TIME_FORMAT,
        equip.date.year,
        equip.date.month,
        equip.date.day,
        equip.time.hour,
        equip.time.minute,
        equip.time.second);

    return equip.display;
}

unsigned char get_apo_time()
{
    return equip.apo_time;
}

unsigned char * get_comp_max()
{
    sprintf(equip.display, "%d", equip.comp_max);
    return equip.display;
}

unsigned int get_comp_max_value()
{
    return equip.comp_max;
}

unsigned char * get_comp_min()
{
    sprintf(equip.display, "%d", equip.comp_min);
    return equip.display;
}

unsigned int get_comp_min_value()
{
    return equip.comp_min;
}

unsigned char get_comp_type()
{
    return equip.comp_type;
}

unsigned char * get_record_rate()
{
    sprintf(equip.display, "%d", equip.record_rate);
    return equip.display;
}

unsigned char get_memory_mode()
{
    return equip.memory_mode;
}

unsigned char * get_back_light()
{
    sprintf(equip.display, "%d", equip.back_light * 10);
    return equip.display;
}

unsigned char get_light_time()
{
    return equip.light_time;
}

unsigned char get_sound_status()
{
    return equip.sound_status;
}

unsigned char get_theme_color()
{
    return equip.themecolor;
}

unsigned char check_leap_year(unsigned int year)
{
    if (((year % 4 == 0) && (year % 100 != 0)) || ((year % 400) == 0))
        return true;
    return false;
    /**
     * if ((year % 400) == 0)
     *     return true;
     * else {
     *     if ((year % 4 == 0) && (year % 100 != 0))
     *         return true;
     *     else
     *         return false;
     * }
     */
}

unsigned char check_month_day(unsigned int year, unsigned char month)
{
    const unsigned char month_day[12] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31,
    };

    if (month > 12)
        return 0;
    if (month == 2)
        return month_day[month - 1] + check_leap_year(year);
    return month_day[month - 1];
}
