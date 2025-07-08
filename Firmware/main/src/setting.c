/**
 * @file setting.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "display_controller.h"
#include "display_string.h"
#include "setting.h"
#include "menu_str.h"
#include "display.h"
#include "setup.h"
#include "key.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void setup_level1_menu(uint8_t key_event, uint8_t * vm)
{
  switch (key_event) {
  case F1_KEY_EVT:
    display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
      DMM_F1_BTN, NULL, MENU_MINUS, WHITE, INV_OFF, vm);
    break;

  case F2_KEY_EVT:
    display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
      DMM_F2_BTN, NULL, MENU_UP, WHITE, INV_OFF, vm);
    break;

  case F3_KEY_EVT:
    display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
      DMM_F3_BTN, NULL, MENU_DOWN, WHITE, INV_OFF, vm);
    break;

  case F4_KEY_EVT:
    display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
      DMM_F4_BTN, NULL, MENU_ADD, WHITE, INV_OFF, vm);
    break;

  case PREV_KEY_EVT:
    display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
      DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, INV_OFF, vm);
    break;

  case NEXT_KEY_EVT:
    display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
      DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, INV_OFF, vm);
    break;
  }
}

void setup_level1_key_event(uint8_t key_event)
{
  switch (key_event) {
  case F1_KEY_EVT:
    dev_topbar_cont_flush_enable();
    ctl_tabv_cont_flush_enable();
    lv_time_set_val(-1);
    lv_date_set_val(-1);
    lv_apoff_set_val(-1);
    lv_comp_set_type_val(-1);
    lv_mem_set_val(-1);
    lv_bright_set_val(-1);
    lv_dispoff_set_val(-1);
    lv_voice_set_val(-1);
    lv_dark_set_val(-1);

    if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
      regu_val_set_type(DEV_COMP_MAX);
      regu_UD_move(-1);
    }
    if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
      regu_val_set_type(DEV_COMP_MIN);
      regu_UD_move(-1);
    }
    break;

  case F2_KEY_EVT:
    lv_tab_set_line(-1);
    ctl_tabv_cont_flush_enable();
    break;

  case F3_KEY_EVT:
    lv_tab_set_line(1);
    ctl_tabv_cont_flush_enable();
    break;

  case F4_KEY_EVT:
    dev_topbar_cont_flush_enable();
    ctl_tabv_cont_flush_enable();
    lv_time_set_val(1);
    lv_date_set_val(1);
    lv_apoff_set_val(1);
    lv_comp_set_type_val(1);
    lv_mem_set_val(1);
    lv_bright_set_val(1);
    lv_dispoff_set_val(1);
    lv_voice_set_val(1);
    lv_dark_set_val(1);

    if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
      regu_val_set_type(DEV_COMP_MAX);
      regu_UD_move(1); 
    }
    if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
      regu_val_set_type(DEV_COMP_MIN);
      regu_UD_move(1);
    }
    break;

  case PREV_KEY_EVT:
    ctl_tabv_cont_flush_enable();
    dev_topbar_cont_flush_enable();
    
    lv_tab_set_hidx(-1);
    if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
      regu_val_set_type(DEV_COMP_MAX);
      regu_LR_move(-1);
    }
    if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
      regu_val_set_type(DEV_COMP_MIN);
      regu_LR_move(-1);
    }
    break;

  case NEXT_KEY_EVT:
    ctl_tabv_cont_flush_enable();
    dev_topbar_cont_flush_enable();
    lv_tab_set_hidx(1);
    if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
      regu_val_set_type(DEV_COMP_MAX);
      regu_LR_move(1);
    }
    if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
      regu_val_set_type(DEV_COMP_MIN);
      regu_LR_move(1);
    }
    break;
  }
}

void setup_level1_key_event_enable(uint8_t key_event)
{
  _Area[DMM_F1_BTN].valid   = true;
  _Area[DMM_F2_BTN].valid   = true;
  _Area[DMM_F3_BTN].valid   = true;
  _Area[DMM_F4_BTN].valid   = true;
  _Area[DMM_PREV_BTN].valid = true;
  _Area[DMM_NEXT_BTN].valid = true;
}
