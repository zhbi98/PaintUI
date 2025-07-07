/**
 * @file lpoff.h
 *
 */

#ifndef __LPOFF_H__
#define __LPOFF_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define TICK_LPOFF 500U /*ms*/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uint8_t qval;
    uint8_t pause;
    uint8_t repeat;
    uint32_t rep_dt;
    uint8_t alert;
} nt_lpoff_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_lpoff_tick_work();

#endif /*__APOFF_H__*/
