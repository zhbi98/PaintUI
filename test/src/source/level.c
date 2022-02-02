
#include "level.h"

static void level_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(LEVEL_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = LEVEL_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(LEVEL_GPIO, &gpio_init);
}

char read_level()
{
    char level;

    level_gpio_init();

    level = GPIO_ReadInputDataBit(LEVEL_GPIO, LEVEL_PIN);
    return level;
}
