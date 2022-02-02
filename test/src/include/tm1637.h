
#ifndef __TM1637_H__
#define __TM1637_H__

#include "stm32f4xx.h"
#include "time.h"

#define TM1637_SDA_GPIO    GPIOC
#define TM1637_SDA_PIN     GPIO_Pin_0
#define TM1637_SDA_CLOCK   RCC_AHB1Periph_GPIOC

#define TM1637_SCL_GPIO    GPIOE
#define TM1637_SCL_PIN     GPIO_Pin_6
#define TM1637_SCL_CLOCK   RCC_AHB1Periph_GPIOE

#define TM1637_START 1
#define TM1637_STOP  0

extern unsigned char num_code[];
extern unsigned char twinkle_code[];

struct hou {
	unsigned char ten;
	unsigned char bits;
} hour;

struct min {
	unsigned char ten;
	unsigned char bits;
} minute;

extern unsigned char twinkle;

static void tm1637_sda_input();
static void tm1637_sda_output();

extern void tm1637_gpio_init();
extern void tm1637_onoff(unsigned char state);
extern void check_tm1637_ack();
extern void tm1637_send_bit(unsigned char a_bit);
extern void tm1637_send_byte(unsigned char a_byte);
extern void write_command(unsigned char command);
extern void write_data(unsigned char address, unsigned char dat_a);
extern void display_value(unsigned int value);
extern void display_time(unsigned char h, unsigned m);
extern void display_off();

#endif
