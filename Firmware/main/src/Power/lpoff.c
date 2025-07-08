/**
 * @file lpoff.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "setup.h"
#include "lpoff.h"

/*********************
 *      DEFINES
 *********************/

#define REP_TIME 300U /*s*/
#define PAUSE 15U /*s*/

/**********************
 *      TYPEDEFS
 **********************/

nt_lpoff_t lpoff = {
    .qval = 100,

    .pause = STMS_TICKS(
        PAUSE, 
        TICK_LPOFF
    ),

    .repeat = 5,

    .rep_dt = STMS_TICKS(
        REP_TIME, 
        TICK_LPOFF
    ),

    .alert = 0,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_lpoff_alerts()
{
    uint8_t desc[48] = {0};

    memset(desc, '\0', 48);

    snprintf(desc, 48, "%s", 
        "Device power low");
}

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_lpoff_end()
{
    /*Power down*/
}

/**
 * Indicates whether the data needs to be retransmitted 
 * to the display after it has been modified.
 * @return need to be refreshed.
 */
void nt_lpoff_tick_work()
{
    static uint8_t _wait = 0;

    /*The control mechanism is suspended 
    for a period of time, waiting for 
    the power detection to be stable*/
    if (lpoff.pause > 0) {
        lpoff.pause--;
        return;
    }

    lpoff.qval = nt_bat_get_qval();

    /*Power abnormal, pick up, re-initialize 
    the controller, re-listening*/
    if (lpoff.qval > 25) {
        lpoff.repeat = 5;

        lpoff.pause = \
            STMS_TICKS(PAUSE, 
            TICK_LPOFF);

        lpoff.rep_dt = \
            STMS_TICKS(REP_TIME, 
                TICK_LPOFF);

        lpoff.alert = 0;
        return;
    }

    if (lpoff.rep_dt > 0) 
        lpoff.rep_dt--;

    /*Alerts interval control*/
    if ((lpoff.repeat > 0) && 
        (!lpoff.rep_dt)
    ) {
        lpoff.rep_dt = \
            STMS_TICKS(REP_TIME, 
                TICK_LPOFF);

        lpoff.repeat--;
        lpoff.alert = 0;
    }

    /*The interval time is reached and 
    the alert is started*/
    if (!lpoff.alert) {
        nt_lpoff_alerts();
        lpoff.alert = 1;
    }

    if ((lpoff.repeat) && 
        (lpoff.qval >= 15)
    ) return;

    if ((!lpoff.rep_dt) && 
        (lpoff.qval < 15)
    ) {
        if (!lpoff.alert) {
            nt_lpoff_alerts();
            lpoff.alert = 1;
        }

        if (!_wait) {
            _wait = STMS_TICKS(
                REP_TIME, 
                TICK_LPOFF);
        }
        
        if (_wait > 0) _wait--;

        if (!_wait) {
            nt_lpoff_end();
        }
    }
    else 
    if (lpoff.qval < 10) {

        if (!lpoff.alert) {
            nt_lpoff_alerts();
            lpoff.alert = 1;
        }

        if (!_wait) {
            _wait = STMS_TICKS(
                REP_TIME, 
                TICK_LPOFF
            );
        }
        if (_wait > 0) _wait--;

        if (!_wait) {
            nt_lpoff_end();
        }
    }
}
