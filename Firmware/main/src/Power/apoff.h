/**
 * @file apoff.h
 *
 */

#ifndef __APOFF_H__
#define __APOFF_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define TICK_APOFF 500U /*ms*/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	uint8_t start;
	uint8_t val;
	uint32_t tick;
} nt_apoff_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void nt_apoff_set_val(uint8_t start, uint8_t val);
void nt_apoff_tick_refer();
void nt_apoff_tick_work();

#endif /*__APOFF_H__*/
