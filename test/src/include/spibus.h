
#ifndef __SPIBUS_H__
#define __SPIBUS_H__

#include "stm32f4xx.h"
#include "time.h"

#define MISO_GPIO  GPIOA
#define MISO_PIN   GPIO_Pin_1
#define MISO_CLOCK RCC_AHB1Periph_GPIOA

#define MOSI_GPIO  GPIOA
#define MOSI_PIN   GPIO_Pin_2
#define MOSI_CLOCK RCC_AHB1Periph_GPIOA

#define SCLK_GPIO  GPIOA
#define SCLK_PIN   GPIO_Pin_3
#define SCLK_CLOCK RCC_AHB1Periph_GPIOA

#define CS_GPIO    GPIOA
#define CS_PIN     GPIO_Pin_4
#define CS_CLOCK   RCC_AHB1Periph_GPIOA

static void spi_gpio_init();

extern void spi_init();
extern void master_send_bit(unsigned char a_bit);
extern void master_send_byte(unsigned char a_byte);
extern unsigned char master_receive_byte();

#endif
