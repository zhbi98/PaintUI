/**
 * @file regulator.h
 *
 */

#ifndef __REGULATOR_H__
#define __REGULATOR_H__

/*********************
 *      INCLUDES
 *********************/

#include <string.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define DISP_LEN_MAX 6U
#define MINIWIN_MAXL 6U

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
  uint8_t cur_movlim;
  uint8_t start_pos;
  uint8_t cur_pos;
  uint8_t pos_change;
  uint8_t val_type;
  void * bechg_val;
  double data;
  /**When the data value is expressed in standard units, 
  the character length of the data value, example 
  In millivolts as the standard unit*/
  uint8_t std_unit_len;
  uint8_t displen;

  uint8_t valstr[32];
  uint8_t vallen;

  /**refer[0][40] Raw string*/
  /**refer[1][40] is Display string*/
  uint8_t refer[2][40];
} _regu_t;

extern _regu_t regu;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void regu_val_set_type(uint8_t _type);
uint8_t regut_val_ge_type();
void regu_dec_point_add(uint8_t _pos);
void regu_Nsign_add();
void regu_separator_add(uint8_t _char);
void regu_LR_move(int32_t val);
void regu_UD_move(int32_t val);
uint8_t regu_cursor_get_pos();
void regu_cursor_pos_reset();
void regu_disp_get_str(uint8_t _type);

#endif
