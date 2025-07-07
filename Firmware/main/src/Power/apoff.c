/**
 * @file apoff.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "setup.h"
#include "apoff.h"

/*********************
 *      DEFINES
 *********************/

#define _SEC(x) ((x) * 1U)
#define _MIN(x) ((x) * _SEC(60U))

/**********************
 *      TYPEDEFS
 **********************/

nt_apoff_t apoff = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_apoff_set_val(uint8_t start, uint8_t val)
{
    apoff.start = start;
    apoff.val = val;

    nt_apoff_tick_refer();
}

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_apoff_tick_refer()
{
    uint32_t _time = _MIN(5);

    if (!apoff.val) _time = _MIN(5);
    else if (apoff.val == 1) _time = _MIN(10);
    else if (apoff.val == 2) _time = _MIN(15);
    else if (apoff.val == 3) _time = _MIN(30);
    else _time = _MIN(5);

    apoff.tick = STMS_TICKS(
        _time, TICK_APOFF);
}

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_apoff_tick_work()
{
    if (apoff.tick > 0)
        apoff.tick--;

    uint32_t _60s = \
        STMS_TICKS(60, TICK_APOFF);

    if (apoff.tick == _60s) {
        /*Voice*/
    }

    /*uint32_t _2s = \
        STMS_TICKS(1, TICK_APOFF);
    if (apoff.tick == _2s)
        _apoffvoice();*/

    uint32_t _0s = \
        STMS_TICKS(0, TICK_APOFF);

    if (apoff.tick == _0s) {
        /*Power down*/
    }
}
