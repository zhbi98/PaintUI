/**
 * @file power.h
 *
 */

#ifndef __POWER_H__
#define __POWER_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

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
  int16_t pbuffer[DATA_NR];
  uint8_t idx;
  uint16_t noft; /**<Number of times*/
  int16_t ret;
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

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_bat_ocv_est_val();
int16_t nt_bat_get_qval();

#endif /*__POWER_H__*/
