
#ifndef __USART_H__
#define __USART_H__

#include <stdio.h>
#include <stdarg.h>
#include "stm32f4xx.h"

void usart_init();
void usart_send_byte(USART_TypeDef * usart_p, uint8_t a_byte);
void usart_send_string(USART_TypeDef * usart_p, uint8_t * string);
void usart_send_fmt_string(USART_TypeDef * usart_p, uint8_t * format, ...);

#endif
