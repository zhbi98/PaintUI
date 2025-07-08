
#ifndef __REGULATOR_H__
#define __REGULATOR_H__

#include <math.h>
#include <string.h>

#include "log.h"
#include "setting.h"

#define DISPLAY_LENGTH_MAX 6U
#define MINIWIN_MAXL 6U

struct value_regulator_t {
    uint8_t current_value_type;
    uint8_t cursor_position;
    uint8_t start_position;
    uint8_t position_change;

    void * be_changed_value;
    double data;
    uint8_t value_string[32];
    uint8_t value_length;

    uint8_t cursor_move_limit;
    uint8_t display_length_max;
    // When the data value is expressed in standard units,
    // the character length of the data value,
    // example In millivolts as the standard unit
    uint8_t standard_unit_length_max; 

    // display_buf[0][40] raw string
    // display_buf[1][40] is display string
    uint8_t display_buf[2][40];
};

extern struct value_regulator_t value_regulator;

extern void set_value_type(uint8_t param_type);
extern uint8_t get_value_type();

extern void read_need_changed_value();
extern void value_format();

extern uint8_t value_valid_bit_index(uint8_t * string);
extern uint8_t renew_first_bit(struct value_regulator_t * value_regulator, uint8_t fir_bit_num);
extern void renew_value_format_string();

extern void digit_lr_move(int lr);
extern void value_ud_flip(int incr);

extern void read_display_number_of_digits(int start, int length);
extern void add_decimal_point(uint8_t point_position);
extern void add_negative_sign();
extern void add_separator(uint8_t character);
extern void read_display_part_string(uint8_t param_type);
extern uint8_t read_cursor_position();
extern void reset_cursor_position();

#endif
