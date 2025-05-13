
#ifndef __ILI9341A_H__
#define __ILI9341A_H__

#include "stm32f4xx.h"

#include <stdio.h>
#include <stdarg.h>

#include "time.h"

#define FSMC_BANK1_NORSRAM    FSMC_Bank1_NORSRAM4
#define FSMC_CLOCK            RCC_AHB3Periph_FSMC

#define ILI9341_WRITE_COMMAND ((uint32_t)0x6c000000)
#define ILI9341_WRITE_DATA    ((uint32_t)0x6c000080)

#define ILI9341_RS_GPIO    GPIOF
#define ILI9341_RS_PIN     GPIO_Pin_12
#define ILI9341_RS_CLOCK   RCC_AHB1Periph_GPIOF
#define ILI9341_RS_AF      GPIO_AF_FSMC
#define ILI9341_RS_SRC     GPIO_PinSource12

#define ILI9341_RD_GPIO    GPIOD
#define ILI9341_RD_PIN     GPIO_Pin_4
#define ILI9341_RD_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9341_RD_AF      GPIO_AF_FSMC
#define ILI9341_RD_SRC     GPIO_PinSource4

#define ILI9341_WR_GPIO    GPIOD
#define ILI9341_WR_PIN     GPIO_Pin_5
#define ILI9341_WR_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9341_WR_AF      GPIO_AF_FSMC
#define ILI9341_WR_SRC     GPIO_PinSource5

#define ILI9341_CS_GPIO    GPIOG
#define ILI9341_CS_PIN     GPIO_Pin_12
#define ILI9341_CS_CLOCK   RCC_AHB1Periph_GPIOG
#define ILI9341_CS_AF      GPIO_AF_FSMC
#define ILI9341_CS_SRC     GPIO_PinSource12

#define ILI9341_RST_GPIO   GPIOG
#define ILI9341_RST_PIN    GPIO_Pin_15
#define ILI9341_RST_CLOCK  RCC_AHB1Periph_GPIOG

#define ILI9341_BL_GPIO    GPIOB
#define ILI9341_BL_PIN     GPIO_Pin_15
#define ILI9341_BL_CLOCK   RCC_AHB1Periph_GPIOB

#define ILI9341_D0_GPIO    GPIOD
#define ILI9341_D0_PIN     GPIO_Pin_14
#define ILI9341_D0_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9341_D0_AF      GPIO_AF_FSMC
#define ILI9341_D0_SRC     GPIO_PinSource14

#define ILI9341_D1_GPIO    GPIOD
#define ILI9341_D1_PIN     GPIO_Pin_15
#define ILI9341_D1_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9341_D1_AF      GPIO_AF_FSMC
#define ILI9341_D1_SRC     GPIO_PinSource15

#define ILI9341_D2_GPIO    GPIOD
#define ILI9341_D2_PIN     GPIO_Pin_0
#define ILI9341_D2_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9341_D2_AF      GPIO_AF_FSMC
#define ILI9341_D2_SRC     GPIO_PinSource0

#define ILI9341_D3_GPIO    GPIOD
#define ILI9341_D3_PIN     GPIO_Pin_1
#define ILI9341_D3_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9341_D3_AF      GPIO_AF_FSMC
#define ILI9341_D3_SRC     GPIO_PinSource1

#define ILI9341_D4_GPIO    GPIOE
#define ILI9341_D4_PIN     GPIO_Pin_7
#define ILI9341_D4_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9341_D4_AF      GPIO_AF_FSMC
#define ILI9341_D4_SRC     GPIO_PinSource7

#define ILI9341_D5_GPIO    GPIOE
#define ILI9341_D5_PIN     GPIO_Pin_8
#define ILI9341_D5_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9341_D5_AF      GPIO_AF_FSMC
#define ILI9341_D5_SRC     GPIO_PinSource8

#define ILI9341_D6_GPIO    GPIOE
#define ILI9341_D6_PIN     GPIO_Pin_9
#define ILI9341_D6_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9341_D6_AF      GPIO_AF_FSMC
#define ILI9341_D6_SRC     GPIO_PinSource9

#define ILI9341_D7_GPIO    GPIOE
#define ILI9341_D7_PIN     GPIO_Pin_10
#define ILI9341_D7_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9341_D7_AF      GPIO_AF_FSMC
#define ILI9341_D7_SRC     GPIO_PinSource10

#define ILI9341_D8_GPIO    GPIOE
#define ILI9341_D8_PIN     GPIO_Pin_11
#define ILI9341_D8_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9341_D8_AF      GPIO_AF_FSMC
#define ILI9341_D8_SRC     GPIO_PinSource11

#define ILI9341_D9_GPIO    GPIOE
#define ILI9341_D9_PIN     GPIO_Pin_12
#define ILI9341_D9_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9341_D9_AF      GPIO_AF_FSMC
#define ILI9341_D9_SRC     GPIO_PinSource12

#define ILI9341_D10_GPIO   GPIOE
#define ILI9341_D10_PIN    GPIO_Pin_13
#define ILI9341_D10_CLOCK  RCC_AHB1Periph_GPIOE
#define ILI9341_D10_AF     GPIO_AF_FSMC
#define ILI9341_D10_SRC    GPIO_PinSource13

#define ILI9341_D11_GPIO   GPIOE
#define ILI9341_D11_PIN    GPIO_Pin_14
#define ILI9341_D11_CLOCK  RCC_AHB1Periph_GPIOE
#define ILI9341_D11_AF     GPIO_AF_FSMC
#define ILI9341_D11_SRC    GPIO_PinSource14

#define ILI9341_D12_GPIO   GPIOE
#define ILI9341_D12_PIN    GPIO_Pin_15
#define ILI9341_D12_CLOCK  RCC_AHB1Periph_GPIOE
#define ILI9341_D12_AF     GPIO_AF_FSMC
#define ILI9341_D12_SRC    GPIO_PinSource15

#define ILI9341_D13_GPIO   GPIOD
#define ILI9341_D13_PIN    GPIO_Pin_8
#define ILI9341_D13_CLOCK  RCC_AHB1Periph_GPIOD
#define ILI9341_D13_AF     GPIO_AF_FSMC
#define ILI9341_D13_SRC    GPIO_PinSource8

#define ILI9341_D14_GPIO   GPIOD
#define ILI9341_D14_PIN    GPIO_Pin_9
#define ILI9341_D14_CLOCK  RCC_AHB1Periph_GPIOD
#define ILI9341_D14_AF     GPIO_AF_FSMC
#define ILI9341_D14_SRC    GPIO_PinSource9

#define ILI9341_D15_GPIO   GPIOD
#define ILI9341_D15_PIN    GPIO_Pin_10
#define ILI9341_D15_CLOCK  RCC_AHB1Periph_GPIOD
#define ILI9341_D15_AF     GPIO_AF_FSMC
#define ILI9341_D15_SRC    GPIO_PinSource10

#define HORIZONTAL         1

// #if (HORIZONTAL)
//     #define TFT_WIDTH     (320 + 1)
//     #define TFT_HEIGH     (240 + 1)
// #else
//     #define TFT_WIDTH     (240 + 1)
//     #define TFT_HEIGH     (320 + 1)
// #endif

// enum color {
//     white       = 0xffff,
//     black       = 0x0000,

//     red         = 0xf800,
//     green       = 0x07e0,
//     blue        = 0x001f,

//     purple      = 0x780f,
//     yellow      = 0xffe0,
//     orange      = 0xfd20,
//     orange_red  = 0xfa20,
//     sun_orange  = 0xfb80,
//     strong_red  = 0xe000,
//     hot_pink    = 0xf8b2,
//     misty_rose  = 0xff3c,
//     sea_green   = 0x2c4a,
//     apple_green = 0x8f20,
//     tomato      = 0xfb08,
//     brown       = 0xa145,
//     olive       = 0x8400,
//     cyan        = 0x07ff,
//     dimcyan     = 0x03ff,
//     dimgray     = 0x7bef,
//     light_gray  = 0xc618,
//     magenta     = 0xf81f
// };

static void ili9341_gpio_init();
static void ili9341_fsmc_init();

extern void ili9341_write_command(uint16_t command);
extern void ili9341_write_data(uint16_t command);
extern void ili9341_write_register(unsigned int register_address, unsigned int register_value);
extern void ili9341_reset();
extern void ili9341_backlight(unsigned char state);
extern void ili9341_direction(unsigned char direction);
extern void ili9341_init();
extern void display_position(unsigned int y, unsigned int x);
extern void ili9341_display_region(unsigned int y, unsigned int x, unsigned int width, unsigned int height);

#endif
