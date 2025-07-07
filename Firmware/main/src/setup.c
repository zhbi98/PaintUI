/**
 * @file setup.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "display_controller.h"
#include "key_controller.h"
#include "setup.h"

/*********************
 *      DEFINES
 *********************/

#define LIST_VIEW_MAX 8U

#define MAT_MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAT_MAX(a, b) ((a) > (b) ? (a) : (b))

#define _MAP1(a, min, max) ((a) < (min) ? (max) : (a))
#define _MAP2(a, min, max) ((a) > (max) ? (min) : (a))

#define _SEC(x) ((x) * 1U)
#define _MIN(x) ((x) * _SEC(60U))

/**********************
 *      TYPEDEFS
 **********************/

_devset_t _devset = {0};

const _devset_t _devset_def = {
    .head = {
        ".SYS."
    },

    .time = {
        12, 1, 1,
    },

    .date = {
        2024, 10, 1, 0,
    },

    .apo_time = 1,

    .comp = {
        20000, 10000, 0,
    },

    .contval = 20,

    .record = {
        10, 100,
    },

    .display = {
        3, 1,
    },

    .memMod = 1,

    .voice = {
        true, 5,
    },

    .devdsc = 0,
    
    .torch_light_off = 3,
    .key_light_off = 0,
    .display_off = 4,

    .ssid = {
        ".Bin-SYS"
    },
};


static list_view_t listview = {
    .h_cnt = {3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    .v_idx = 0,
    .h_idx = 0,
    .page = 0,
    .opti_id = 0,
};

/**********************
 *  STATIC VARIABLES
 **********************/

static _devset_t _verify_devset = {0};
static uint8_t monday(uint16_t y, uint8_t m);
static bool isleap(uint16_t year);
static void verify_time_up();
static void date_refer();
static void time_refer();

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * A content observer to see if the data has changed, 
 * returning an error if the content is different 
 * from the original, or the correct result.
 * @param p1 pointer to the source data.
 * @param p2 pointer to the verify data.
 * @param n data size.
 * @return ture or false.
 */
static bool verify(void * p1, void * p2, uint32_t n)
{
    uint8_t * data_p1 = (uint8_t *)p1;
    uint8_t * data_p2 = (uint8_t *)p2;

    for (uint32_t i = 0; i < n; i++)
        if (data_p1[i] != data_p2[i])
            return false;
    return true;
}

/*==============================
 * Option to modify the value
 *=============================*/

/**
 * Gets the number of days that the specified month contains.
 * @param y year, specified year if leap year.
 * @param m month, specified month.
 * @return day number of month.
 */
static uint8_t monday(uint16_t y, uint8_t m)
{
    const uint8_t day[12] = {31, 28, 31, 
    30, 31, 30, 31, 31, 30, 31, 30, 31};

    uint8_t leap = isleap(y);
    uint8_t _day = day[m - 1];

    if (m != 2) return _day;
    else return _day + leap;
}

/**
 * Determines whether the specified year is a leap year.
 * @param year, specified year if leap year.
 * @return determines result.
 */
static bool isleap(uint16_t year)
{
    if (!(year % 400)) return true;
    if (year % 4) return false;
    if (!(year % 100)) return false;
    return true;
}

/**
 * Activate a child view under the device settings view.
 * @param _tabvidx tabview card index.
 */
void lv_tab_set_line(int8_t val)
{
    listview.opti_id += val;

    if (listview.opti_id > DEV_CTL_MAX - 1)
        listview.opti_id = 0;

    listview.opti_id = \
        _MAP1(listview.opti_id, 
            0, DEV_CTL_MAX - 1);

    listview.opti_id = \
        _MAP2(listview.opti_id, 
            0, DEV_CTL_MAX - 1);

    listview.page = \
        listview.opti_id / LIST_VIEW_MAX;

    listview.v_idx = \
        listview.opti_id % LIST_VIEW_MAX;

    listview.h_idx = 0;
}

/**
 * Activate a child option under the device settings view.
 * @param _optidx card options index.
 */
void lv_tab_set_hidx(int8_t val)
{
    uint16_t opti_id = lv_tab_get_opti_id();
    uint16_t h_cnt = listview.h_cnt[opti_id];

    listview.h_idx += val;

    listview.h_idx = \
        _MAP1(listview.h_idx, 
            0, h_cnt - 1);

    listview.h_idx = \
        _MAP2(listview.h_idx, 
            0, h_cnt - 1);
}

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return tabview card index result.
 */
uint8_t lv_tab_get_line_id()
{
    return listview.v_idx;
}

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return index of the current page options.
 */
uint8_t lv_tab_get_opti_id()
{
    return listview.opti_id;
}

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return index of the current option part.
 */
uint8_t lv_tab_get_hidx()
{
    return listview.h_idx;
}

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return index of the current option part.
 */
uint8_t lv_tab_get_page_id()
{
    return listview.page;
}

/**
 * Adds or subtracts a value from the specified 
 * part of the date value.
 */
void lv_date_set_val(int8_t val)
{
    uint8_t opt_idx = lv_tab_get_opti_id();
    uint8_t hidx = lv_tab_get_hidx();
    uint8_t _tran = lv_date_tran_get_val();

    if (opt_idx != DEV_DATE) return;

    int16_t year = _devset.date.year;
    int8_t month = _devset.date.month;
    int8_t day = _devset.date.day;

    uint8_t max = monday(year, month);

    if (!_tran) {
        switch (hidx) {
        case 0:
            year += val;
            year = _MAP1(year, 2000, 2099);
            year = _MAP2(year, 2000, 2099);

            max = monday(year, month);
            day = MAT_MAX(day, 1);
            day = MAT_MIN(day, max);
            break;
        case 1:
            month += val;
            month = _MAP1(month, 1, 12);
            month = _MAP2(month, 1, 12);

            max = monday(year, month);
            day = MAT_MAX(day, 1);
            day = MAT_MIN(day, max);
            break;
        case 2:
            day += val;
            day = _MAP1(day, 1, max);
            day = _MAP2(day, 1, max);
            break;
        }
    } else {
        switch (hidx) {
        case 0:
            day += val;
            day = _MAP1(day, 1, max);
            day = _MAP2(day, 1, max);
            break;
        case 1:
            month += val;
            month = _MAP1(month, 1, 12);
            month = _MAP2(month, 1, 12);

            max = monday(year, month);
            day = MAT_MAX(day, 1);
            day = MAT_MIN(day, max);
            break;
        case 2:
            year += val;
            year = _MAP1(year, 2000, 2099);
            year = _MAP2(year, 2000, 2099);

            max = monday(year, month);
            day = MAT_MAX(day, 1);
            day = MAT_MIN(day, max);
            break;
        }
    }

    _devset.date.year = year;
    _devset.date.month = month;
    _devset.date.day = day;

    date_refer();
}

/**
 * Adds or subtracts a value from the specified 
 * part of the time value.
 */
void lv_time_set_val(int8_t val)
{
    uint8_t opt_idx = lv_tab_get_opti_id();
    uint8_t hidx = lv_tab_get_hidx();

    if (opt_idx != DEV_TIM) return;

    int8_t hour = _devset.time.hour;
    int8_t min = _devset.time.min;
    int8_t sec = _devset.time.sec;

    uint8_t _min = 0;
    uint8_t _max = 23;

    switch (hidx) {
    case 0:
        hour += val;
        hour = _MAP1(hour, _min, _max);
        hour = _MAP2(hour, _min, _max);
        break;
    case 1:
        min += val;
        min = _MAP1(min, 0, 59);
        min = _MAP2(min, 0, 59);
        break;
    case 2:
        sec += val;
        sec = _MAP1(sec, 0, 59);
        sec = _MAP2(sec, 0, 59);
        break;
    }

    _devset.time.hour = hour;
    _devset.time.min = min;
    _devset.time.sec = sec;

    time_refer();
}

/**
 * Adds or subtracts a value from the specified 
 * part of the date's tran switch value.
 */
void lv_tran_set_val(int8_t val)
{
    uint8_t opt_idx = lv_tab_get_opti_id();
    uint8_t hidx = lv_tab_get_hidx();

    if (opt_idx != DEV_DATE_TRAN) return;

    int8_t tran = _devset.date.tran;

    tran += val;

    tran = _MAP1(tran, 0, 1);
    tran = _MAP2(tran, 0, 1);

    _devset.date.tran = tran;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_apoff_set_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_APOFF) return;
    int16_t _val = _devset.apo_time;

    _val += val;

    _val = _MAP1(_val, 0, 4);
    _val = _MAP2(_val, 0, 4);

    _devset.apo_time = _val;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_bright_set_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_BRIGHT) return;
    int16_t _val = _devset.display.bright;

    _val += val;

    _val = _MAP1(_val, 0, 3);
    _val = _MAP2(_val, 0, 3);

    _devset.display.bright = _val;

    if (_val != 0) {
        /*hal_fpga_spi_write(0x2001, 
            _val * 650);*/
    }
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_voice_set_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_VOICE) return;
    uint8_t hidx = lv_tab_get_hidx();
    int16_t _val = 0;

    switch (hidx) {
    case 0:
        _val = _devset.voice.state;
        _val += val;
        
        _val = _MAP1(_val, 0, 1);
        _val = _MAP2(_val, 0, 1);

        _devset.voice.state = _val;
        if (_val) {/*set_beep(1, 3, 1);*/}
        break;
    case 1:
        _val = _devset.voice.vol;
        _val += val;

        _val = _MAP1(_val, 1, 5);
        _val = _MAP2(_val, 1, 5);

        _devset.voice.vol = _val;
        /*set_beep_volume(_val * 10);*/
        break;
    }
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_dark_set_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_DARK) return;
    int16_t _val = _devset.display.dark;

    _val += val;

    _val = _MAP1(_val, 0, 2);
    _val = _MAP2(_val, 0, 2);

    _devset.display.dark = _val;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_comp_set_type_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_COMP_TYPE) return;
    int16_t _val = _devset.comp.type;

    _val += val;

    _val = _MAP1(_val, 0, 1);
    _val = _MAP2(_val, 0, 1);

    _devset.comp.type = _val;
    /*dev_comp_init();*/
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_record_set_val(uint16_t nr, uint32_t tim)
{
    tim = _MAP1(tim, 1, 20000);
    tim = _MAP2(tim, 1, 20000);
    _devset.record.rate = tim;

    nr = _MAP1(nr, 1, 10000);
    nr = _MAP2(nr, 1, 10000);
    _devset.record.nr = nr;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_mem_set_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_MEM) return;
    int16_t _val = _devset.memMod;

    _val += val;

    _val = _MAP1(_val, 0, 1);
    _val = _MAP2(_val, 0, 1);

    _devset.memMod = _val;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_dispoff_set_val(int8_t val)
{
    if (lv_tab_get_opti_id() != DEV_DISP_OFF) return;
    int16_t _val = _devset.display_off;

    _val += val;

    _val = _MAP1(_val, 0, 3);
    _val = _MAP2(_val, 0, 3);

    _devset.display_off = _val;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date of year.
 */
int16_t lv_date_year_get_val()
{
    return _devset.date.year;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date of month.
 */
int8_t lv_date_month_get_val()
{
    return _devset.date.month;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date of day.
 */
int8_t lv_date_day_get_val()
{
    return _devset.date.day;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date is need tran.
 */
int8_t lv_date_tran_get_val()
{
    return _devset.date.tran;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return time of hour.
 */
int8_t lv_time_hour_get_val()
{
    return _devset.time.hour;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return time of minute.
 */
int8_t lv_time_min_get_val()
{
    return _devset.time.min;
}

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return time of second.
 */
int8_t lv_time_sec_get_val()
{
    return _devset.time.sec;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_apoff_get_val()
{
    return _devset.apo_time;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_comp_get_type_val()
{
    return _devset.comp.type;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_comp_get_max_val()
{
    return _devset.comp.max;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_comp_get_min_val()
{
    return _devset.comp.min;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_record_get_rate_val()
{
    return _devset.record.rate;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_record_get_nr_val()
{
    return _devset.record.nr;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_mem_get_val()
{
    return _devset.memMod;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_dark_get_val()
{
    return _devset.display.dark;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_bright_get_val()
{
    return _devset.display.bright;
}

/**
 * Adds or subtracts a value from the specified 
 * part of the date's tran switch value.
 */
static void date_refer()
{
    int16_t year = _devset.date.year;
    int8_t month = _devset.date.month;
    int8_t day = _devset.date.day;

    /*set_rtc_date(year - 2000, 
        month, day);*/
}

/**
 * Adds or subtracts a value from the specified 
 * part of the date's tran switch value.
 */
static void time_refer()
{
    int8_t hour = _devset.time.hour;
    int8_t min = _devset.time.min;
    int8_t sec = _devset.time.sec;

    /*set_rtc_time(hour, 
        min, sec);*/
}

/**
 * Since the time dynamically follows the time of 
 * the real-time module, the values used for 
 * observations need to be followed to 
 * the latest time before validation.
 */
void time_up()
{
    uint16_t year = 0/*get_rtc_year()*/ + 2000;
    uint8_t month = 1/*get_rtc_month()*/;
    uint8_t day = 1/*get_rtc_day()*/;

    uint8_t hour = 5/*get_rtc_hour()*/;
    uint8_t min = 5/*get_rtc_minute()*/;
    uint8_t sec = 5/*get_rtc_second()*/;

    _devset.time.hour = hour;

    _devset.time.min = min;

    _devset.time.sec = sec;

    _devset.date.year = year;

    _devset.date.month = month;

    _devset.date.day = day;

    verify_time_up();
}

/**
 * Since the time dynamically follows the time of 
 * the real-time module, the values used for 
 * observations need to be followed to 
 * the latest time before validation.
 */
static void verify_time_up()
{
    _verify_devset.time.hour = \
        _devset.time.hour;

    _verify_devset.time.min = \
        _devset.time.min;

    _verify_devset.time.sec = \
        _devset.time.sec;

    _verify_devset.date.year = \
        _devset.date.year;

    _verify_devset.date.month = \
        _devset.date.month;

    _verify_devset.date.day = \
        _devset.date.day;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_dispoff_get_val()
{
    return _devset.display_off;
}

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_voice_get_state_val()
{
    return _devset.voice.state;
}
