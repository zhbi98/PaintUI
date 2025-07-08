/**
 * @file idenMang.h
 *
 */

#ifndef __IDEN_MANAG__
#define __IDEN_MANAG__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define MAX_LOGO_NUM 5

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uint8_t state;
    uint8_t name;
} _iden_t;

typedef struct {
    uint8_t phead;
    uint8_t ptail;
    _iden_t buf[MAX_LOGO_NUM];
} _iden_mang_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void iden_qq_init(_iden_mang_t * _qq_p);
uint8_t iden_qq_empty(_iden_mang_t * _qq_p);
uint8_t iden_qq_full(_iden_mang_t * _qq_p);
uint8_t iden_qq_ins(_iden_mang_t * _qq_p, uint8_t name, uint8_t state);
uint8_t iden_qq_remove(_iden_mang_t * _qq_p, _iden_t * iden_p);

#endif /*__IDEN_MANAG__*/
