
#include "pcf8591.h"

static void pcf8591_sda_input()
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin = PCF8591_SDA_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_OType = GPIO_OType_OD;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(PCF8591_SDA_GPIO, &gpio_init);
}

static void pcf8591_sda_output()
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin = PCF8591_SDA_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_OD;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(PCF8591_SDA_GPIO, &gpio_init);
}

void pcf8591_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(PCF8591_SCL_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(PCF8591_SDA_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = PCF8591_SCL_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PCF8591_SCL_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = PCF8591_SDA_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PCF8591_SDA_GPIO, &gpio_init);
}

void pcf8591_onoff(unsigned char state)
{
    if (state)
        GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    else
        GPIO_ResetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);

    GPIO_SetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);
    
    if (state)
        GPIO_ResetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    else
        GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    sleep_us(20);
    GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
}

void master_sendack_pcf8591(unsigned char ack)
{
    if (!ack)
        GPIO_ResetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    else
        GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);

    GPIO_SetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);

    if (!ack)
        GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    else
        GPIO_ResetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);

    GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
}

void check_pcf8591_ack()
{
    unsigned char ack = 0;

    pcf8591_sda_input();

    GPIO_SetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);
    while ((GPIO_ReadInputDataBit(PCF8591_SDA_GPIO, PCF8591_SDA_PIN) == 1) && (ack < 255)) {
        ack++;
    }
    GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);

    pcf8591_sda_output();
}

void pcf8591_send_bit(unsigned char a_bit)
{
    GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);

    if (a_bit)
        GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    else
        GPIO_ResetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    sleep_us(20);
    GPIO_SetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);
}

void pcf8591_send_byte(unsigned char a_byte)
{
    unsigned char send;

    for (send = 0; send < 8; send++) {
        pcf8591_send_bit((a_byte << send) & 0x80);
    }
    GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);
    GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    sleep_us(20);
    GPIO_SetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);
}

unsigned char master_receive_pcf8591()
{
    unsigned char dat_a;
    unsigned char receive;

    pcf8591_sda_input();

    GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
    sleep_us(20);
    GPIO_SetBits(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
    sleep_us(20);

    for (receive = 0; receive < 8; receive++) {
        GPIO_SetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
        sleep_us(20);
        dat_a = (dat_a << 1) | GPIO_ReadInputDataBit(PCF8591_SDA_GPIO, PCF8591_SDA_PIN);
        GPIO_ResetBits(PCF8591_SCL_GPIO, PCF8591_SCL_PIN);
        sleep_us(20);
    }
    pcf8591_sda_output();

    return dat_a;
}

unsigned char pcf8591_read(unsigned char ain)
{
    unsigned char ad_value;

    pcf8591_onoff(PCF8591_START);
    pcf8591_send_byte(PCF8591_ADDRESS + PCF8591_WRITE);
    pcf8591_send_byte(0x40 + ain - 1);
    check_pcf8591_ack();
    pcf8591_onoff(PCF8591_STOP);

    pcf8591_onoff(PCF8591_START);
    pcf8591_send_byte(PCF8591_ADDRESS + PCF8591_READ);
    ad_value = master_receive_pcf8591();
    master_sendack_pcf8591(PCF8591_NOACK);
    pcf8591_onoff(PCF8591_STOP);

    return ad_value;
}

void pcf8591_aout(unsigned char da_value)
{
    pcf8591_onoff(PCF8591_START);
    pcf8591_send_byte(PCF8591_ADDRESS + PCF8591_WRITE);
    check_pcf8591_ack();
    pcf8591_send_byte(0x40);
    check_pcf8591_ack();
    pcf8591_send_byte(da_value);
    check_pcf8591_ack();
    pcf8591_onoff(PCF8591_STOP);
}
