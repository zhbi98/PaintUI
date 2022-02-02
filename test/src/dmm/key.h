
#ifndef __KEY_H__
#define __KEY_H__

#include <stdbool.h>

#include "stm32f4xx.h"

#include "display.h"
#include "display_controller.h"

#define F1_KEY_GPIO  GPIOA
#define F1_KEY_PIN   GPIO_Pin_0
#define F1_KEY_CLOCK RCC_AHB1Periph_GPIOA

#define F2_KEY_GPIO  GPIOE
#define F2_KEY_PIN   GPIO_Pin_2
#define F2_KEY_CLOCK RCC_AHB1Periph_GPIOE

#define F3_KEY_GPIO  GPIOE
#define F3_KEY_PIN   GPIO_Pin_3
#define F3_KEY_CLOCK RCC_AHB1Periph_GPIOE

#define F4_KEY_GPIO  GPIOE
#define F4_KEY_PIN   GPIO_Pin_4
#define F4_KEY_CLOCK RCC_AHB1Periph_GPIOE

#define F1_KEY_STATUS() GPIO_ReadInputDataBit(F1_KEY_GPIO, F1_KEY_PIN)
#define F2_KEY_STATUS() GPIO_ReadInputDataBit(F2_KEY_GPIO, F2_KEY_PIN)
#define F3_KEY_STATUS() GPIO_ReadInputDataBit(F3_KEY_GPIO, F3_KEY_PIN)
#define F4_KEY_STATUS() GPIO_ReadInputDataBit(F4_KEY_GPIO, F4_KEY_PIN)

#define F1_KEY_EVT   ('1')
#define F2_KEY_EVT   ('2')
#define F3_KEY_EVT   ('3')
#define F4_KEY_EVT   ('4')
#define PREV_KEY_EVT ('<')
#define NEXT_KEY_EVT ('>')
#define RELEASE      ('0')

struct key_event_t {
    // false: short pressed event
    // true : long pressed event
    bool press_long;
    // duration pressed time
    unsigned int press_duration;
    // pressed active speed
    unsigned int active_time;
};

extern struct key_event_t key_evt;

extern void key_gpio_init();
extern void key_event_ticks();
extern unsigned char read_key_event();

#endif
