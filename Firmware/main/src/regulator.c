
#include "regulator.h"

struct value_regulator_t value_regulator;

void set_value_type(uint8_t param_type)
{
    value_regulator.current_value_type = param_type;
}

uint8_t get_value_type()
{
    return value_regulator.current_value_type;
}

void read_need_changed_value()
{
    static double temp_data;

    value_regulator.data = 0;
    value_regulator.be_changed_value = (void *)&temp_data;

    if (get_value_type() == DEV_COMP_MAX)
        *((int *)value_regulator.be_changed_value) = abs(_devset.comp.max);

    if (get_value_type() == DEV_COMP_MIN)
        *((int *)value_regulator.be_changed_value) = abs(_devset.comp.min);

    if (value_regulator.data == 0)
        value_regulator.data = *((int *)value_regulator.be_changed_value);
}

void value_format()
{
    value_regulator.display_length_max = DISPLAY_LENGTH_MAX;

    read_need_changed_value();

    if (get_value_type() == DEV_COMP_MAX) {
        sprintf(value_regulator.value_string, "%06d", *((int *)value_regulator.be_changed_value));
        value_regulator.display_length_max = 6;
        value_regulator.standard_unit_length_max = 6;
        value_regulator.cursor_move_limit = value_regulator.standard_unit_length_max - 1;
        value_regulator.value_length = strlen(value_regulator.value_string);
    }

    if (get_value_type() == DEV_COMP_MIN) {
        sprintf(value_regulator.value_string, "%06d", *((int *)value_regulator.be_changed_value));
        value_regulator.display_length_max = 6;
        value_regulator.standard_unit_length_max = 6;
        value_regulator.cursor_move_limit = value_regulator.standard_unit_length_max - 1;
        value_regulator.value_length = strlen(value_regulator.value_string);
    }

    if (value_regulator.value_length > 16 || value_regulator.display_length_max > DISPLAY_LENGTH_MAX) {
        value_regulator.value_length = 0;
        value_regulator.display_length_max = MINIWIN_MAXL;
    }
}

uint8_t value_valid_bit_index(uint8_t * string)
{
    uint8_t length;
    uint8_t valid_bit_index;

    length = strlen(string);
    // info("parameter bit length:%d", length);

    if ((length <= 0) || (length > 6))
        return 0;

    for (uint8_t i = 0; i <= length; i++) {
        if (string[i] != '0') {
            valid_bit_index = i;
            // info("first valid bit index:%d", valid_bit_index);
            break;
        }
    }

    if (valid_bit_index >= length)
        valid_bit_index = length - 1;

    if (valid_bit_index > 6)
        valid_bit_index = 6;

    if (string[valid_bit_index] == '.')
        valid_bit_index--;

    return valid_bit_index;
}

uint8_t renew_first_bit(struct value_regulator_t * value_regulator, uint8_t fir_bit_num)
{
    uint8_t length;
    uint8_t curlen;

    length = value_regulator->value_length;
    curlen = length - value_regulator->start_position;

    if (curlen > value_regulator->display_length_max)
        curlen = value_regulator->display_length_max;

    if (curlen == value_regulator->display_length_max) {
        if ((value_regulator->cursor_position - fir_bit_num) < value_regulator->display_length_max)
            return true;
    } else
        return true;

    return false;
}

void renew_value_format_string()
{
    uint8_t valid_bit_index;
    uint8_t reflesh;

    value_format();

    valid_bit_index = value_valid_bit_index(value_regulator.value_string);
    reflesh = renew_first_bit(&value_regulator, valid_bit_index);

    if (reflesh || (value_regulator.position_change != false))
        value_regulator.start_position = valid_bit_index;

    if (value_regulator.position_change != false)
        value_regulator.cursor_position = value_regulator.start_position;

    value_regulator.position_change = true;
}

void digit_lr_move(int lr)
{
    /**
     * value = pow(10, (6 - value_regulator.cursor_position)) * incr
     * -------------------------------------------------------------
     * example incr = -1:
     * value = 100 + pow(10, (2 - value_regulator.cursor_position)) * -1
     * value_regulator.cursor_position = 0, value = 0
     * value_regulator.cursor_position = 2, value = 99
     * -------------------------------------------------------------
     * example incr = 1:
     * value = 100 + pow(10, (2 - value_regulator.cursor_position)) * 1
     * value_regulator.cursor_position = 0, value = 200
     * value_regulator.cursor_position = 2, value = 101
     */

    value_format();

    // digit_lr_move(-1) move left
    if (lr == -1) {
        if (value_regulator.cursor_position > 0)
            value_regulator.cursor_position--;

        if (value_regulator.cursor_position < value_regulator.start_position)
            value_regulator.start_position--;
    }

    // digit_lr_move(1) move right
    if (lr == 1) {
        if (value_regulator.cursor_position < value_regulator.cursor_move_limit) {
            value_regulator.cursor_position++;

            if (((value_regulator.value_string[value_regulator.start_position] == '0') && (value_regulator.data < pow(10, value_regulator.standard_unit_length_max - value_regulator.start_position))) || (value_regulator.cursor_position - value_regulator.start_position) >= value_regulator.display_length_max) {

                // info("value regulator data:%d\n", value_regulator.data);
                // info("start position:%d\n", value_regulator.start_position);
                value_regulator.start_position++;
                // info("start position++");
            }
        }
    }

    // info("value_regulator.start_position:%d", value_regulator.start_position);
    // info("value_regulator.cursor_position:%d\n", value_regulator.cursor_position);
}

void value_ud_flip(int incr)
{
    int value;

    if (get_value_type() == DEV_COMP_MAX) {
        value = _devset.comp.max;
        // info("cursor position:%d", value_regulator.cursor_position);
        value += pow(10, ((value_regulator.value_length - 1) - value_regulator.cursor_position)) * incr;
        // info("value:%d", value);

        if (value > 20000) value = 20000;
        if (value < 0) value = 0;

        if (_devset.comp.min > value) 
            _devset.comp.min = value;

        _devset.comp.max = value;
    }

    if (get_value_type() == DEV_COMP_MIN) {
        value = _devset.comp.min;
        // info("cursor position:%d", value_regulator.cursor_position);
        value += pow(10, ((value_regulator.value_length - 1) - value_regulator.cursor_position)) * incr;
        // info("value:%d", value);

        if (value > 20000) value = 20000;
        if (value < 0) value = 0;

        if (_devset.comp.max < value) 
            _devset.comp.max = value;

        _devset.comp.min = value;
    }

    if (value_regulator.start_position > value_regulator.cursor_position)
        value_regulator.start_position = value_regulator.cursor_position;

    value_regulator.position_change = false;

    renew_value_format_string();
}

void read_display_number_of_digits(int start, int length)
{
    uint8_t raw_part = 0;
    uint8_t display_part = 0;

    if ((start < 0) || (start > 20) || (value_regulator.display_buf[0][start] == '.')) {
        // info("%s", "value_regulator.display_buf[1]");
        return;
    }

    for (raw_part = start; raw_part <= (start + length); raw_part++) {
        value_regulator.display_buf[1][display_part++] = value_regulator.display_buf[0][raw_part];

        if (value_regulator.display_buf[0][raw_part] == '\0')
            break;
    }

    value_regulator.display_buf[1][display_part] = '\0';
    // info("%s", value_regulator.display_buf[1]);
}

void add_decimal_point(uint8_t point_position)
{
    uint8_t i;
    uint8_t temp_char1, temp_char2;

    if ((point_position > 20) || (point_position < 1))
        return;

    if (value_regulator.display_buf[0][point_position] == '\0')
        return;

    temp_char2 = value_regulator.display_buf[0][point_position];
    value_regulator.display_buf[0][point_position] = '.';

    for (i = point_position + 1; i < 6; i++) {
        temp_char1 = value_regulator.display_buf[0][i];
        value_regulator.display_buf[0][i] = temp_char2;
        temp_char2 = temp_char1;
        if (temp_char1 == '\0') {
            value_regulator.display_buf[0][i + 1] = '\0';
            break;
        }
    }
}

void add_negative_sign()
{
    int i;
    int8_t t1,t2;

    t1 = value_regulator.display_buf[1][0];
    value_regulator.display_buf[1][0] = '-';

    for(i = 1; i < 20; i++) {
        t2 = value_regulator.display_buf[1][i];
        value_regulator.display_buf[1][i] = t1;
        t1 = t2;
        if (t1 == '\0')
            break;
    }
    value_regulator.display_buf[1][i + 1] = '\0';
    value_regulator.display_buf[1][20] = '\0';
}

void add_separator(uint8_t character)
{
    int8_t i;
    int8_t point;
    int8_t count;
    int8_t len;
    int8_t *pt;
    int8_t ch[24];
    
    point = count = 0;

    for (i = 0; i < 30; i++) {
        if (value_regulator.display_buf[1][i] == '\0')
            break;

         if (value_regulator.display_buf[1][i] == '.') {
            point = i + 1;
            break;
         }
    }

    if (point == 0) {
        len = strlen(value_regulator.display_buf[1]);
        
        for (i = len - 1; i > 0; i--) {
            count++;
            if ((count % 3) == 0) {
                pt = &value_regulator.display_buf[1][i];
                strcpy(ch, pt);
                *pt = '\0';

                switch (character) {
                    case ',':
                        strcat(value_regulator.display_buf[1], ",");
                        break;

                    case ' ':
                        strcat(value_regulator.display_buf[1], " ");
                        break;
                }
                strcat(value_regulator.display_buf[1], ch);
            }
        }
        return;
    }

    for (i = point; i < 30; i++) {
        if (value_regulator.display_buf[1][i] == '\0')
            break;
        count++;
        if (count % 3 == 0) {
            pt = &value_regulator.display_buf[1][i + 1];
            if (*pt == '\0')
                break;
            strcpy(ch, pt);
            *pt = '\0';
            switch (character) {
                case ',':
                    strcat(value_regulator.display_buf[1], ",");
                    break;
                case ' ':
                    strcat(value_regulator.display_buf[1], " ");
                    break;
            }
            strcat(value_regulator.display_buf[1], ch);
            i++;
        }
    }
}

// const uint8_t * unit[] = {"kV", "V", "mV"};

void read_display_part_string(uint8_t param_type)
{
    uint8_t tf;

    set_value_type(param_type);

    value_format();

    strcpy(value_regulator.display_buf[0], value_regulator.value_string);
    // info("%s", value_regulator.display_buf[0]);
    if (value_regulator.start_position > value_regulator.cursor_position)
        value_regulator.start_position = value_regulator.cursor_position;

    if (param_type == DEV_COMP_MAX) {
        // tf = value_valid_bit_index(value_regulator.display_buf[0]);
        // add_decimal_point(tf + (value_regulator.standard_unit_length_max - tf) % 3 + 1);
        // info("get_digit_pos:%d", value_regulator.start_position);
        read_display_number_of_digits(value_regulator.start_position, value_regulator.display_length_max);
        // add_separator(',');

        // strcat(value_regulator.display_buf[1], unit[(value_regulator.start_position + 1) / 3]);
    }

    if (param_type == DEV_COMP_MIN) {
        // tf = value_valid_bit_index(value_regulator.display_buf[0]);
        // add_decimal_point(tf + (value_regulator.standard_unit_length_max - tf) % 3 + 1);
        // info("get_digit_pos:%d", value_regulator.start_position);
        read_display_number_of_digits(value_regulator.start_position, value_regulator.display_length_max);
        // add_separator(',');

        // strcat(value_regulator.display_buf[1], unit[(value_regulator.start_position + 1) / 3]);
    }

    value_regulator.display_buf[0][29] = '\0';
    value_regulator.display_buf[1][29] = '\0';
}

uint8_t read_cursor_position()
{
    // info("cursor index:%d", value_regulator.cursor_position - value_regulator.start_position);
    return value_regulator.cursor_position - value_regulator.start_position;
}

void reset_cursor_position()
{
    value_regulator.cursor_position = 0;
    value_regulator.start_position = 0;
}
