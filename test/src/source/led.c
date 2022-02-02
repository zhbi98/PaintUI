
#include "led.h"

void led1_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(LED1_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = LED1_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED1_GPIO, &gpio_init);
}

void led2_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(LED2_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = LED2_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED2_GPIO, &gpio_init);
}

void led1_twink(unsigned int times)
{
    unsigned int i;

    for (i = times; i > 0; i--) {
        LED1_L();
        sleep_ms(1000);
        LED1_H();
        sleep_ms(1000);
    }
}

void led2_twink(unsigned int times)
{
    unsigned int i;

    for (i = times; i > 0; i--) {
        LED2_L();
        sleep_ms(1000);
        LED2_H();
        sleep_ms(1000);
    }
}

static void led1_breath_period(unsigned int period, unsigned int time_l)
{
    unsigned int time_h;

    time_h = period - time_l;

    LED1_L();
    while (time_l--);
    LED1_H();
    while (time_h--);
}

void led1_breath()
{
    unsigned int i;

    for (i = 0; i < 8000; i++) {
        led1_breath_period(8000, i);
    }
    for (i = 8000; i > 0; i--) {
        led1_breath_period(8000, i);
    }  
}

static void led2_breath_period(unsigned int period, unsigned int time_l)
{
    unsigned int time_h;

    time_h = period - time_l;

    LED2_L();
    while (time_l--);
    LED2_H();
    while (time_h--);
}

void led2_breath()
{
    unsigned int i;

    for (i = 0; i < 8000; i++) {
        led2_breath_period(8000, i);
    }
    for (i = 8000; i > 0; i--) {
        led2_breath_period(8000, i);
    }
}
