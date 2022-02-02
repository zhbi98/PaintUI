
#ifndef __SETUP_H__
#define __SETUP_H__

#include <stdbool.h>

#include "log.h"
#include "key_controller.h"
#include "display_controller.h"

#define RTC_BASE    2000

#define YEAR_MAX    2099
#define YEAR_MIN    2000
#define MONTH_MAX   12
#define MONTH_MIN   1
#define DAY_MAX     30
#define DAY_MIN     1

#define HOUR_MAX    23
#define HOUR_MIN    0
#define MINUTE_MAX  59
#define MINUTE_MIN  0
#define SECOND_MAX  59
#define SECOND_MIN  0

#define TIME_FORMAT "%04d/%02d/%02d  %02d:%02d:%02d"

#define MINUTE_7200 (7200 * 60 * 2) // 500ms
#define MINUTE_15   (15   * 60 * 2) // 500ms
#define MINUTE_30   (30   * 60 * 2) // 500ms
#define MINUTE_60   (60   * 60 * 2) // 500ms
#define MINUTE_120  (120  * 60 * 2) // 500ms
#define MINUTE_180  (180  * 60 * 2) // 500ms

struct rtc_time_t {
    char hour;
    char minute;
    char second;
};

struct rtc_date_t {
    int year;
    char month;
    char day;
};

enum equip_setup_type {
    SETUP_RTC_TIME    = 0,
    SETUP_RTC_DATE    = 1,
    SETUP_APO_TIME    = 2,
    SETUP_COMP_MAX    = 3,
    SETUP_COMP_MIN    = 4,
    SETUP_COMP_TYPE   = 5,
    SETUP_RECORD_RATE = 6,
    SETUP_MEMORY_MODE = 7,
    SETUP_BACK_LIGHT  = 8,
    SETUP_LIGHT_TIME  = 9,
    SETUP_SOUND       = 10,
    SETUP_THEMECOLOR  = 11,

    PARAM_NUM_MAX     = 12,
    PARAM_DOCK_MAX    = 8,
};

struct equip_param_t {
    struct rtc_time_t time;
    struct rtc_date_t date;
    char apo_time; // auto power off time
    int comp_max;
    int comp_min;
    char comp_type;
    char record_rate;
    char memory_mode;
    char back_light;
    char light_time;
    char sound_status;
    char themecolor;
    unsigned char display[32];
};

struct set_item_list {
    char vpos;
    char hpos;
    char page;
    char param_number;
    const unsigned char subitem[PARAM_NUM_MAX];
};

extern struct equip_param_t equip;
extern struct set_item_list list;

extern void vpos_selected(char incr);
extern unsigned char get_vpos_selected();
extern unsigned char get_param_number();

extern void hpos_selected(char incr);
extern unsigned char get_hpos_selected();

extern void page_selected(char incr);
extern unsigned char get_page_selected();

extern void set_equip_time(char incr);
extern void set_equip_date(char incr);
extern void set_apo_time(char incr);
extern void set_comp_type(char incr);
extern void set_record_rate(char incr);
extern void set_memory_mode(char incr);
extern void set_back_light(char incr);
extern void set_light_time(char incr);
extern void set_sound_status(char incr);
extern void set_theme_color(char incr);

extern unsigned char * get_hour();
extern unsigned char * get_minute();
extern unsigned char * get_second();
extern unsigned char * get_year();
extern unsigned char * get_month();
extern unsigned char * get_day();
extern unsigned char * get_real_time();
extern unsigned char   get_apo_time();
extern unsigned char * get_comp_max();
extern unsigned char * get_comp_min();
extern unsigned char   get_comp_type();
extern unsigned char * get_record_rate();
extern unsigned char   get_memory_mode();
extern unsigned char * get_back_light();
extern unsigned char   get_light_time();
extern unsigned char   get_sound_status();
extern unsigned char   get_theme_color();

extern unsigned char check_leap_year(unsigned int year);
extern unsigned char check_month_day(unsigned int year, unsigned char month);

#endif
