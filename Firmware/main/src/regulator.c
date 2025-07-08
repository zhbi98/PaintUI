/**
 * @file regulator.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <math.h>
#include "log.h"
#include "regulator.h"
#include "setup.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

_regu_t regu = {0};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void regu_val_set_type(uint8_t _type)
{
    regu.val_type = _type;
}

uint8_t regut_val_ge_type()
{
    return regu.val_type;
}

void regu_get_changed_val()
{
    static double temp_data;

    regu.data = 0;
    regu.bechg_val = (void *)&temp_data;

    if (regut_val_ge_type() == DEV_COMP_MAX)
        *((int32_t *)regu.bechg_val) = \
            abs(_devset.comp.max);

    if (regut_val_ge_type() == DEV_COMP_MIN)
        *((int32_t *)regu.bechg_val) = \
            abs(_devset.comp.min);

    if (regu.data == 0)
        regu.data = *((int32_t *)regu.bechg_val);
}

void regu_fmtval_refer()
{
    regu.disp_len_max = DISPLAY_LENGTH_MAX;

    regu_get_changed_val();

    if (regut_val_ge_type() == DEV_COMP_MAX) {
        sprintf(regu.valstr, "%06d", *((int32_t *)regu.bechg_val));
        regu.disp_len_max = 6;
        regu.std_unit_len_max = 6;
        regu.cur_movlim = regu.std_unit_len_max - 1;
        regu.vallen = strlen(regu.valstr);
    }

    if (regut_val_ge_type() == DEV_COMP_MIN) {
        sprintf(regu.valstr, "%06d", *((int32_t *)regu.bechg_val));
        regu.disp_len_max = 6;
        regu.std_unit_len_max = 6;
        regu.cur_movlim = regu.std_unit_len_max - 1;
        regu.vallen = strlen(regu.valstr);
    }

    if (regu.vallen > 16 || regu.disp_len_max > DISPLAY_LENGTH_MAX) {
        regu.vallen = 0;
        regu.disp_len_max = MINIWIN_MAXL;
    }
}

uint8_t regu_valid_bit_get_idx(uint8_t * string)
{
    uint8_t length;
    uint8_t valid_bit_index;

    length = strlen(string);
    /*info("parameter bit length:%d", length);*/

    if ((length <= 0) || (length > 6))
        return 0;

    for (uint8_t i = 0; i <= length; i++) {
        if (string[i] != '0') {
            valid_bit_index = i;
            /*info("first valid bit index:%d", valid_bit_index);*/
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

uint8_t regu_first_bit_refer(_regu_t * regu, uint8_t firstbit_idx)
{
    uint8_t length;
    uint8_t curlen;

    length = regu->vallen;
    curlen = length - regu->start_pos;

    if (curlen > regu->disp_len_max)
        curlen = regu->disp_len_max;

    if (curlen == regu->disp_len_max) {
        if ((regu->cur_pos - firstbit_idx) < regu->disp_len_max)
            return true;
    } else
        return true;

    return false;
}

void regu_fmt_str_refer()
{
    uint8_t valid_bit_index;
    uint8_t reflesh;

    regu_fmtval_refer();

    valid_bit_index = regu_valid_bit_get_idx(regu.valstr);
    reflesh = regu_first_bit_refer(&regu, valid_bit_index);

    if (reflesh || (regu.pos_change != false))
        regu.start_pos = valid_bit_index;

    if (regu.pos_change != false)
        regu.cur_pos = regu.start_pos;

    regu.pos_change = true;
}

void regu_LR_move(int32_t lr)
{
    /**
     * value = pow(10, (6 - regu.cur_pos)) * incr
     * -------------------------------------------------------------
     * example incr = -1:
     * value = 100 + pow(10, (2 - regu.cur_pos)) * -1
     * regu.cur_pos = 0, value = 0
     * regu.cur_pos = 2, value = 99
     * -------------------------------------------------------------
     * example incr = 1:
     * value = 100 + pow(10, (2 - regu.cur_pos)) * 1
     * regu.cur_pos = 0, value = 200
     * regu.cur_pos = 2, value = 101
     */

    regu_fmtval_refer();

    // regu_LR_move(-1) move left
    if (lr == -1) {
        if (regu.cur_pos > 0)
            regu.cur_pos--;

        if (regu.cur_pos < regu.start_pos)
            regu.start_pos--;
    }

    // regu_LR_move(1) move right
    if (lr == 1) {
        if (regu.cur_pos < regu.cur_movlim) {
            regu.cur_pos++;

            if (((regu.valstr[regu.start_pos] == '0') && 
                (regu.data < pow(10, regu.std_unit_len_max - regu.start_pos))) || 
                (regu.cur_pos - regu.start_pos) >= regu.disp_len_max) {

                /*info("value regulator data:%d\n", regu.data);*/
                /*info("start position:%d\n", regu.start_pos);*/
                regu.start_pos++;
                /*info("start position++");*/
            }
        }
    }

    /*info("regu.start_pos:%d", regu.start_pos);*/
    /*info("regu.cur_pos:%d\n", regu.cur_pos);*/
}

void regu_UD_move(int32_t incr)
{
    int32_t value;

    if (regut_val_ge_type() == DEV_COMP_MAX) {
        value = _devset.comp.max;
        /*info("cursor position:%d", regu.cur_pos);*/
        value += pow(10, ((regu.vallen - 1) - regu.cur_pos)) * incr;
        /*info("value:%d", value);*/

        if (value > 20000) value = 20000;
        if (value < 0) value = 0;

        if (_devset.comp.min > value) 
            _devset.comp.min = value;

        _devset.comp.max = value;
    }

    if (regut_val_ge_type() == DEV_COMP_MIN) {
        value = _devset.comp.min;
        /*info("cursor position:%d", regu.cur_pos);*/
        value += pow(10, ((regu.vallen - 1) - regu.cur_pos)) * incr;
        /*info("value:%d", value);*/

        if (value > 20000) value = 20000;
        if (value < 0) value = 0;

        if (_devset.comp.max < value) 
            _devset.comp.max = value;

        _devset.comp.min = value;
    }

    if (regu.start_pos > regu.cur_pos)
        regu.start_pos = regu.cur_pos;

    regu.pos_change = false;

    regu_fmt_str_refer();
}

void regu_disp_digits_req(int32_t start, int32_t length)
{
    uint8_t raw_part = 0;
    uint8_t display_part = 0;

    if ((start < 0) || (start > 20) || (regu.disp_buf[0][start] == '.')) {
        /*info("%s", "regu.disp_buf[1]");*/
        return;
    }

    for (raw_part = start; raw_part <= (start + length); raw_part++) {
        regu.disp_buf[1][display_part++] = regu.disp_buf[0][raw_part];

        if (regu.disp_buf[0][raw_part] == '\0')
            break;
    }

    regu.disp_buf[1][display_part] = '\0';
    /*info("%s", regu.disp_buf[1]);*/
}

void regu_dec_point_add(uint8_t point_position)
{
    uint8_t i;
    uint8_t temp_char1, temp_char2;

    if ((point_position > 20) || (point_position < 1))
        return;

    if (regu.disp_buf[0][point_position] == '\0')
        return;

    temp_char2 = regu.disp_buf[0][point_position];
    regu.disp_buf[0][point_position] = '.';

    for (i = point_position + 1; i < 6; i++) {
        temp_char1 = regu.disp_buf[0][i];
        regu.disp_buf[0][i] = temp_char2;
        temp_char2 = temp_char1;
        if (temp_char1 == '\0') {
            regu.disp_buf[0][i + 1] = '\0';
            break;
        }
    }
}

void regu_Nsign_add()
{
    int32_t i;
    int8_t t1,t2;

    t1 = regu.disp_buf[1][0];
    regu.disp_buf[1][0] = '-';

    for(i = 1; i < 20; i++) {
        t2 = regu.disp_buf[1][i];
        regu.disp_buf[1][i] = t1;
        t1 = t2;
        if (t1 == '\0')
            break;
    }
    regu.disp_buf[1][i + 1] = '\0';
    regu.disp_buf[1][20] = '\0';
}

void regu_separator_add(uint8_t character)
{
    int8_t i;
    int8_t point;
    int8_t count;
    int8_t len;
    int8_t *pt;
    int8_t ch[24];
    
    point = count = 0;

    for (i = 0; i < 30; i++) {
        if (regu.disp_buf[1][i] == '\0')
            break;

         if (regu.disp_buf[1][i] == '.') {
            point = i + 1;
            break;
         }
    }

    if (point == 0) {
        len = strlen(regu.disp_buf[1]);
        
        for (i = len - 1; i > 0; i--) {
            count++;
            if ((count % 3) == 0) {
                pt = &regu.disp_buf[1][i];
                strcpy(ch, pt);
                *pt = '\0';

                switch (character) {
                case ',':
                    strcat(regu.disp_buf[1], ",");
                    break;

                case ' ':
                    strcat(regu.disp_buf[1], " ");
                    break;
                }
                strcat(regu.disp_buf[1], ch);
            }
        }
        return;
    }

    for (i = point; i < 30; i++) {
        if (regu.disp_buf[1][i] == '\0')
            break;
        count++;
        if (count % 3 == 0) {
            pt = &regu.disp_buf[1][i + 1];
            if (*pt == '\0')
                break;
            strcpy(ch, pt);
            *pt = '\0';
            switch (character) {
            case ',':
                strcat(regu.disp_buf[1], ",");
                break;
            case ' ':
                strcat(regu.disp_buf[1], " ");
                break;
            }
            strcat(regu.disp_buf[1], ch);
            i++;
        }
    }
}

// const uint8_t * unit[] = {"kV", "V", "mV"};

void regu_disp_get_str(uint8_t _type)
{
    uint8_t tf;

    regu_val_set_type(_type);

    regu_fmtval_refer();

    strcpy(regu.disp_buf[0], regu.valstr);
    /*info("%s", regu.disp_buf[0]);*/
    if (regu.start_pos > regu.cur_pos)
        regu.start_pos = regu.cur_pos;

    if (_type == DEV_COMP_MAX) {
        // tf = regu_valid_bit_get_idx(regu.disp_buf[0]);
        // regu_dec_point_add(tf + (regu.std_unit_len_max - tf) % 3 + 1);
        /*info("get_digit_pos:%d", regu.start_pos);*/
        regu_disp_digits_req(regu.start_pos, regu.disp_len_max);
        // regu_separator_add(',');

        // strcat(regu.disp_buf[1], unit[(regu.start_pos + 1) / 3]);
    }

    if (_type == DEV_COMP_MIN) {
        // tf = regu_valid_bit_get_idx(regu.disp_buf[0]);
        // regu_dec_point_add(tf + (regu.std_unit_len_max - tf) % 3 + 1);
        /*info("get_digit_pos:%d", regu.start_pos);*/
        regu_disp_digits_req(regu.start_pos, regu.disp_len_max);
        // regu_separator_add(',');

        // strcat(regu.disp_buf[1], unit[(regu.start_pos + 1) / 3]);
    }

    regu.disp_buf[0][29] = '\0';
    regu.disp_buf[1][29] = '\0';
}

uint8_t regu_cursor_get_pos()
{
    /*info("cursor index:%d", regu.cur_pos - regu.start_pos);*/
    return regu.cur_pos - regu.start_pos;
}

void regu_cursor_pos_reset()
{
    regu.cur_pos = 0;
    regu.start_pos = 0;
}
