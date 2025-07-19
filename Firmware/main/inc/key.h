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
#include "gpio.h"

/*********************
 *      DEFINES
 *********************/

#define key0_level() (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) << 7
#define key1_level() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) << 6
#define key2_level() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) << 5
#define key3_level() GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) << 4

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
  bool phold;
  uint32_t dura; /**< duration pressed time*/
  uint32_t interval; /**< pressed active speed*/
} key_event_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void key_gpio_init();
uint8_t key_get_event();

#endif
