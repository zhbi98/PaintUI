
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f4xx.h"

#define US_1  1000000
#define US_10 100000
#define MS_1  1000

static volatile unsigned int timing;

extern void systick_init(double scale);
extern void systick_sleep(unsigned int ms);
extern void SysTick_Handler();

#endif
