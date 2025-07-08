/**
 * @file idenMang.h
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include "idenMang.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize an identifier queue structure
 * @param _qq_p Pointer to the queue structure to initialize
 */
void iden_qq_init(_iden_mang_t * _qq_p)
{
    memset(_qq_p->buf, 0, sizeof(_qq_p->buf));
    _qq_p->phead = 0;
    _qq_p->ptail = 0;
}

/**
 * Check if the identifier queue is empty
 * @param _qq_p Pointer to the queue structure
 * @return true if queue is empty, false otherwise
 */
uint8_t iden_qq_empty(_iden_mang_t * _qq_p)
{
    if (_qq_p->phead == _qq_p->ptail) return true;
    else return false;
}

/**
 * Check if the identifier queue is full
 * @param _qq_p Pointer to the queue structure
 * @return true if queue is full, false otherwise
 */
uint8_t iden_qq_full(_iden_mang_t * _qq_p)
{
    if (((_qq_p->ptail + 1) % MAX_LOGO_NUM) == _qq_p->phead)
        return true;
    else return false;
}

/**
 * Insert an identifier into the queue
 * @param _qq_p Pointer to the queue structure
 * @param name Identifier name to insert
 * @param state Status value to insert
 * @return true if insertion succeeded, false if queue is full
 */
uint8_t iden_qq_ins(_iden_mang_t * _qq_p, uint8_t name, uint8_t state)
{
    if (iden_qq_full(_qq_p)) return false;

    _qq_p->buf[_qq_p->ptail].name = name;
    _qq_p->buf[_qq_p->ptail].state = state;
    _qq_p->ptail += 1;

    _qq_p->ptail = _qq_p->ptail % MAX_LOGO_NUM;
    return true;
}

/**
 * Remove an identifier from the queue
 * @param _qq_p Pointer to the queue structure
 * @param iden_p Pointer to store the removed identifier
 * @return true if removal succeeded, false if queue is empty
 */
uint8_t iden_qq_remove(_iden_mang_t * _qq_p, _iden_t * iden_p)
{
    if (iden_qq_empty(_qq_p)) return false;

    *iden_p = _qq_p->buf[_qq_p->phead];
    _qq_p->phead += 1;

    _qq_p->phead = _qq_p->phead % MAX_LOGO_NUM;
    return true;
}
