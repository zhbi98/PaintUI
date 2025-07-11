/**
 * @file example.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "example_v.h"
#include "display_controller.h"
#include "menu_str.h"

_example_t _example = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void example_level1_menu(uint8_t key_event, uint8_t * vm)
{
  uint8_t page = act_bar_get_page(&_dmm_actbar);

  if (_example.state == EXAM_DC) {
    if (page == EXAM_LEFT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_AC_DC, WHITE, INVE_NONE, vm);
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

    if (page == EXAM_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_RANGE, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_MAX_MIN, WHITE, INVE_NONE, vm);
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

    if (page == EXAM_RIGHT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_COMP, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_AUTO_SAVE, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_MANUAL_SAVE, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F4_BTN, NULL, MENU_VIEW_DATA, WHITE, INVE_NONE, vm);
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

  if (_example.state == EXAM_AC) {
    if (page == EXAM_LEFT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_AC_DC, WHITE, INVE_NONE, vm);
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

    if (page == EXAM_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_RANGE, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_MAX_MIN, WHITE, INVE_NONE, vm);
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

    if (page == EXAM_RIGHT) {
      switch (key_event) {
      case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F1_BTN, NULL, MENU_COMP, WHITE, INVE_NONE, vm);
        break;

      case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F2_BTN, NULL, MENU_AUTO_SAVE, WHITE, INVE_NONE, vm);
        break;

      case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F3_BTN, NULL, MENU_MANUAL_SAVE, WHITE, INVE_NONE, vm);
        break;

      case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, 
          DMM_F4_BTN, NULL, MENU_VIEW_DATA, WHITE, INVE_NONE, vm);
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

void example_level1_key_event(uint8_t key_event)
{
  uint8_t page = act_bar_get_page(&_dmm_actbar);

  if (_example.state == EXAM_DC) {
    if (page == EXAM_LEFT) {
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
        act_bar_set_page(&_dmm_actbar, EXAM_CENTER);
        break;
      }
    }

    if (page == EXAM_CENTER) {
      switch (key_event) {
      case F1_KEY_EVT:
        alerts_call(&alerts[0], STMS_TICKS(100, 500));
        break;

      case F2_KEY_EVT:
        break;

      case F3_KEY_EVT:
        break;

      case F4_KEY_EVT:
        break;

      case PREV_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, EXAM_LEFT);
        break;

      case NEXT_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, EXAM_RIGHT);
        break;
      }
    }

    if (page == EXAM_RIGHT) {
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
        act_bar_set_page(&_dmm_actbar, EXAM_CENTER);
        break;

      case NEXT_KEY_EVT:
        break;
      }
    }
  }

  if (_example.state == EXAM_AC) {
    if (page == EXAM_LEFT) {
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
        act_bar_set_page(&_dmm_actbar, EXAM_CENTER);
        break;
      }
    }

    if (page == EXAM_CENTER) {
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
        act_bar_set_page(&_dmm_actbar, EXAM_LEFT);
        break;

      case NEXT_KEY_EVT:
        act_bar_set_page(&_dmm_actbar, EXAM_RIGHT);
        break;
      }
    }

    if (page == EXAM_RIGHT) {
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
        act_bar_set_page(&_dmm_actbar, EXAM_LEFT);
        break;

      case NEXT_KEY_EVT:
        break;
      }
    }
  }
}

void example_level1_key_event_enable(uint8_t key_event)
{
  uint8_t page = act_bar_get_page(&_dmm_actbar);

  if (_example.state == EXAM_DC) {
    if (page == EXAM_LEFT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == EXAM_CENTER) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == EXAM_RIGHT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }
  }

  if (_example.state == EXAM_AC) {
    if (page == EXAM_LEFT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == EXAM_CENTER) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }

    if (page == EXAM_RIGHT) {
      _Area[DMM_F1_BTN].valid = true;
      _Area[DMM_F2_BTN].valid = true;
      _Area[DMM_F3_BTN].valid = true;
      _Area[DMM_F4_BTN].valid = true;
      _Area[DMM_PREV_BTN].valid = true;
      _Area[DMM_NEXT_BTN].valid = true;
    }
  }
}

void example_select()
{
  if (act_bar_get_func(&_dmm_actbar) != DMM_EXAM_V) return;
  act_bar_set_page(&_dmm_actbar, EXAM_CENTER);
  _example.state++;
  if (_example.state > EXAM_AC)
    _example.state = EXAM_DC; 
}
