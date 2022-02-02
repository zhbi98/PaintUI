
#include "i2cbus.h"

static void master_sda_input()
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin = SDA_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_OType = GPIO_OType_OD;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(SDA_GPIO, &gpio_init);
}

static void master_sda_output()
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin = SDA_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_OD;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(SDA_GPIO, &gpio_init);
}

void master_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(SCL_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(SDA_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = SCL_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SCL_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = SDA_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SDA_GPIO, &gpio_init);
}

void master_onoff(unsigned char state)
{
    if (state)
        GPIO_SetBits(SDA_GPIO, SDA_PIN);
    else
        GPIO_ResetBits(SDA_GPIO, SDA_PIN);

    GPIO_SetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);
    
    if (state)
        GPIO_ResetBits(SDA_GPIO, SDA_PIN);
    else
        GPIO_SetBits(SDA_GPIO, SDA_PIN);
    // sleep_us(20);
    GPIO_ResetBits(SCL_GPIO, SCL_PIN);
}

void master_send_ack(unsigned char ack)
{
    if (!ack)
        GPIO_ResetBits(SDA_GPIO, SDA_PIN);
    else
        GPIO_SetBits(SDA_GPIO, SDA_PIN);

    GPIO_SetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);

    if (!ack)
        GPIO_SetBits(SDA_GPIO, SDA_PIN);
    else
        GPIO_ResetBits(SDA_GPIO, SDA_PIN);

    GPIO_ResetBits(SCL_GPIO, SCL_PIN);
}

void check_slave_ack()
{
    unsigned char ack = 0;

    master_sda_input();

    GPIO_SetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);
    while ((GPIO_ReadInputDataBit(SDA_GPIO, SDA_PIN) == 1) && (ack < 255)) {
        ack++;
    }
    GPIO_ResetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);

    master_sda_output();
}

void master_send_bit(unsigned char a_bit)
{
    GPIO_ResetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);

    if (a_bit)
        GPIO_SetBits(SDA_GPIO, SDA_PIN);
    else
        GPIO_ResetBits(SDA_GPIO, SDA_PIN);
    sleep_us(20);
    GPIO_SetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);
}

void master_send_byte(unsigned char a_byte)
{
    unsigned char send;

    for (send = 0; send < 8; send++) {
        master_send_bit((a_byte >> send) & 0x01);
    }
    GPIO_ResetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);
    GPIO_SetBits(SDA_GPIO, SDA_PIN);
    sleep_us(20);
    GPIO_SetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);
}

unsigned char master_receive_byte()
{
    unsigned char dat_a;
    unsigned char receive;

    master_sda_input();

    GPIO_ResetBits(SCL_GPIO, SCL_PIN);
    sleep_us(20);
    GPIO_SetBits(SDA_GPIO, SDA_PIN);
    sleep_us(20);

    for (receive = 0; receive < 8; receive++) {
        GPIO_SetBits(SCL_GPIO, SCL_PIN);
        sleep_us(20);
        dat_a = (dat_a << 1) | GPIO_ReadInputDataBit(SDA_GPIO, SDA_PIN);
        GPIO_ResetBits(SCL_GPIO, SCL_PIN);
        sleep_us(20);
    }
    master_sda_output();

    return dat_a;
}
