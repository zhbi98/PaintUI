
#ifndef __OV7670_H__
#define __OV7670_H__

#include "gpio.h"
#include "sccb.h"
#include "ov7670conf.h"      

#define OV7670_CS_GPIO     GPIOG
#define OV7670_CS_PIN      GPIO_Pin_15
#define OV7670_CS_CLOCK    RCC_AHB1Periph_GPIOG

#define OV7670_RRST_GPIO   GPIOA
#define OV7670_RRST_PIN    GPIO_Pin_4
#define OV7670_RRST_CLOCK  RCC_AHB1Periph_GPIOA

#define OV7670_RCK_GPIO    GPIOA
#define OV7670_RCK_PIN     GPIO_Pin_6
#define OV7670_RCK_CLOCK   RCC_AHB1Periph_GPIOA

#define OV7670_WREN_GPIO   GPIOG
#define OV7670_WREN_PIN    GPIO_Pin_9
#define OV7670_WREN_CLOCK  RCC_AHB1Periph_GPIOG

#define OV7670_WRST_GPIO   GPIOB
#define OV7670_WRST_PIN    GPIO_Pin_7
#define OV7670_WRST_CLOCK  RCC_AHB1Periph_GPIOB

#define OV7670_VSYNC_GPIO  GPIOA
#define OV7670_VSYNC_PIN   GPIO_Pin_8
#define OV7670_VSYNC_CLOCK RCC_AHB1Periph_GPIOA

#define OV7670_D0_GPIO     GPIOC
#define OV7670_D0_PIN      GPIO_Pin_6
#define OV7670_D0_CLOCK    RCC_AHB1Periph_GPIOC

#define OV7670_D1_GPIO     GPIOC
#define OV7670_D1_PIN      GPIO_Pin_7
#define OV7670_D1_CLOCK    RCC_AHB1Periph_GPIOC

#define OV7670_D2_GPIO     GPIOC
#define OV7670_D2_PIN      GPIO_Pin_8
#define OV7670_D2_CLOCK    RCC_AHB1Periph_GPIOC

#define OV7670_D3_GPIO     GPIOC
#define OV7670_D3_PIN      GPIO_Pin_9
#define OV7670_D3_CLOCK    RCC_AHB1Periph_GPIOC

#define OV7670_D4_GPIO     GPIOC
#define OV7670_D4_PIN      GPIO_Pin_11
#define OV7670_D4_CLOCK    RCC_AHB1Periph_GPIOC

#define OV7670_D5_GPIO     GPIOB
#define OV7670_D5_PIN      GPIO_Pin_6
#define OV7670_D5_CLOCK    RCC_AHB1Periph_GPIOB

#define OV7670_D6_GPIO     GPIOE
#define OV7670_D6_PIN      GPIO_Pin_5
#define OV7670_D6_CLOCK    RCC_AHB1Periph_GPIOE

#define OV7670_D7_GPIO     GPIOE
#define OV7670_D7_PIN      GPIO_Pin_6
#define OV7670_D7_CLOCK    RCC_AHB1Periph_GPIOE

#define OV7670_RCK_H()     (OV7670_RCK_GPIO -> BSRRL = OV7670_RCK_PIN)// GPIO_SetBits(OV7670_RCK_GPIO, OV7670_RCK_PIN)
#define OV7670_RCK_L()     (OV7670_RCK_GPIO -> BSRRH = OV7670_RCK_PIN)// GPIO_ResetBits(OV7670_RCK_GPIO, OV7670_RCK_PIN)

#define OV7670_CS_H()      (OV7670_CS_GPIO -> BSRRL = OV7670_CS_PIN)  // GPIO_SetBits(OV7670_CS_GPIO, OV7670_CS_PIN)
#define OV7670_CS_L()      (OV7670_CS_GPIO -> BSRRH = OV7670_CS_PIN)  // GPIO_ResetBits(OV7670_CS_GPIO, OV7670_CS_PIN)

#define OV7670_VSYNC       GPIOA_IN(8)  // Sync signal detection IO
#define OV7670_WRST        GPIOB_OUT(7) // Write pointer reset
#define OV7670_WREN        GPIOG_OUT(9) // Write FIFO enable
#define OV7670_RRST        GPIOA_OUT(4) // Read pointer reset

// OV7670_DATA() use to read camera data, 
// camera data format is 16 bits, so one
// pixel need read twice, each read 8 bits
// #define OV7670_DATA() ((GPIOC -> IDR & 0x03C0) >> 6) | ((GPIOC -> IDR & 0x0800) >> 7) | ((GPIOB -> IDR & 0x0040) >> 1) | ((GPIOE -> IDR & 0x0060) << 1)                
#define OV7670_DATA() (GPIOE_IN(6) << 7) | (GPIOE_IN(5) << 6) | (GPIOB_IN(6) << 5) | (GPIOC_IN(11) << 4) | (GPIOC_IN(9) << 3) | (GPIOC_IN(8) << 2) | (GPIOC_IN(7) << 1) | (GPIOC_IN(6) << 0) 

extern unsigned char frame;
                 
extern unsigned char ov7670_init();
extern void exti8_init();
extern void read_image(uint32_t n, unsigned int *vm);
extern void ov7670_light_mode(unsigned char mode);
extern void ov7670_color_saturation(unsigned char sat);
extern void ov7670_brightness(unsigned char bright);
extern void ov7670_contrast(unsigned char contrast);
extern void ov7670_special_effects(unsigned char eft);
extern void image_size(unsigned int x, unsigned int y, unsigned int width,unsigned int height);

#endif
