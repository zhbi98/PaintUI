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

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

key_event_t key_evt = {
  .phold = false,
  .dura = 400,
  .interval = 29,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Generates keyboard drive code by 
 * reading physical key status.
 * @return 8-bit drive code pattern: Bit7-Bit6 Physical keys, 
 * Bit5-Bit0 Reserved bits (fixed to 1).     
 */
static uint8_t key_drive_code()
{
  uint8_t val = 0xFF;

  val = (val & 0x7F) | key0_level();
  val = (val & 0xBF) | key1_level();
  val = (val & 0xDF) | key2_level();
  val = (val & 0xEF) | key3_level();

  return val;
}

/**
 * Decrements timing counters for key event handling.
 * Should be called periodically (e.g., every 10ms).
 */
static void key_tick_work()
{
  if (key_evt.interval > 0)
    key_evt.interval--;
  if (key_evt.dura > 0)
    key_evt.dura--;
}

/**
 * Detects and processes keyboard events
 * @return Detected key event code: KEY0_EVT(0x7F): 
 * key0 pressed, KEY1_EVT(0xBF): key1 pressed, 
 * RELEASE(0x00): No key activity.
 */
uint8_t key_get_event()
{
  static uint8_t k_old = RELEASE;
  uint8_t drive_code = 0;
  uint8_t val = 0;

  drive_code = key_drive_code();

  switch (drive_code) {
  case 0x7F:
    val = F1_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F1_BTN].valid)
      actbar_btn_pressed(F1_KEY_EVT);
    break;
  case 0xBF:
    val = F2_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F2_BTN].valid)
      actbar_btn_pressed(F2_KEY_EVT);
    break;
  case 0xDF:
    val = F3_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F3_BTN].valid)
      actbar_btn_pressed(F3_KEY_EVT);
    break;
  case 0xEF:
    val = F4_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_F4_BTN].valid)
      actbar_btn_pressed(F4_KEY_EVT);
    break;
  case 0x00:
    val = PREV_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_PREV_BTN].valid)
      actbar_btn_pressed(PREV_KEY_EVT);
    break;
  case 0x01:
    val = NEXT_KEY_EVT;
    /*key pressed to display the effect*/
    if (_Area[DMM_NEXT_BTN].valid)
      actbar_btn_pressed(NEXT_KEY_EVT);
    break;
  default:
    val = RELEASE;
    break;
  }

  if (val == RELEASE) key_evt.dura = 400;

  /*key2 Unsupport long press auto trigger active*/
  if (key_evt.dura <= 0) key_evt.phold = true;
  else key_evt.phold = false;

  key_tick_work();

  if (key_evt.phold == true) {
    if (key_evt.interval <= 0) {
      key_evt.interval = 29;
      return val;
    } else return RELEASE;
  }

  /**
   * Pressed event
   * if ((val != RELEASE) && (k_old == RELEASE)) {
   *     k_old = val;
   *     return val;
   * } else {
   *     k_old = val;
   *     return RELEASE;
   * }
   */

  /*Released event */
  if ((val == RELEASE) && (k_old != RELEASE)) {
    drive_code = k_old;
    k_old = RELEASE;
    return drive_code;
  } else {
    k_old = val;
    return RELEASE;
  }

  return 0;
}
