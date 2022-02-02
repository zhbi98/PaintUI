
#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "stm32f4xx.h"

#define LEVEL_GPIO  GPIOA
#define LEVEL_PIN   GPIO_Pin_5
#define LEVEL_CLOCK RCC_AHB1Periph_GPIOA

static void level_gpio_init();
extern char read_level();

#endif
