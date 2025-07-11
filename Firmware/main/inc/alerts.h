/**
 * @file alerts.h
 *
 */

#ifndef __ALERTS_H__
#define __ALERTS_H__

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    const uint8_t stridx;
    uint8_t specify[64];
    uint8_t active;
    uint32_t _tick;
} dev_alerts_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern dev_alerts_t alerts[];

#endif /*__ALERTS_H__*/
