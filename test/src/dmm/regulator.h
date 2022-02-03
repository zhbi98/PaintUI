
#ifndef __REGULATOR_H__
#define __REGULATOR_H__

#include <math.h>
#include <string.h>

#include "log.h"
#include "setting.h"

#define DISPLAY_LENGTH_MAX 6U
#define MINIWIN_MAXL 6U

struct value_regulator_t {
    unsigned char current_value_type;
    unsigned char cursor_position;
    unsigned char start_position;
    unsigned char position_change;

    void * be_changed_value;
    double data;
    unsigned char value_string[32];
    unsigned char value_length;

    unsigned char cursor_move_limit;
    unsigned char display_length_max;
    // When the data value is expressed in standard units,
    // the character length of the data value,
    // example In millivolts as the standard unit
    unsigned char standard_unit_length_max; 

    // display_buf[0][40] raw string
    // display_buf[1][40] is display string
    unsigned char display_buf[2][40];
};

extern struct value_regulator_t value_regulator;

extern void set_value_type(unsigned char param_type);
extern unsigned char get_value_type();

extern void read_need_changed_value();
extern void value_format();

extern unsigned char value_valid_bit_index(unsigned char * string);
extern unsigned char renew_first_bit(struct value_regulator_t * value_regulator, unsigned char fir_bit_num);
extern void renew_value_format_string();

extern void digit_lr_move(int lr);
extern void value_ud_flip(int incr);

extern void read_display_number_of_digits(int start, int length);
extern void add_decimal_point(unsigned char point_position);
extern void add_separator(unsigned char character);
extern void read_display_part_string(unsigned char param_type);
extern unsigned char read_cursor_position();
extern void reset_cursor_position();

#endif
