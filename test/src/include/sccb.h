
#ifndef __SCCB_H__
#define __SCCB_H__

#include "stm32f4xx.h"
#include "gpio.h"
#include "time.h"

#define SCCB_SDA_GPIO  GPIOD
#define SCCB_SDA_PIN   GPIO_Pin_7
#define SCCB_SDA_CLOCK RCC_AHB1Periph_GPIOD

#define SCCB_SCL_GPIO  GPIOD
#define SCCB_SCL_PIN   GPIO_Pin_6
#define SCCB_SCL_CLOCK RCC_AHB1Periph_GPIOD

#define sccb_sda_in()  {SCCB_SDA_GPIO -> MODER &= ~(3 << (7 * 2)); SCCB_SDA_GPIO -> MODER |= 0 << 7 * 2;}
#define sccb_sda_out() {SCCB_SDA_GPIO -> MODER &= ~(3 << (7 * 2)); SCCB_SDA_GPIO -> MODER |= 1 << 7 * 2;}

// #define SCCB_SCL       GPIOD_OUT(6)
// #define SCCB_SDA       GPIOD_OUT(7)

#define SCCB_SDA_H()   (SCCB_SDA_GPIO -> BSRRL = SCCB_SDA_PIN)// GPIO_SetBits(SCCB_SDA_GPIO, SCCB_SDA_PIN)
#define SCCB_SDA_L()   (SCCB_SDA_GPIO -> BSRRH = SCCB_SDA_PIN)// GPIO_ResetBits(SCCB_SDA_GPIO, SCCB_SDA_PIN)

#define SCCB_SCL_H()   (SCCB_SCL_GPIO -> BSRRL = SCCB_SCL_PIN)// GPIO_SetBits(SCCB_SCL_GPIO, SCCB_SCL_PIN)
#define SCCB_SCL_L()   (SCCB_SCL_GPIO -> BSRRH = SCCB_SCL_PIN)// GPIO_ResetBits(SCCB_SCL_GPIO, SCCB_SCL_PIN)

#define SCCB_READ_SDA() GPIOD_IN(7)

#define OV7670_ADDRESS 0x42
#define WRITE          0
#define READ           1

extern void sccb_gpio_init();
extern void sccb_on();
extern void sccb_off();
extern void sccb_no_ack();
extern unsigned char sccb_write(unsigned char dat_a);
extern unsigned char sccb_read();
extern unsigned char sccb_write_reg(unsigned char reg, unsigned char dat_a);
extern unsigned char sccb_read_reg(unsigned char reg);

#endif
