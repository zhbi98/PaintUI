/**
 * @file main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "display_controller.h"
#include "key_doing.h"
#include "display.h"
#include "usart.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int32_t main()
{
  ili9341_init();
  usart_init();
  key_gpio_init();

  _Area_init();
  act_bar_set_func(&_dmm_actbar, 
    DMM_VOLTAGE_V);
  tft_clear(BLACK);
  regu_LR_move(0);

  for (;;) {
    key_event_doing();
    display_flush(req_rendererVM());
    tft_flush(req_rendererVM());
  }

  return 0;
}
