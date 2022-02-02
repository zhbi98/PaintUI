
#ifndef __OLED096_H__
#define __OLED096_H__

#include <stdio.h>
#include <stdarg.h>

#include "stm32f4xx.h"

#include "fontlib.h"
#include "time.h"

// sclk
#define OLED096_D0_GPIO  GPIOE
#define OLED096_D0_PIN   GPIO_Pin_2
#define OLED096_D0_CLOCK RCC_AHB1Periph_GPIOE
// mosi
#define OLED096_D1_GPIO  GPIOE
#define OLED096_D1_PIN   GPIO_Pin_4
#define OLED096_D1_CLOCK RCC_AHB1Periph_GPIOE
// rest
#define OLED096_RS_GPIO  GPIOE
#define OLED096_RS_PIN   GPIO_Pin_6
#define OLED096_RS_CLOCK RCC_AHB1Periph_GPIOE
// d::c
#define OLED096_DC_GPIO  GPIOC
#define OLED096_DC_PIN   GPIO_Pin_0
#define OLED096_DC_CLOCK RCC_AHB1Periph_GPIOC
// cs
#define OLED096_CS_GPIO  GPIOA
#define OLED096_CS_PIN   GPIO_Pin_0
#define OLED096_CS_CLOCK RCC_AHB1Periph_GPIOA

#define white 0
#define black 1

// oled 0.96 display video memory
extern unsigned char oled_vm[];

static void oled096_gpio_init();

extern void oled096_send_bit(unsigned char a_bit);
extern void oled096_send_byte(unsigned char a_byte);
extern void write_command(unsigned char command);
extern void write_data(unsigned char dat_a);
extern void clean(unsigned char dat_a);
extern void oled096_init();
extern void display_on();
extern void display_off();
extern void display_pixel(unsigned char y, unsigned char x, unsigned char color, unsigned char vm[]);
extern void send_display_memory(unsigned char vm[]);
extern void display_position(unsigned char y, unsigned char x);
extern void display_character(unsigned char y, unsigned char x, unsigned char character);
extern void display_string(unsigned char y, unsigned char x, const unsigned char * string);
extern void display_value(unsigned char y, unsigned char x, unsigned char *format, ...);
extern void display_bevel_rectangle(unsigned char y, unsigned char x, unsigned char width, unsigned char height, unsigned char radian, unsigned char vm[]);

#endif
