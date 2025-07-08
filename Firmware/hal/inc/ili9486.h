
#ifndef __ILI9486_H__
#define __ILI9486_H__

#include "stm32f4xx.h"

#include <stdio.h>
#include <stdarg.h>

#include "time.h"

/*
					STM32F4 Board TFT Interface
	31   29  27  25  23  21  19  17  15  13  11  9   7   5     3   1
	VCC  NC  NC  NC  NC  RS  RD  D1  D3  D5  D7  D9  D11 D13 D15 GND

	32   30  28  26  24  22  20  18  16  14  12  10  8   6     4   2
	GND  GND BL  NC  NC  CS  WR  D0  D2  D4  D6  D8  D10 D12 D14 RST

	Fsmc_A18    command/data         RS
	FSMC_NOE    read enable          RD
	FSMC_NWE    write enable         WR
	FSMC_NE1    chip select          CS
	FSMC_D0-D15 16 bit data bus  D0-D15
    
    RST pin must connection	
	hardware reset                  RST
	back light                       BL
*/

#define FSMC_BANK1_NORSRAM    FSMC_Bank1_NORSRAM1
#define FSMC_CLOCK            RCC_AHB3Periph_FSMC

#define ILI9486_WRITE_COMMAND ((uint32_t)0x60000000)
#define ILI9486_WRITE_DATA    ((uint32_t)0x60080000)

#define ILI9486_RS_GPIO    GPIOD
#define ILI9486_RS_PIN     GPIO_Pin_13
#define ILI9486_RS_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_RS_AF      GPIO_AF_FSMC
#define ILI9486_RS_SRC     GPIO_PinSource13

#define ILI9486_RD_GPIO    GPIOD
#define ILI9486_RD_PIN     GPIO_Pin_4
#define ILI9486_RD_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_RD_AF      GPIO_AF_FSMC
#define ILI9486_RD_SRC     GPIO_PinSource4

#define ILI9486_WR_GPIO    GPIOD
#define ILI9486_WR_PIN     GPIO_Pin_5
#define ILI9486_WR_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_WR_AF      GPIO_AF_FSMC
#define ILI9486_WR_SRC     GPIO_PinSource5

#define ILI9486_CS_GPIO    GPIOE
#define ILI9486_CS_PIN     GPIO_Pin_7
#define ILI9486_CS_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_CS_AF      GPIO_AF_FSMC
#define ILI9486_CS_SRC     GPIO_PinSource7

#define ILI9486_RST_GPIO   GPIOA
#define ILI9486_RST_PIN    GPIO_Pin_0
#define ILI9486_RST_CLOCK  RCC_AHB1Periph_GPIOA

#define ILI9486_BL_GPIO    GPIOA
#define ILI9486_BL_PIN     GPIO_Pin_1
#define ILI9486_BL_CLOCK   RCC_AHB1Periph_GPIOA

#define ILI9486_D0_GPIO    GPIOD
#define ILI9486_D0_PIN     GPIO_Pin_14
#define ILI9486_D0_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_D0_AF      GPIO_AF_FSMC
#define ILI9486_D0_SRC     GPIO_PinSource14

#define ILI9486_D1_GPIO    GPIOD
#define ILI9486_D1_PIN     GPIO_Pin_15
#define ILI9486_D1_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_D1_AF      GPIO_AF_FSMC
#define ILI9486_D1_SRC     GPIO_PinSource15

#define ILI9486_D2_GPIO    GPIOD
#define ILI9486_D2_PIN     GPIO_Pin_0
#define ILI9486_D2_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_D2_AF      GPIO_AF_FSMC
#define ILI9486_D2_SRC     GPIO_PinSource0

#define ILI9486_D3_GPIO    GPIOD
#define ILI9486_D3_PIN     GPIO_Pin_1
#define ILI9486_D3_CLOCK   RCC_AHB1Periph_GPIOD
#define ILI9486_D3_AF      GPIO_AF_FSMC
#define ILI9486_D3_SRC     GPIO_PinSource1

#define ILI9486_D4_GPIO    GPIOE
#define ILI9486_D4_PIN     GPIO_Pin_7
#define ILI9486_D4_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_D4_AF      GPIO_AF_FSMC
#define ILI9486_D4_SRC     GPIO_PinSource7

#define ILI9486_D5_GPIO    GPIOE
#define ILI9486_D5_PIN     GPIO_Pin_8
#define ILI9486_D5_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_D5_AF      GPIO_AF_FSMC
#define ILI9486_D5_SRC     GPIO_PinSource8

#define ILI9486_D6_GPIO    GPIOE
#define ILI9486_D6_PIN     GPIO_Pin_9
#define ILI9486_D6_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_D6_AF      GPIO_AF_FSMC
#define ILI9486_D6_SRC     GPIO_PinSource9

#define ILI9486_D7_GPIO    GPIOE
#define ILI9486_D7_PIN     GPIO_Pin_10
#define ILI9486_D7_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_D7_AF      GPIO_AF_FSMC
#define ILI9486_D7_SRC     GPIO_PinSource10

#define ILI9486_D8_GPIO    GPIOE
#define ILI9486_D8_PIN     GPIO_Pin_11
#define ILI9486_D8_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_D8_AF      GPIO_AF_FSMC
#define ILI9486_D8_SRC     GPIO_PinSource11

#define ILI9486_D9_GPIO    GPIOE
#define ILI9486_D9_PIN     GPIO_Pin_12
#define ILI9486_D9_CLOCK   RCC_AHB1Periph_GPIOE
#define ILI9486_D9_AF      GPIO_AF_FSMC
#define ILI9486_D9_SRC     GPIO_PinSource12

#define ILI9486_D10_GPIO   GPIOE
#define ILI9486_D10_PIN    GPIO_Pin_13
#define ILI9486_D10_CLOCK  RCC_AHB1Periph_GPIOE
#define ILI9486_D10_AF     GPIO_AF_FSMC
#define ILI9486_D10_SRC    GPIO_PinSource13

#define ILI9486_D11_GPIO   GPIOE
#define ILI9486_D11_PIN    GPIO_Pin_14
#define ILI9486_D11_CLOCK  RCC_AHB1Periph_GPIOE
#define ILI9486_D11_AF     GPIO_AF_FSMC
#define ILI9486_D11_SRC    GPIO_PinSource14

#define ILI9486_D12_GPIO   GPIOE
#define ILI9486_D12_PIN    GPIO_Pin_15
#define ILI9486_D12_CLOCK  RCC_AHB1Periph_GPIOE
#define ILI9486_D12_AF     GPIO_AF_FSMC
#define ILI9486_D12_SRC    GPIO_PinSource15

#define ILI9486_D13_GPIO   GPIOD
#define ILI9486_D13_PIN    GPIO_Pin_8
#define ILI9486_D13_CLOCK  RCC_AHB1Periph_GPIOD
#define ILI9486_D13_AF     GPIO_AF_FSMC
#define ILI9486_D13_SRC    GPIO_PinSource8

#define ILI9486_D14_GPIO   GPIOD
#define ILI9486_D14_PIN    GPIO_Pin_9
#define ILI9486_D14_CLOCK  RCC_AHB1Periph_GPIOD
#define ILI9486_D14_AF     GPIO_AF_FSMC
#define ILI9486_D14_SRC    GPIO_PinSource9

#define ILI9486_D15_GPIO   GPIOD
#define ILI9486_D15_PIN    GPIO_Pin_10
#define ILI9486_D15_CLOCK  RCC_AHB1Periph_GPIOD
#define ILI9486_D15_AF     GPIO_AF_FSMC
#define ILI9486_D15_SRC    GPIO_PinSource10

#define HORIZONTAL 1U

void ili9486_write_command(uint16_t command);
void ili9486_write_data(uint16_t dat_a);
void ili9486_write_register(uint32_t register_address, uint32_t register_value);
void ili9486_reset();
void ili9486_direction(uint8_t direction);
void ili9486_init();
void display_position(uint32_t y, uint32_t x);
void display_region(uint32_t y, uint32_t x, uint32_t width, uint32_t height);

#endif
