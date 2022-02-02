
#include "adc.h"

static void adc_nvic_init()
{
    NVIC_InitTypeDef nvic_init;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    nvic_init.NVIC_IRQChannel = ADC_IRQN;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);
}

static void adc_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(ANALOG_CLOCK, ENABLE);

    gpio_init.GPIO_Pin   = ANALOG_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AIN;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(ANALOG_GPIO, &gpio_init);
}

static void adc_common_init()
{
    ADC_CommonInitTypeDef adc_common_init;

    RCC_APB2PeriphClockCmd(ADC_CLOCK, ENABLE);

    adc_common_init.ADC_Mode = ADC_Mode_Independent;
    adc_common_init.ADC_Prescaler = ADC_Prescaler_Div2;
    adc_common_init.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    adc_common_init.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
    ADC_CommonInit(&adc_common_init);
}

static void adc_seting_init()
{
    ADC_InitTypeDef adc_init;

    adc_init.ADC_Resolution = ADC_Resolution_12b;
    adc_init.ADC_ScanConvMode = DISABLE;
    adc_init.ADC_ContinuousConvMode = ENABLE;
    adc_init.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    // adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfConversion = 1;
    ADC_Init(CURRENT_ADC, &adc_init);
}

void adc_conversion_config()
{
    adc_gpio_init();
    adc_common_init();
    adc_seting_init();

    ADC_RegularChannelConfig(CURRENT_ADC, ADC_CHANNEL, 1, ADC_SampleTime_56Cycles);
    adc_nvic_init();
    ADC_ITConfig(CURRENT_ADC, ADC_IT_EOC, ENABLE);
    ADC_Cmd(CURRENT_ADC, ENABLE);
    ADC_SoftwareStartConv(CURRENT_ADC);
}

unsigned int adc_read()
{
    unsigned int adc_value;

    adc_value = ADC_GetConversionValue(CURRENT_ADC);
    return adc_value;
}

void ADC_IRQHandler()
{
    if (ADC_GetITStatus(CURRENT_ADC, ADC_IT_EOC) == SET)
        ADC_ClearITPendingBit(CURRENT_ADC, ADC_IT_EOC);
}
