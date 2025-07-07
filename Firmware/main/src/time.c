/**
 * @file time.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "time.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Creates a blocking microsecond-level delay using busy loops.
 * @param us Number of microseconds to delay 
 * (valid range depends on CPU frequency).
 */
void sleep_us(uint32_t us)
{
    volatile uint32_t i;

    for (; us > 0; us--)
        for (i = 12; 
            i > 0; i--);
}

/**
 * Creates a blocking millisecond-level delay using busy loops.
 * @param ms Number of millisecond to delay 
 * (valid range depends on CPU frequency).
 */
void sleep_ms(uint32_t ms)
{
    volatile uint32_t i;

    for (; ms > 0; ms--)
        for (i = 12000; 
            i > 0; i--);
}
