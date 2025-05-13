
#include "nvic.h"

/*
    group               NVIC_PriorityGroup_0
    channel             TIM6_DAC_IRQn
    preemption_priority 0
    sub_priority        3
 */
void nvic_init(uint32_t group, unsigned int channel, unsigned char preemption_priority, unsigned char sub_priority)
{
    NVIC_InitTypeDef nvic_init;

    NVIC_PriorityGroupConfig(group);
    nvic_init.NVIC_IRQChannel = channel;
    nvic_init.NVIC_IRQChannelPreemptionPriority = preemption_priority;
    nvic_init.NVIC_IRQChannelSubPriority = sub_priority;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);
}
