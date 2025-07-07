/**
 * @file key_doing.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "key_doing.h"
#include "nt_pwd.h"
#include "key.h"

/**********************
 *  STATIC VARIABLES
 **********************/

bool pwd_cal_lock = true;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void pwd_call(void * parm)
{
  pwd_cal_lock = (pwd_cal_lock) ? false : true;
  load_activity(NT_ACT_CTL);
}

nt_pwd_auth_t cal_auth = {
  .auth_data  = {'B', 'C', 'D'},
  .auth_len   = 3,
  .auth_cb = pwd_call,
  .auth_state = false,
};

void key_event_doing()
{
  static uint8_t release = true;
  uint8_t event = read_key_event();

  if ((_Area[DMM_F1_BTN].valid == true) && 
    (F1_KEY_STATUS() == 1)
  ){
    actbar_btn_pressed(F1_KEY_EVT);
    release = true;
  }
  if ((_Area[DMM_F2_BTN].valid == true) && 
    (F2_KEY_STATUS() == 0)
  ) {
    actbar_btn_pressed(F2_KEY_EVT);
    release = true;
  }
  if ((_Area[DMM_F3_BTN].valid == true) && 
    (F3_KEY_STATUS() == 0)
  ){
    actbar_btn_pressed(F3_KEY_EVT);
    release = true;
  }
  if ((_Area[DMM_F4_BTN].valid == true) && 
    (F4_KEY_STATUS() == 0)
  ){
    actbar_btn_pressed(F4_KEY_EVT);
    release = true;
  }

  if (
    (F1_KEY_STATUS() == 0) && 
    (F2_KEY_STATUS() == 1) && 
    (F3_KEY_STATUS() == 1) && 
    (F4_KEY_STATUS() == 1)
  ) {
    if (release == true) {
      actbar_btn_pressed(RELEASE);
      release = false;
    }
  }

  if (event != RELEASE) {
    switch (event) {
    case F1_KEY_EVT:
      nt_pwd_read(&cal_auth, 'B');
      break;
    case F2_KEY_EVT:
      nt_pwd_read(&cal_auth, 'C');
      break;
    case F3_KEY_EVT:
      nt_pwd_read(&cal_auth, 'D');
      break;
    default :
      nt_pwd_read(&cal_auth, 'x');
      break;
    }
  }

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
