
#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"

#define ANALOG_GPIO   GPIOA
#define ANALOG_PIN    GPIO_Pin_0
#define ANALOG_CLOCK  RCC_AHB1Periph_GPIOA

#define CURRENT_ADC   ADC1
#define ADC_CLOCK     RCC_APB2Periph_ADC1

#define ADC_CHANNEL   ADC_Channel_0

#define ADC_IRQN      ADC_IRQn

static void adc_nvic_init();
static void adc_gpio_init();
static void adc_common_init();
static void adc_seting_init();

extern void adc_conversion_config();
extern unsigned int adc_read();
extern void ADC_IRQHandler();

#endif
