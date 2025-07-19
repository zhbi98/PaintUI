/**
 * @file key_doing.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "display_controller.h"
#include "key_doing.h"
#include "nt_pwd.h"
#include "key.h"

/**********************
 *  STATIC VARIABLES
 **********************/

bool pwd_lock = true;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void pwd_call(void * parm)
{
  pwd_lock = (pwd_lock) ? false : true;
  ctl_actbar_cont_flush_enable();
  load_activity(NT_ACT_CTL);
}

nt_pwd_auth_t _auth = {
  .auth_data  = {'B', 'C', 'D'},
  .auth_len   = 3,
  .auth_cb = pwd_call,
  .auth_state = false,
};

void dmm_key_doing(uint8_t event)
{
  switch (event) {
  case F1_KEY_EVT:
    if (_Area[DMM_ACTBAR_CONT].valid) {
      if (_Area[DMM_F1_BTN].valid) {
        dmm_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_dmm_actbar, F1_KEY_EVT);
        dmm_function_key_event(F1_KEY_EVT);
      }
    } else dmm_function_key_event_enable(F1_KEY_EVT);
    break;

  case F2_KEY_EVT:
    if (_Area[DMM_ACTBAR_CONT].valid) {
      if (_Area[DMM_F2_BTN].valid) {
        dmm_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_dmm_actbar, F2_KEY_EVT);
        dmm_function_key_event(F2_KEY_EVT);
      }
    } else dmm_function_key_event_enable(F2_KEY_EVT);
    break;

  case F3_KEY_EVT:
    if (_Area[DMM_ACTBAR_CONT].valid) {
      if (_Area[DMM_F3_BTN].valid) {
        dmm_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_dmm_actbar, F3_KEY_EVT);
        dmm_function_key_event(F3_KEY_EVT);
      }
    } else dmm_function_key_event_enable(F3_KEY_EVT);
    break;

  case F4_KEY_EVT:
    if (_Area[DMM_ACTBAR_CONT].valid) {
      if (_Area[DMM_F4_BTN].valid) {
        dmm_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_dmm_actbar, F4_KEY_EVT);
        dmm_function_key_event(F4_KEY_EVT);
      }
    } else dmm_function_key_event_enable(F4_KEY_EVT);
    break;

  case PREV_KEY_EVT:
    if (_Area[DMM_ACTBAR_CONT].valid) {
      if (_Area[DMM_F4_BTN].valid) {
        dmm_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_dmm_actbar, PREV_KEY_EVT);
        dmm_function_key_event(PREV_KEY_EVT);
      }
    } else dmm_function_key_event_enable(PREV_KEY_EVT);
    break;

  case NEXT_KEY_EVT:
    if (_Area[DMM_ACTBAR_CONT].valid) {
      if (_Area[DMM_F4_BTN].valid) {
        dmm_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_dmm_actbar, NEXT_KEY_EVT);
        dmm_function_key_event(NEXT_KEY_EVT);
      }
    } else dmm_function_key_event_enable(NEXT_KEY_EVT);
    break;
  }
}

void ctl_key_doing(uint8_t event)
{
  switch (event) {
  case F1_KEY_EVT:
    if (_Area[CTL_ACTBAR_CONT].valid) {
      if (_Area[CTL_F1_BTN].valid) {
        ctl_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_ctl_actbar, F1_KEY_EVT);
        ctl_function_key_event(F1_KEY_EVT);
      }
    } else ctl_function_key_event_enable(F1_KEY_EVT);
    break;

  case F2_KEY_EVT:
    if (_Area[CTL_ACTBAR_CONT].valid) {
      if (_Area[CTL_F2_BTN].valid) {
        ctl_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_ctl_actbar, F2_KEY_EVT);
        ctl_function_key_event(F2_KEY_EVT);
      }
    } else ctl_function_key_event_enable(F2_KEY_EVT);
    break;

  case F3_KEY_EVT:
    if (_Area[CTL_ACTBAR_CONT].valid) {
      if (_Area[CTL_F3_BTN].valid) {
        ctl_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_ctl_actbar, F3_KEY_EVT);
        ctl_function_key_event(F3_KEY_EVT);
      }
    } else ctl_function_key_event_enable(F3_KEY_EVT);
    break;

  case F4_KEY_EVT:
    if (_Area[CTL_ACTBAR_CONT].valid) {
      if (_Area[CTL_F4_BTN].valid) {
        ctl_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_ctl_actbar, F4_KEY_EVT);
        ctl_function_key_event(F4_KEY_EVT);
      }
    } else ctl_function_key_event_enable(F4_KEY_EVT);
    break;

  case PREV_KEY_EVT:
    if (_Area[CTL_ACTBAR_CONT].valid) {
      if (_Area[CTL_F4_BTN].valid) {
        ctl_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_ctl_actbar, PREV_KEY_EVT);
        ctl_function_key_event(PREV_KEY_EVT);
      }
    } else ctl_function_key_event_enable(PREV_KEY_EVT);
    break;

  case NEXT_KEY_EVT:
    if (_Area[CTL_ACTBAR_CONT].valid) {
      if (_Area[CTL_F4_BTN].valid) {
        ctl_actbar_cont_flush_enable();
        actbar_btn_pressed(RELEASE);
        act_bar_set_pressed(&_ctl_actbar, NEXT_KEY_EVT);
        ctl_function_key_event(NEXT_KEY_EVT);
      }
    } else ctl_function_key_event_enable(NEXT_KEY_EVT);
    break;
  }
}

void key_event_doing()
{
  uint8_t event = key_get_event();
  uint8_t _act = read_cur_activity();

  if (event != RELEASE) {
    switch (event) {
    case F2_KEY_EVT:
      nt_pwd_read(&_auth, 'B');
      break;
    case F3_KEY_EVT:
      nt_pwd_read(&_auth, 'C');
      break;
    case F4_KEY_EVT:
      nt_pwd_read(&_auth, 'D');
      break;
    default :
      nt_pwd_read(&_auth, 'x');
      break;
    }
  }

  if (_act == NT_ACT_DMM) 
    dmm_key_doing(event);
  else if (_act == NT_ACT_CTL) 
    ctl_key_doing(event);
  else dmm_key_doing(event);
}
