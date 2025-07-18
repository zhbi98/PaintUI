/**
 * @file display_show.h
 *
 */

#ifndef __DISPLAY_SHOW_H__
#define __DISPLAY_SHOW_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void dev_topbar_cont_refer(uint8_t * vm);
void dev_battery_refer(uint8_t * vm);
void dev_buletooth_refer(uint8_t * vm);
void dev_poff_tim_refer(uint8_t * vm);
void dev_trumpet_refer(uint8_t * vm);
void dev_lighting_refer(uint8_t * vm);
void dev_realtim_refer(uint8_t * vm);
void dmm_zone_cont_refer(uint8_t * vm);
void dmm_mea_mod_refer(uint8_t * vm);
void dmm_rec_refer(uint8_t * vm);
void dmm_hold_state_refer(uint8_t * vm);
void dmm_rel_val_refer(uint8_t * vm);
void dmm_ret_cont_refer(uint8_t * vm);
void dev_alerts_refer(uint8_t * vm);
void dmm_ret_val_refer(uint8_t * vm);
void dmm_ret_unit_refer(uint8_t * vm);
void dmm_bcht_cont_refer(uint8_t * vm);
void dmm_mea_lpf_refer(uint8_t * vm);
void dmm_loz_state_refer(uint8_t * vm);
void dmm_bcht_refer(uint8_t * vm);
void dmm_run_state_refer(uint8_t * vm);
void dmm_actbar_cont_fefer(uint8_t * vm);
void dmm_f1_btn_refer(uint8_t * vm);
void dmm_f2_btn_refer(uint8_t * vm);
void dmm_f3_btn_refer(uint8_t * vm);
void dmm_f4_btn_refer(uint8_t * vm);
void dmm_prev_btn_refer(uint8_t * vm);
void dmm_next_btn_refer(uint8_t * vm);
void ctl_tabv_cont_refer(uint8_t * vm);
void ctl_tabv_refer(uint8_t * vm);

#endif /*__DISPLAY_SHOW_H__*/
