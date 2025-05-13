
#ifndef __TIMERS_H__
#define __TIMERS_H__

#include "stm32f4xx.h"
#include "nvic.h"

#define CURRENT_TIMER              TIM6
#define CURRENT_TIMER_CLOCK        RCC_APB1Periph_TIM6
#define CURRENT_TIMER_IRQN         TIM6_DAC_IRQn
#define CURRENT_TIMER_IRQHANDLER() TIM6_DAC_IRQHandler()

extern void timers_model_init(uint32_t times, uint32_t prescaler);
extern void timers_init(uint32_t times, uint32_t prescaler);
extern void CURRENT_TIMER_IRQHANDLER();

#endif
