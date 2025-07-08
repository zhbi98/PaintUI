/**
 * @file key.h
 *
 */

#ifndef __KEY_H__
#define __KEY_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include "stm32f4xx.h"

/*********************
 *      DEFINES
 *********************/

#define F1_KEY_STATUS() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define F2_KEY_STATUS() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define F3_KEY_STATUS() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define F4_KEY_STATUS() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)

#define F1_KEY_EVT   ('1')
#define F2_KEY_EVT   ('2')
#define F3_KEY_EVT   ('3')
#define F4_KEY_EVT   ('4')
#define PREV_KEY_EVT ('<')
#define NEXT_KEY_EVT ('>')
#define RELEASE      ('0')

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
  uint32_t press_duration;
  uint32_t active_time;
  bool press_long;
} key_event_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void key_gpio_init();
void key_event_ticks();
uint8_t read_key_event();

#endif
