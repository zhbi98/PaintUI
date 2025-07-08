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

#define DISPLAY_LENGTH_MAX 6U
#define MINIWIN_MAXL 6U

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uint8_t val_type;
    uint8_t cur_pos;
    uint8_t start_pos;
    uint8_t pos_change;
    void * bechg_val;
    double data;
    uint8_t valstr[32];
    uint8_t vallen;
    uint8_t cur_movlim;
    uint8_t disp_len_max;
    /**
     * When the data value is expressed in standard units,
     * the character length of the data value,
     * example In millivolts as the standard unit
     */
    uint8_t std_unit_len_max; 
    /*disp_buf[0][40] raw string*/
    /*disp_buf[1][40] is display string*/
    uint8_t disp_buf[2][40];
} _regu_t;

extern _regu_t regu;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void regu_val_set_type(uint8_t _type);
uint8_t regut_val_ge_type();
void regu_get_changed_val();
void regu_fmtval_refer();
uint8_t regu_valid_bit_get_idx(uint8_t * string);
uint8_t regu_first_bit_refer(_regu_t * regu, uint8_t firstbit_idx);
void regu_fmt_str_refer();
void regu_LR_move(int32_t lr);
void regu_UD_move(int32_t incr);
void regu_disp_digits_req(int32_t start, int32_t length);
void regu_dec_point_add(uint8_t point_position);
void regu_Nsign_add();
void regu_separator_add(uint8_t character);
void regu_disp_get_str(uint8_t _type);
uint8_t regu_cursor_get_pos();
void regu_cursor_pos_reset();

#endif
