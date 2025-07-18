/**
 * @file voltage_v.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdio.h>
#include "voltage_v.h"
#include "setup.h"
#include "display_controller.h"
#include "display_string.h"
#include "display.h"
#include "menu_str.h"
#include "key.h"

_volt_t _volt = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void volt_level1_menu(uint8_t key_event, uint8_t * vm)
{
  uint8_t page = act_bar_get_page(&_dmm_actbar);

  if (_volt.state == VOLT_DC) {
    if (page == VOLT_LEFT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_ACDC, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        break;

      case NEXT_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, INVE_NONE, vm);
        break;
      }
    } 

    if (page == VOLT_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_RANGE, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_MAX, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_REL, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F4_BTN, NULL, MENU_HOLD, WHITE, INVE_NONE, vm);
        break;

      case PREV_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, INVE_NONE, vm);
        break;

      case NEXT_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, INVE_NONE, vm);
        break;
      }
    } 

    if (page == VOLT_RIGHT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_COMP, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_REC, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_SAVE, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F4_BTN, NULL, MENU_LOG, WHITE, INVE_NONE, vm);
        break;

      case PREV_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, INVE_NONE, vm);
        break;

      case NEXT_KEY_EVT:
        break;
      }
    }
  }

  if (_volt.state == VOLT_AC) {
    if (page == VOLT_LEFT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_ACDC, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_LO, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_PEAK, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        break;

      case NEXT_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, INVE_NONE, vm);
        break;
      }
    }

    if (page == VOLT_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_RANGE, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_MAX, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_REL, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F4_BTN, NULL, MENU_HOLD, WHITE, INVE_NONE, vm);
        break;

      case PREV_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, INVE_NONE, vm);
        break;

      case NEXT_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, INVE_NONE, vm);
        break;
      }
    }

    if (page == VOLT_RIGHT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_COMP, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_REC, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_SAVE, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F4_BTN, NULL, MENU_LOG, WHITE, INVE_NONE, vm);
        break;

      case PREV_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, INVE_NONE, vm);
        break;

      case NEXT_KEY_EVT:
        break;
      }
    }
  }
}

void volt_level1_key_event(uint8_t key_event)
{
  uint8_t page = act_bar_get_page(&_dmm_actbar);

  if (_volt.state == VOLT_DC) {
    if (page == VOLT_LEFT) {
      switch (key_event) {
      case F1_KEY_EVT:
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        break;

      case NEXT_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_CENTER);
        break;
      }
    }

    if (page == VOLT_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        alerts_call(&alerts[0], NULL, STMS_TICKS(100, 500));
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_LEFT);
        break;

      case NEXT_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_RIGHT);
        break;
      }
    }

    if (page == VOLT_RIGHT) {
      switch (key_event) {
      case F1_KEY_EVT:
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_CENTER);
        break;

      case NEXT_KEY_EVT:
        break;
      }
    }
  }

  if (_volt.state == VOLT_AC) {
    if (page == VOLT_LEFT) {
      switch (key_event) {
      case F1_KEY_EVT:
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        break;

      case NEXT_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_CENTER);
        break;
      }
    }

    if (page == VOLT_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_LEFT);
        break;

      case NEXT_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_RIGHT);
        break;
      }
    }

    if (page == VOLT_RIGHT) {
      switch (key_event) {
      case F1_KEY_EVT:
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, VOLT_LEFT);
        break;

      case NEXT_KEY_EVT:
        break;
      }
    }
  }
}

void volt_level1_key_event_enable(uint8_t key_event)
{
  uint8_t page = act_bar_get_page(&_dmm_actbar);

  if (_volt.state == VOLT_DC) {
    if (page == VOLT_LEFT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == VOLT_CENTER) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == VOLT_RIGHT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }
  }

  if (_volt.state == VOLT_AC) {
    if (page == VOLT_LEFT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == VOLT_CENTER) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == VOLT_RIGHT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }
  }
}

void volt_select()
{
  if (act_bar_get_func(&_dmm_actbar) != DMM_VOLTAGE_V) return;
  act_bar_set_page(&_dmm_actbar, VOLT_CENTER);
  _volt.state++;
  if (_volt.state > VOLT_AC)
    _volt.state = VOLT_DC; 
}
