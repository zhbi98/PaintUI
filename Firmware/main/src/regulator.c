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
 *  STATIC PROTOTYPES
 **********************/

static void regu_get_chg_val();
static void regu_fmtval_refer();
static uint8_t regu_valid_bit_get_idx(uint8_t * str_p);
static uint8_t regu_first_bit_refer(_regu_t * regu, uint8_t firstbit_idx);
static void regu_disp_get_digits(int32_t start, int32_t len);
static void regu_fmtstr_refer();

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_val_set_type(uint8_t _type)
{
    regu.val_type = _type;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
uint8_t regut_val_ge_type()
{
    return regu.val_type;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
static void regu_get_chg_val()
{
    uint16_t _type = regut_val_ge_type();
    void * val = regu.bechg_val;
    static double _val = 0.0f;

    regu.bechg_val = (void *)&_val;
    regu.data = 0;

    if (_type == DEV_COMP_MAX)
        *((int32_t *)val) = abs(
            _devset.comp.max);

    if (_type == DEV_COMP_MIN)
        *((int32_t *)val) = abs(
            _devset.comp.min);

    if (!regu.data) regu.data = \
        *((int32_t *)val);
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
static void regu_fmtval_refer()
{
    uint16_t _type = regut_val_ge_type();
    regu.displen = DISP_LEN_MAX;

    regu_get_chg_val();

    if (_type == DEV_COMP_MAX) {
        sprintf(regu.valstr, "%06d", 
            *((int32_t *)regu.bechg_val));

        regu.std_unit_len = 6;
        regu.cur_movlim = regu.std_unit_len - 1;
        regu.vallen = strlen(regu.valstr);
        regu.displen = 6;
    }

    if (_type == DEV_COMP_MIN) {
        sprintf(regu.valstr, "%06d", 
            *((int32_t *)regu.bechg_val));

        regu.std_unit_len = 6;
        regu.cur_movlim = regu.std_unit_len - 1;
        regu.vallen = strlen(regu.valstr);
        regu.displen = 6;
    }

    if (regu.displen > DISP_LEN_MAX ||
        regu.vallen > 16
    ) {
        regu.displen = MINIWIN_MAXL;
        regu.vallen = 0;
    }
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
static uint8_t regu_valid_bit_get_idx(uint8_t * str_p)
{
    uint8_t _valid = 0;
    uint8_t len = 0;

    len = strlen(str_p);
    /*info("Bit len:%d", len);*/
    if ((len <= 0) || (len > 6)) return 0;

    for (uint8_t i = 0; i <= len; i++) {
        if (str_p[i] != '0') {
            _valid = i;
            /*info("_valid:%d", _valid);*/
            break;
        }
    }

    if (_valid >= len) _valid = len - 1;
    if (_valid > 6) _valid = 6;
    if (str_p[_valid] == '.') _valid--;

    return _valid;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
static uint8_t regu_first_bit_refer(_regu_t * regu, 
    uint8_t firstbit_idx)
{
    uint8_t curlen = 0;
    uint8_t len = 0;

    len = regu->vallen;
    curlen = len - regu->start_pos;

    if (curlen > regu->displen)
        curlen = regu->displen;

    if (curlen == regu->displen) {
        if ((regu->cur_pos - firstbit_idx) < regu->displen)
            return true;
    } else return true;

    return false;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
static void regu_fmtstr_refer()
{
    uint8_t _valid = 0;
    uint8_t refer = 0;

    regu_fmtval_refer();

    _valid = regu_valid_bit_get_idx(regu.valstr);
    refer = regu_first_bit_refer(&regu, _valid);

    if ((refer) || (regu.pos_change != false))
        regu.start_pos = _valid;

    if (regu.pos_change != false)
        regu.cur_pos = regu.start_pos;

    regu.pos_change = true;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_LR_move(int32_t val)
{
    regu_fmtval_refer();

    if (val == -1) { /**Left*/
        if (regu.cur_pos > 0) regu.cur_pos--;
        if (regu.cur_pos < regu.start_pos)
            regu.start_pos--;
    }

    if (val == 1) { /*Right*/
        if (regu.cur_pos < regu.cur_movlim) {
            regu.cur_pos++;
            if (((regu.valstr[regu.start_pos] == '0') && 
                (regu.data < pow(10, regu.std_unit_len - regu.start_pos))) || 
                (regu.cur_pos - regu.start_pos) >= regu.displen
            ) {
                regu.start_pos++;
            }
        }
    }
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_UD_move(int32_t val)
{
    double _powval = 0.0f;
    int32_t value = 0;

    if (regut_val_ge_type() == DEV_COMP_MAX) {
        value = _devset.comp.max;
        _powval = pow(10, (regu.vallen - 1) - regu.cur_pos);
        value += _powval * val;
        /*info("cursor position:%d", regu.cur_pos);*/
        /*info("value:%d", value);*/

        if (value > 20000) value = 20000;
        if (value < 0) value = 0;
        if (_devset.comp.min > value) 
            _devset.comp.min = value;
        _devset.comp.max = value;
    }

    if (regut_val_ge_type() == DEV_COMP_MIN) {
        value = _devset.comp.min;
        _powval = pow(10, (regu.vallen - 1) - regu.cur_pos);
        value += _powval * val;
        /*info("cursor position:%d", regu.cur_pos);*/
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

    regu_fmtstr_refer();
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
static void regu_disp_get_digits(int32_t start, int32_t len)
{
    uint8_t disp_part = 0;
    uint8_t raw_part = 0;

    if ((start < 0) || (start > 20) || 
        (regu.refer[0][start] == '.')
    ) {
        /*info("%s", "regu.refer[1]");*/
        return;
    }

    for (raw_part = start; raw_part <= (start + len); raw_part++) {
        regu.refer[1][disp_part++] = regu.refer[0][raw_part];
        if (regu.refer[0][raw_part] == '\0') break;
    }

    regu.refer[1][disp_part] = '\0';
    /*info("%s", regu.refer[1]);*/
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_dec_point_add(uint8_t _pos)
{
    uint8_t t_char1 = '\0';
    uint8_t t_char2 = '\0';
    uint8_t pos = 0;

    if ((_pos > 20) || (_pos < 1)) return;
    if (regu.refer[0][_pos] == '\0') return;

    t_char2 = regu.refer[0][_pos];
    regu.refer[0][_pos] = '.';

    for (pos = _pos + 1; pos < 6; pos++) {
        t_char1 = regu.refer[0][pos];
        regu.refer[0][pos] = t_char2;
        t_char2 = t_char1;
        if (t_char1 == '\0') {
            regu.refer[0][pos + 1] = '\0';
            break;
        }
    }
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_Nsign_add()
{
    int8_t _char = '\0';
    int8_t char_ = '\0';
    int32_t _len = 0;

    _char = regu.refer[1][0];
    regu.refer[1][0] = '-';

    for(_len = 1; _len < 20; _len++) {
        char_ = regu.refer[1][_len];
        regu.refer[1][_len] = _char;
        _char = char_;
        if (_char == '\0') break;
    }
    regu.refer[1][_len + 1] = '\0';
    regu.refer[1][20] = '\0';
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_separator_add(uint8_t _char)
{
    int8_t * str_p = NULL;
    int8_t str[24] = {0};
    int8_t _idx = 0;
    int8_t point = 0;
    int8_t count = 0;
    int8_t len = 0;

    for (_idx = 0; _idx < 30; _idx++) {
        if (regu.refer[1][_idx] == '\0') break;
        if (regu.refer[1][_idx] == '.') {
            point = _idx + 1;
            break;
        }
    }

    if (point == 0) {
        len = strlen(regu.refer[1]);
        
        for (_idx = len - 1; _idx > 0; _idx--) {
            count++;
            if ((count % 3) == 0) {
                str_p = &regu.refer[1][_idx];
                strcpy(str, str_p);
                *str_p = '\0';

                if (_char >= ' ' && _char <= '~')
                    strcat(regu.refer[1], (uint8_t *)&_char);
                strcat(regu.refer[1], str);
            }
        }
        return;
    }

    for (_idx = point; _idx < 30; _idx++) {
        if (regu.refer[1][_idx] == '\0') break;
        count++;
        if (count % 3 == 0) {
            str_p = &regu.refer[1][_idx + 1];
            if (*str_p == '\0') break;
            strcpy(str, str_p);
            *str_p = '\0';
            if (_char >= ' ' && _char <= '~')
                strcat(regu.refer[1], (uint8_t *)&_char);
            strcat(regu.refer[1], str);
            _idx++;
        }
    }
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_disp_get_str(uint8_t _type)
{
    uint8_t _idx = 0;

    regu_val_set_type(_type);
    regu_fmtval_refer();

    strcpy(regu.refer[0], regu.valstr);
    /*info("%s", regu.refer[0]);*/
    if (regu.start_pos > regu.cur_pos)
        regu.start_pos = regu.cur_pos;

    if (_type == DEV_COMP_MAX) {
        /*_idx = regu_valid_bit_get_idx(regu.refer[0]);*/
        /*regu_dec_point_add(_idx + 
        (regu.std_unit_len - _idx) % 3 + 1);*/
        regu_disp_get_digits(regu.start_pos, 
            regu.displen);
        /*regu_separator_add(',');*/
        /*strcat(regu.refer[1], 
        unit[(regu.start_pos + 1) / 3]);*/
    }

    if (_type == DEV_COMP_MIN) {
        /*_idx = regu_valid_bit_get_idx(regu.refer[0]);*/
        /*regu_dec_point_add(_idx + 
        (regu.std_unit_len - _idx) % 3 + 1);*/
        regu_disp_get_digits(regu.start_pos, 
            regu.displen);
        /*regu_separator_add(',');*/
        /*strcat(regu.refer[1], 
        unit[(regu.start_pos + 1) / 3]);*/
    }

    /*info("_pos:%d", regu.start_pos);*/

    regu.refer[0][29] = '\0';
    regu.refer[1][29] = '\0';
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
uint8_t regu_cursor_get_pos()
{
    int16_t _pos = regu.cur_pos - regu.start_pos;
    return _pos;
}

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
void regu_cursor_pos_reset()
{
    regu.cur_pos = 0;
    regu.start_pos = 0;
}
