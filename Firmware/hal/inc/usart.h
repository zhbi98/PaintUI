
#ifndef __USART_H__
#define __USART_H__

#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx.h"

#define CURRENT_USART     USART1
#define BAUD_RATE         115200
#define USART_CLOCK       RCC_APB2Periph_USART1

#define USART_TX_GPIO     GPIOA
#define USART_TX_PIN      GPIO_Pin_9
#define USART_TX_CLOCK    RCC_AHB1Periph_GPIOA
#define USART_TX_AF       GPIO_AF_USART1
#define USART_TX_SRC      GPIO_PinSource9

#define USART_RX_GPIO     GPIOA
#define USART_RX_PIN      GPIO_Pin_10
#define USART_RX_CLOCK    RCC_AHB1Periph_GPIOA
#define USART_RX_AF       GPIO_AF_USART1
#define USART_RX_SRC      GPIO_PinSource10

#define USART_IRQN        USART1_IRQn
#define USART_IRQHANDLER() USART1_IRQHandler()

extern unsigned char usart_data[];

static void usart_nvic_init();
static void usart_gpio_init();

extern void usart_init();
extern void usart_send_byte(USART_TypeDef * usart, unsigned char a_byte);
extern void usart_send_string(USART_TypeDef * usart, unsigned char * string);
extern void usart_send_value(USART_TypeDef * usart, unsigned char * format, ...);
extern void USART_IRQHANDLER();

#endif
