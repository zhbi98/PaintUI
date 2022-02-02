
#ifndef __PCF8591_H__
#define __PCF8591_H__

#include "stm32f4xx.h"
#include "time.h"

#define PCF8591_SDA_GPIO    GPIOE
#define PCF8591_SDA_PIN     GPIO_Pin_5
#define PCF8591_SDA_CLOCK   RCC_AHB1Periph_GPIOE

#define PCF8591_SCL_GPIO    GPIOE
#define PCF8591_SCL_PIN     GPIO_Pin_3
#define PCF8591_SCL_CLOCK   RCC_AHB1Periph_GPIOE

#define PCF8591_START       1
#define PCF8591_STOP        0

#define PCF8591_ACK         0
#define PCF8591_NOACK       1

#define PCF8591_ADDRESS  0x90

#define PCF8591_WRITE       0
#define PCF8591_READ        1

static void pcf8591_sda_input();
static void pcf8591_sda_output();

extern void pcf8591_gpio_init();
extern void pcf8591_onoff(unsigned char state);
extern void master_sendack_pcf8591(unsigned char ack);
extern void check_pcf8591_ack();
extern void pcf8591_send_bit(unsigned char a_bit);
extern void pcf8591_send_byte(unsigned char a_byte);
extern unsigned char master_receive_pcf8591();
extern unsigned char pcf8591_read(unsigned char ain);
extern void pcf8591_aout(unsigned char da_value);

#endif
