
#include "spibus.h"

static void spi_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(MISO_CLOCK | MOSI_CLOCK | SCLK_CLOCK | CS_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = MISO_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(MISO_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = MOSI_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(MOSI_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = SCLK_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(SCLK_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = CS_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(CS_GPIO, &gpio_init);
}

void spi_init()
{
    spi_gpio_init();

    GPIO_SetBits(SCLK_GPIO, SCLK_PIN);
    sleep_ms(1);
}

void master_send_bit(unsigned char a_bit)
{
    if (a_bit)
        GPIO_SetBits(MOSI_GPIO, MOSI_PIN);
    else
        GPIO_ResetBits(MOSI_GPIO, MOSI_PIN);
}

void master_send_byte(unsigned char a_byte)
{
    unsigned char i;

    GPIO_ResetBits(CS_GPIO, CS_PIN);

    for (i = 0; i < 8; i++) {
        GPIO_ResetBits(SCLK_GPIO, SCLK_PIN);
        master_send_bit((a_byte << i) & 0x80);
        sleep_us(1);
        GPIO_SetBits(SCLK_GPIO, SCLK_PIN);
    }
    
    GPIO_SetBits(CS_GPIO, CS_PIN);
}

unsigned char master_receive_byte()
{
    unsigned char i;
    unsigned char dat_a;

    GPIO_SetBits(SCLK_GPIO, SCLK_PIN);

    for (i = 0; i < 8; i++) {
        GPIO_SetBits(SCLK_GPIO, SCLK_PIN);
        sleep_us(1);
        GPIO_ResetBits(SCLK_GPIO, SCLK_PIN);
        dat_a = dat_a << 1;
        dat_a =  dat_a | (GPIO_ReadInputDataBit(MISO_GPIO, MISO_PIN));
        sleep_us(1);
    }

    return dat_a;
}
