/**
 * @file setup.h
 *
 */

#ifndef __SETUP_H__
#define __SETUP_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include "log.h"

/*********************
 *      DEFINES
 *********************/

#define TICKS(v1, v2) \
    (((uint32_t)(v1)) / ((uint32_t)(v2)))
#define STMS_TICKS(s, ms) \
    ((uint32_t)((s) * (1000U) / (ms)))
#define TICK_APOFF 500U /*ms*/

/**********************
 *      TYPEDEFS
 **********************/

enum {
    DEV_TIM = 0,
    DEV_DATE,
    DEV_DATE_TRAN,
    DEV_APOFF,
    DEV_COMP_MAX,
    DEV_COMP_MIN,
    DEV_COMP_TYPE,
    DEV_REC_RATE,
    DEV_MEM,
    DEV_BRIGHT,
    DEV_DISP_OFF,
    DEV_VOICE,
    DEV_DARK,
    DEV_CTL_MAX = 12,
};

typedef struct {
    uint8_t head[5 + 1];

    struct {
        int8_t hour;
        int8_t min;
        int8_t sec;
    } time;

    struct {
        int32_t year;
        int8_t month;
        int8_t day;
        int8_t tran;
    } date;

    int8_t apo_time;

    struct {
        int32_t max;
        int32_t min;
        int8_t type;
    } comp;

    int32_t contval;

    struct {
        int32_t rate;
        int32_t nr;
    } record;

    struct {
        int8_t bright;
        int8_t dark;
    } display;

    int8_t memMod;

    int8_t torch_light_off;
    int8_t key_light_off;
    int8_t display_off;

    struct {
        int8_t state;
        int8_t vol;
    } voice;

    int8_t devdsc;

    uint8_t dispstr[32];
    uint8_t ssid[8 + 1];
} _devset_t;

typedef struct {
    const uint8_t h_cnt[DEV_CTL_MAX];
    int8_t v_idx;
    int8_t h_idx;
    int8_t page;
    int8_t opti_id;
} list_view_t;

typedef struct {
    uint8_t val;
    uint32_t tick;
    bool start;
} dev_off_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern _devset_t _devset;

/**
 * Activate a child view under the device settings view.
 * @param _tabvidx tabview card index.
 */
void lv_tab_set_line(int8_t val);

/**
 * Activate a child option under the device settings view.
 * @param _optidx card options index.
 */
void lv_tab_set_hidx(int8_t val);

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return tabview card index result.
 */
uint8_t lv_tab_get_line_id();

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return index of the current page options.
 */
uint8_t lv_tab_get_opti_id();

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return index of the current option part.
 */
uint8_t lv_tab_get_hidx();

/**
 * Gets the index of the child view currently 
 * active under settings view.
 * @return index of the current option part.
 */
uint8_t lv_tab_get_page_id();

/**
 * Adds or subtracts a value from the specified 
 * part of the date value.
 */
void lv_date_set_val(int8_t val);

/**
 * Adds or subtracts a value from the specified 
 * part of the time value.
 */
void lv_time_set_val(int8_t val);

/**
 * Adds or subtracts a value from the specified 
 * part of the date's tran switch value.
 */
void lv_tran_set_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_apoff_set_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_bright_set_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_voice_set_val(int8_t val);
/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_dark_set_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_comp_set_type_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_record_set_val(uint16_t nr, uint32_t tim);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_mem_set_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_dispoff_set_val(int8_t val);

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date of year.
 */
int16_t lv_date_year_get_val();

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date of month.
 */
int8_t lv_date_month_get_val();

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date of day.
 */
int8_t lv_date_day_get_val();

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return date is need tran.
 */
int8_t lv_date_tran_get_val();

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return time of hour.
 */
int8_t lv_time_hour_get_val();

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return time of minute.
 */
int8_t lv_time_min_get_val();

/**
 * Gets the value of the current setting, which is used only to update 
 * page options and the state of the element.
 * @return time of second.
 */
int8_t lv_time_sec_get_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_apoff_get_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_comp_get_type_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_comp_get_max_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_comp_get_min_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_record_get_rate_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint32_t lv_record_get_nr_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
void lv_mem_set_val(int8_t val);

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_dark_get_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_bright_get_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_dispoff_get_val();

/**
 * Writes the display date of user changes 
 * to the hardware module.
 */
uint8_t lv_voice_get_state_val();

/**
 * Writes the changed parameters to the file system, next time can 
 * extract the settings from the file system 
 * to update to the hardware drive
 */
void write_file();

/**
 * Extract the settings from the file system 
 * to update to the hardware drive
 */
void read_file();

#endif /*__SETUP_H__*/
