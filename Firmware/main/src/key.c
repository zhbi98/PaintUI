/**
 * @file key.h
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include "display_controller.h"
#include "display.h"
#include "key.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void key_gpio_init()
{
  GPIO_InitTypeDef gpio_init;

  RCC_AHB1PeriphClockCmd(
    RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(
    RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_AHB1PeriphClockCmd(
    RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_AHB1PeriphClockCmd(
    RCC_AHB1Periph_GPIOE, ENABLE);

  gpio_init.GPIO_Pin = GPIO_Pin_0;
  gpio_init.GPIO_Mode = GPIO_Mode_IN;
  gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &gpio_init);

  gpio_init.GPIO_Pin = GPIO_Pin_2;
  gpio_init.GPIO_Mode = GPIO_Mode_IN;
  gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &gpio_init);

  gpio_init.GPIO_Pin = GPIO_Pin_3;
  gpio_init.GPIO_Mode = GPIO_Mode_IN;
  gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &gpio_init);

  gpio_init.GPIO_Pin = GPIO_Pin_4;
  gpio_init.GPIO_Mode = GPIO_Mode_IN;
  gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &gpio_init);
}

key_event_t key_evt = {
  .press_long = false,
  .press_duration = 400,
  .active_time = 29,
};

uint8_t key_drive_code()
{
  uint8_t t = 0x00;

  t = (t << 1) | !F1_KEY_STATUS();
  t = (t << 1) |  F2_KEY_STATUS();
  t = (t << 1) |  F3_KEY_STATUS();
  t = (t << 1) |  F4_KEY_STATUS();
  t = (t << 1) | (0x01);
  t = (t << 1) | (0x01);
  t = (t << 1) | (0x01);
  t = (t << 1) | (0x01);

  return t;
}

void key_event_ticks()
{
  if (key_evt.press_duration != 0) {
    key_evt.press_duration--;
  }
  if (key_evt.active_time != 0) {
    key_evt.active_time--;
  }
}

uint8_t read_key_event()
{
  /**
   * [1110, 1111], <k1, k2, k3, k4, 1, 1, 1, 1>
   * Key follow the code:
   * Key <1> <0x7f>
   * Key <2> <0xbf>
   * Key <3> <0xdf>
   * Key <4> <0xef>
   */

  uint8_t drive_code = 0;
  uint8_t k = 0;
  static uint8_t plast = RELEASE;

  drive_code = key_drive_code();

  switch (drive_code) {
  case 0x7f:
    k = F1_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F1_BTN].valid)
      actbar_btn_pressed(F1_KEY_EVT);
    break;
  case 0xbf:
    k = F2_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F2_BTN].valid)
      actbar_btn_pressed(F2_KEY_EVT);
    break;
  case 0xdf:
    k = F3_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F3_BTN].valid)
      actbar_btn_pressed(F3_KEY_EVT);
    break;
  case 0xef:
    k = F4_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F4_BTN].valid)
      actbar_btn_pressed(F4_KEY_EVT);
    break;
  case 0x00:
    k = PREV_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_PREV_BTN].valid)
      actbar_btn_pressed(PREV_KEY_EVT);
    break;
  case 0x01:
    k = NEXT_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_NEXT_BTN].valid)
      actbar_btn_pressed(NEXT_KEY_EVT);
    break;
  default:
    k = RELEASE;
    break;
  }

  if (k == RELEASE) {
    key_evt.press_duration = 400;
  }

  /*key 5 unsupport long press auto trigger active*/
  if ((key_evt.press_duration <= 0)/* && (k != KEY5_EVT)*/) {
    key_evt.press_long = true;
  } else {
    key_evt.press_long = false;
  }

  key_event_ticks();

  if (key_evt.press_long == true) {
    if (key_evt.active_time <= 0) {
      key_evt.active_time = 29;
      return k;
    } else {
      return RELEASE;
    }
  }

  /*Pressed event
  if ((k != RELEASE) && (plast == RELEASE)) {
      plast = k;
      return k;
  } else {
      plast = k;
      return RELEASE;
  }*/

  /*Released event */
  if ((k == RELEASE) && (plast != RELEASE)) {
    drive_code = plast;
    plast = RELEASE;
    return drive_code;
  } else {
    plast = k;
    return RELEASE;
  }
}
