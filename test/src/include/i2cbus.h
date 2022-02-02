
#ifndef __I2CBUS_H__
#define __I2CBUS_H__

#include "stm32f4xx.h"

#include "time.h"

#define SCL_GPIO  GPIOA
#define SCL_PIN   GPIO_Pin_1
#define SCL_CLOCK RCC_AHB1Periph_GPIOA

#define SDA_GPIO  GPIOA
#define SDA_PIN   GPIO_Pin_2
#define SDA_CLOCK RCC_AHB1Periph_GPIOA

#define MASTER_START  1
#define MASTER_STOP   0

#define MASTER_ACK    0
#define MASTER_NOACK  1

static void master_sda_input();
static void master_sda_output();

extern void master_gpio_init();
extern void master_onoff(unsigned char state);
extern void master_send_ack(unsigned char ack);
extern void check_slave_ack();
extern void master_send_bit(unsigned char a_bit);
extern void master_send_byte(unsigned char a_byte);
extern unsigned char master_receive_byte();

#endif
