/**
 * @file _power.h
 *
 */

#ifndef __POWER_H__
#define __POWER_H__

/*********************
 *      INCLUDES
 *********************/

#include <math.h>
#include <stdbool.h>
#include "lvgl.h"
#include "log.h"
#include "hal_def.h"
#include "tick.h"

/*********************
 *      DEFINES
 *********************/

#define DATA_NR 100U

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Describe the historical parameters
 * of the Kalman filter.
 */
typedef struct {
    float pbuffer[DATA_NR];
    uint16_t idx;
    uint16_t noft; /**<Number of times*/
    float ret;
    bool end;
} nt_liocv_t;

/**
 * Describe the historical parameters
 * of the Kalman filter.
 */
typedef struct {
    float cur_est;
    float last_est;
    float K_gain;
    float Y;
} km_filte_t;

/**
 * Describe the historical parameters
 * of the Kalman filter.
 */
typedef struct {
    uint8_t soc;
    uint8_t soh;
} nt_lisox_t;

/**
 * Describe the historical parameters
 * of the Kalman filter.
 */
typedef struct {
    uint32_t prev_tick;
    uint32_t act_tick;
    int16_t soc_prev;
    float soc_chrg;
    uint8_t inited;
} nt_lichrg_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_bat_ocv_est_val();
int16_t nt_bat_get_qval();
void nt_bat_chrg_act_tick();

#endif /*__POWER_H__*/
