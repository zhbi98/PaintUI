
#include "systick.h"

static volatile unsigned int timing;

void systick_init(double scale)
{
#ifdef SysTick_HCLK_Div8
    // SystemCoreClock / 1000    1ms
    // SystemCoreClock / 100000  10us
    // SystemCoreClock / 1000000 1us
    SysTick_Config(SystemCoreClock / scale / 8);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
#else
    SysTick_Config(SystemCoreClock / scale);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
#endif
}

void systick_sleep(unsigned int ms)
{
    timing = ms;
    while (timing != 0);
}

void SysTick_Handler()
{
    timing--;
}
