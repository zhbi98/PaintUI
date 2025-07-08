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
    uint8_t active;
    uint32_t _time;
    const uint32_t msg_width;
    const uint32_t msg_high;
    const uint8_t stridx;
} dev_alerts_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern dev_alerts_t alerts[];

#endif /*__ALERTS_H__*/
