/**
 * @file gpio.h
 *
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "stm32f4xx.h"

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void dev_gpio_init(void);

#ifdef __cplusplus
}
#endif
#endif /*__GPIO_H__*/
