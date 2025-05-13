
#ifndef __NVIC_H__
#define __NVIC_H__

#include "stm32f4xx.h"

/*
    group               NVIC_PriorityGroup_0
    channel             TIM6_DAC_IRQn
    preemption_priority 0
    sub_priority        3
 */

extern void nvic_init(uint32_t group, unsigned int channel, unsigned char preemption_priority, unsigned char sub_priority);

#endif
