
#ifndef __W25Q16S_H__
#define __W25Q16S_H__

#include "stm32f4xx.h"
#include "time.h"

#define W25Q16S_MISO_GPIO  GPIOB
#define W25Q16S_MISO_PIN   GPIO_Pin_4
#define W25Q16S_MISO_CLOCK RCC_AHB1Periph_GPIOB

#define W25Q16S_MOSI_GPIO  GPIOB
#define W25Q16S_MOSI_PIN   GPIO_Pin_5
#define W25Q16S_MOSI_CLOCK RCC_AHB1Periph_GPIOB

#define W25Q16S_SCLK_GPIO  GPIOB
#define W25Q16S_SCLK_PIN   GPIO_Pin_3
#define W25Q16S_SCLK_CLOCK RCC_AHB1Periph_GPIOB

#define W25Q16S_CS_GPIO    GPIOB
#define W25Q16S_CS_PIN     GPIO_Pin_0
#define W25Q16S_CS_CLOCK   RCC_AHB1Periph_GPIOB

#define WRITE_ENABLE       0x06
#define WRITE_DISABLE      0x04
#define READ_STATUS        0x05
#define WRITE_STATUS       0x01
#define READ_DATA          0x03
#define FAST_READ_DATA     0x0b
#define FAST_READ_DUAL     0x3b
#define PAGE_PROGRAM       0x02
#define BLOCK_ERASE        0xd8
#define SECTOR_ERASE       0x20
#define CHIP_ERASE         0xc7
#define POWER_OFF          0xb9
#define RELEASE_POWEROFF   0xab
#define DEVICE_ID          0xab
#define FACT_DEVICE_ID     0x90
#define JEDEC_DEVICE_ID    0x9f

#define W25Q16S_ID   	   0xef4015
#define DUMMY_BYTE 		   0xff

extern unsigned char read_buffers[];

static void w25q16s_gpio_init();

extern void w25q16s_spibus_init();

static void w25q16s_send_bit(unsigned char a_bit);
static void w25q16s_send(unsigned char a_byte);
static unsigned char w25q16s_receive();
static unsigned char w25q16s_send_byte(unsigned char a_byte);

extern unsigned int read_w25q16s_id();

static void w25q16s_write_enable();
static void tesing_w25q16s_busy();

extern void w25q16s_sector_erase(unsigned int address);
extern void w25q16s_page_write(unsigned int address, unsigned char lenth, unsigned char *string);
extern void w25q16s_write_pro(unsigned int address, unsigned char lenth, unsigned char *string);
extern void w25q16s_read_data(unsigned int address, unsigned char lenth);

#endif
