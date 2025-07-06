
#include "display_menu_content.h"
#include "display.h"

uint8_t display_buf[DISP_BUF_SIZE] = {0};

const uint16_t color_data[] = {
    /**< Dark color*/
    0x0000,/**< Black Color*/
    0xFFFF,/**< White Color*/
    0xF965,/**< Red Color*/
    0x2965,/**< Gray Color*/
    0x4AA9,/**< Dark Green Color*/
    0x07E0,/**< Green*/
    0x5351,/**< Dark Blue*/

    /**< Light color*/
    0xFFFF,/**< White Color*/
    0x0000,/**< Black Color*/
    0xFA49,/**< Red Color*/
    0x94B2,/**< Gray Color*/
    0x4208,/**< Dark Brown Color*/
    0x07E0,/**< Green*/
    0x8DFF,/**< Dark Blue*/
};

typedef struct {
    uint8_t param_cnt;
    uint32_t param_incr;
    uint8_t param_height;
    uint8_t scale_width;
    uint8_t scale_height;
    uint8_t scale_count;
    uint8_t sigh_len;
} bar_chart_t;

extern const sym_desc_t dmm_logo[];

uint8_t * tft_buf()
{
    /**
     * This parameter is received using an array pointer
     * uint8_t (* tft_buf())[]
     */
    return display_buf;
}

void display_pixel(uint32_t y, uint32_t x, uint8_t color, uint8_t * vm)
{
    /**
     * Two colors
     * 
     * uint32_t index = (y * TFT_WIDTH + x) / 8;
     * uint8_t pxindex = (y * TFT_WIDTH + x) % 8;
     *
     * # method 1:
     * vm[index] = (vm[index] & (~(0x01 << (7 - pxindex)))) | (color << (7 - pxindex));
     * 
     * # method 2:
     * 0x7f: [0111, 1111]
     * 0xbf: [1011, 1111]
     * 0xdf: [1101, 1111]
     * 0xef: [1110, 1111]
     * 0xf7: [1111, 0111]
     * 0xfb: [1111, 1011]
     * 0xfd: [1111, 1101]
     * 0xfe: [1111, 1110]
     *
     * switch (pxindex) {
     *     case 0: vm[index] = (vm[index] & 0x7f) | (color << (7 - pxindex)); break;
     *     case 1: vm[index] = (vm[index] & 0xbf) | (color << (7 - pxindex)); break;
     *     case 2: vm[index] = (vm[index] & 0xdf) | (color << (7 - pxindex)); break;
     *     case 3: vm[index] = (vm[index] & 0xef) | (color << (7 - pxindex)); break;
     *     case 4: vm[index] = (vm[index] & 0xf7) | (color << (7 - pxindex)); break;
     *     case 5: vm[index] = (vm[index] & 0xfb) | (color << (7 - pxindex)); break;
     *     case 6: vm[index] = (vm[index] & 0xfd) | (color << (7 - pxindex)); break;
     *     case 7: vm[index] = (vm[index] & 0xfe) | (color << (7 - pxindex)); break;
     * }
     *
     * # method 3:
     * const uint8_t split_byte[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
     * vm[index] = (vm[index] & split_byte[pxindex]) | (color << (7 - pxindex));
     */
    
    vm[y * TFT_WIDTH + x] = color;
}

void display_line(uint32_t y1, uint32_t x1, 
    uint32_t y2, uint32_t x2, uint8_t color, uint8_t * vm)
{
    uint32_t i;
    int xerr = 0, yerr = 0, dx, dy, distance;
    int increment_x, increment_y, row, col;

    dx = x2 - x1;
    dy = y2 - y1;

    row = y1;
    col = x1;

    if (dx > 0) increment_x = 1;
    else if (dx == 0) increment_x = 0;
    else {
        increment_x = -1;
        dx = - dx;
    }

    if (dy > 0) increment_y = 1;
    else if (dy == 0) increment_y = 0;
    else {
        increment_y = - 1;
        dy = -dy;
    }

    if (dx > dy) distance = dx;
    else distance = dy;

    for (i = 0; i <= distance + 1; i++) {
        display_pixel(row, col, color, vm);

        xerr += dx;
        yerr += dy;

        if (xerr > distance) {
            xerr -= distance;
            col += increment_x;
        }

        if (yerr > distance) {
            yerr -= distance;
            row += increment_y;
        }
    }
}

void display_dotted_line(uint32_t y, uint32_t x, uint32_t lenth, uint8_t space, 
    uint8_t direction, uint8_t color, uint8_t * vm)
{
    uint32_t l;

    if (!direction) {
        for (l = 0; l < lenth; l = l + space)
            display_pixel(y, x + l, color, vm);
    } else {
        for (l = 0; l < lenth; l = l + space)
            display_pixel(y + l, x, color, vm);
    }
}

void display_hollow_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t color, uint8_t * vm)
{
    display_line(y, x, y, x + width, color, vm);
    display_line(y, x + width, y + height, x + width, color, vm);
    display_line(y + height, x + width, y + height, x, color, vm);
    display_line(y, x, y + height, x, color, vm);
}

void display_solid_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t color, uint8_t * vm)
{
    uint32_t i, j;

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            display_pixel(y + i, x + j, color, vm);
}

void display_bevel_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint32_t color, uint8_t chamfer, uint8_t * vm)
{
    uint32_t i, j;

    for (i = chamfer; i > 0; i--) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, color, vm);
        }
        y++;
        height--;
    }
    for (i = 0; i < (height - chamfer * 2); i++) {
        for (j = 0; j < width; j++) {
            display_pixel(y, x + j, color, vm);
        }
        y++;
    }
    for (i = 0; i < chamfer + 1; i++) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, color, vm);
        }
        y++;
    }
}

void display_fillet_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint32_t color, uint8_t radius, uint8_t * vm)
{
    uint32_t a, b;
    uint32_t j;

    for (b = radius; b > 0; b--) {
        a = sqrt(radius * radius - b * b);
        for (j = 0; j < (width - (radius - a) * 2); j++) {
            display_pixel(y, x + (radius - a) + j, color, vm);
        }
        y++;
    }
    for (b = 0; b < (height - radius * 2); b++) {
        for (j = 0; j < width; j++) {
            display_pixel(y, x + j, color, vm);
        }
        y++;
    }
    for (b = 0; b < radius; b++) {
        a = sqrt(radius * radius - b * b);
        for (j = 0; j < (width - (radius - a) * 2); j++) {
            display_pixel(y, x + (radius - a) + j, color, vm);
        }
        y++;
    }
}

void display_hollow_triangle(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t color, uint8_t * vm)
{
    display_line(y + height, x, y, x + width / 2, color, vm);
    display_line(y, x + width / 2, y + height, x + width, color, vm);
    display_line(y + height, x + width, y + height, x, color, vm);
}

void _display_circle(uint16_t y, uint16_t x, uint16_t r, uint16_t color, uint8_t * vm)
{
    /**Bresenham 画圆算法*/
    int16_t a = 0, b = r;
    int16_t d = 3 - (r << 1); /**算法决策参数*/

    /**如果圆在屏幕可见区域外，直接退出*/
    if ((x - r < 0) || (x + r > TFT_WIDTH) || 
        (y - r < 0) || (y + r > TFT_HEIGHT)) 
        return;

    /**开始画圆*/
    while (a <= b) {
        display_pixel(y - a, x - b, color, vm);
        display_pixel(y - a, x + b, color, vm);
        display_pixel(y + b, x - a, color, vm);
        display_pixel(y - a, x - b, color, vm);
        display_pixel(y - b, x - a, color, vm);
        display_pixel(y + a, x + b, color, vm);
        display_pixel(y - b, x + a, color, vm);
        display_pixel(y + b, x + a, color, vm);
        display_pixel(y + a, x - b, color, vm);
        a++;

        if (d < 0) d += 4 * a + 6;
        else {
            d += 10 + 4 * (a - b);
            b--;
        }

        display_pixel(y + b, x + a, color, vm);
    }
}

void display_circle(uint16_t y, uint16_t x, uint16_t r, uint16_t color, uint8_t * vm)
{
    /**Bresenham 画圆算法*/
    int16_t a = 0, b = r;
    int16_t d = 3 - (r << 1);

    while (a <= b) {
        int16_t i = a, p = b;
        while (i > 0) {
            display_pixel(y - i, x + b, color, vm);
            display_pixel(y + b, x - i, color, vm);
            i--;
        }
        while (p > 0) {
            display_pixel(y - p, x - a, color, vm);
            display_pixel(y - a, x - p, color, vm);
            display_pixel(y - p, x + a, color, vm);
            display_pixel(y + a, x - p, color, vm);
            display_pixel(y + p, x + a, color, vm);
            display_pixel(y + a, x + p, color, vm);
            p--;
        }
        a++;
        /**Bresenham 画圆算法*/
        if (d < 0) d += 4 * a + 6;
        else {
            d += 10 + 4 * (a - b);
            b--;
        }
    }
    display_pixel(y, x, color, vm); /**圆心坐标*/
}

void display_bookmark(int y, uint32_t x, uint32_t width, uint32_t height, 
    uint32_t color, uint8_t radian, uint8_t * vm)
{
    uint8_t i, j;

    /*Open to the right*/
    for (i = 0; i < radian; i++) {
        for (j = 0; j < (width - i); j++) {
            if ((!(i == 0 && j == 0)) && (j < width - 1))
            display_pixel(y, (x + j), color, vm);
        }
        y++;
    }
    for (i = radian; i > 0; i--) {
        for (j = 0; j < (width - i); j++) {
            if ((!(i == 1 && j == 0)) && (j < width - 2))
            display_pixel(y, (x + j), color, vm);
        }
        y++;
    }
}

void display_sym(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, 
    uint8_t logo_name, uint8_t status, uint8_t * vm)
{
    uint32_t width, height;

    uint32_t total_byte = 0;
    uint32_t column = 0;
    uint32_t tx, ty;

    if (!status) return; /*Do not show this logo*/

    ty = y;
    tx = x;

    width = dmm_logo[logo_name].width;
    height = dmm_logo[logo_name].height;

    /*How many bytes are needed for a character*/
    total_byte = (int)((width + 7) / 8) * height;

    for (int i = 0; i < total_byte; i++) {
        for (int j = 0; j < 8; j++) {
            if (dmm_logo[logo_name].data[i] & (0x80 >> j)) {
                display_pixel(ty, tx, fg, vm);
            } else {
                if (1/*bg != 0*/) display_pixel(ty, tx, bg, vm);
            }
            tx++;
            column++;
            if (column >= width) {
                column = 0;
                ty++;
                tx = x;
                break;
            }
        }
    }
}

void display_battery(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t power, uint8_t status, uint8_t * vm)
{
    uint8_t direction = 0;

    /*power area range: 0 pixel to (width-5) pixel, express power 0%-100%*/
    power = power / (100 / (width - 5));
    if (power >= (width - 5))
        power = width - 5;

    /*Recharge status*/
    if (status == true)
        fg = GREEN;

    if (direction) {
        /*battery back ground*/
        display_solid_rect(y, x, width, height, bg, vm);
        /*battery rim*/
        display_hollow_rect(y, x, width, height, fg, vm);
        display_hollow_rect(y + 1, x + 1, width - 2, height - 2, fg, vm);
        /*display power area*/
        if (power < width / 4) display_solid_rect(y + 3, x + 3, power, height - 5, RED, vm);
        else display_solid_rect(y + 3, x + 3, power, height - 5, fg, vm);
        /*display no power blank area*/
        display_solid_rect(y + 3, x + 3 + power, (width - 5 - power), height - 5, bg, vm);
        /*display battery head*/
        display_solid_rect(y + 2, x + width + 1, 2, height - 3, fg, vm);
    } else {
        /*battery back ground*/
        display_solid_rect(y, x, width, height, bg, vm);
        /*battery rim*/
        display_hollow_rect(y, x, width, height, fg, vm);
        display_hollow_rect(y + 1, x + 1, width - 2, height - 2, fg, vm);
        /*display power area*/
        if (power < width / 4) display_solid_rect(y + 3, x + 3 + (width - 5 - power), power, height - 5, RED, vm);
        else display_solid_rect(y + 3, x + 3 + (width - 5 - power), power, height - 5, fg, vm);
        /*display no power blank area*/
        display_solid_rect(y + 3, x + 3, (width - 5 - power), height - 5, bg, vm);
        /*display battery head*/
        /*display_solid_rect(y + 2, x - 2, 2, height - 3, fg, vm);*/
        display_solid_rect(y + 4, x - 2, 2, height - 7, fg, vm);

        /*battery right chamfer*/
        display_solid_rect(y, x, 1, 1, bg, vm);
        display_solid_rect(y + height, x, 1, 1, bg, vm);
        display_solid_rect(y, x + width, 1, 1, bg, vm);
        display_solid_rect(y + height, x + width, 1, 1, bg, vm);
    }
}

void display_recording_mark(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t status, uint8_t * vm)
{
    if (!status) return;

    display_solid_rect(y, x, width, height, bg, vm);
    display_N2string(y + 2, x + 2, SPECIFY, LAYOUT_R11, 0, 
        "RECORDING", _MENU_LAST, fg, UNSELECT, vm);
}

void display_maxmin_mark(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t status, uint8_t * vm)
{
    if (!status) return;

    display_solid_rect(y, x, width, height, bg, vm);
    display_N2string(y + 2, x + 2, SPECIFY, LAYOUT_R11, 0, 
        "MAX/MIN", _MENU_LAST, fg, UNSELECT, vm);
}

void display_hold_mark(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t status, uint8_t * vm)
{
    if (!status) return;

    display_solid_rect(y, x, width, height, bg, vm);
    display_N2string(y + 2, x + 2, SPECIFY, LAYOUT_R11, 0, 
        "HOLD", _MENU_LAST, fg, UNSELECT, vm);
}

void display_barchart(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, 
    int8_t percentage, int32_t value_max, uint8_t * vm)
{
    bar_chart_t bar_chart = {0};

    uint8_t param_string[8];
    uint8_t offset_y = 0;

    if ((value_max % 6) == 0) {
        bar_chart.param_cnt = 6;
        bar_chart.param_height = 15;
        bar_chart.param_incr = value_max / 6;
        bar_chart.scale_width = 4;
        bar_chart.scale_count = 60;
        bar_chart.sigh_len = 10;
    } else {
        bar_chart.param_cnt = 5;
        bar_chart.param_height = 15;
        bar_chart.param_incr = value_max / 5;
        bar_chart.scale_width = 4;
        bar_chart.scale_count = 50;
        bar_chart.sigh_len = 10;
    }

    if (percentage < 0) display_solid_rect(y + bar_chart.param_height + 11, x, bar_chart.sigh_len - 4, 4, fg, vm);

    for (uint8_t i = 0; i < (bar_chart.param_cnt + 1); i++) {
        sprintf(param_string, "%d", i * bar_chart.param_incr);
        display_N1string(y, x + bar_chart.sigh_len + bar_chart.scale_width * 10 * i - 2, 
            SPECIFY, 0, 0, param_string, _MENU_LAST, fg, UNSELECT, vm);
    }

    for (uint8_t i = 0; i < bar_chart.scale_count + 1; i++) {
        if (i % 5 == 0) {
            bar_chart.scale_height = 8;
            offset_y = 0;
        } else {
            bar_chart.scale_height = 4;
            offset_y = 4;
        }
        display_dotted_line(y + bar_chart.param_height + offset_y, x + bar_chart.sigh_len + bar_chart.scale_width * i, bar_chart.scale_height, 1, 1, fg, vm);
    }
    bar_chart.scale_height = 8;

    for (uint8_t i = 0; i < bar_chart.scale_count + 1; i++)
        display_solid_rect(y + bar_chart.param_height + bar_chart.scale_height + 2, x + bar_chart.sigh_len + bar_chart.scale_width * i - 1, 3, 6, fg, vm);

    /*Red color progress*/
    if (abs(percentage) <= 100) display_solid_rect(y + bar_chart.param_height + bar_chart.scale_height + 2, x + bar_chart.sigh_len - 1, (bar_chart.scale_width * bar_chart.scale_count) * abs(percentage) / 100 + 3, 6, RED, vm);
    else display_sym(y + bar_chart.param_height + bar_chart.scale_height + 1, x + bar_chart.sigh_len + (bar_chart.scale_width * bar_chart.scale_count) + 4, WHITE, BLACK, RULER_OVERFLOW, 1, vm);
}

void display_dock(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint32_t rows, uint8_t row_gap, uint8_t select_num, uint8_t * vm)
{
    uint32_t color;
    uint8_t items = rows;

    for (; items > 0; items--) {
        if (items == (rows - select_num)) color = fg;
        else color = bg;

        display_bevel_rect(y, x, width, height, color, 1, vm);
        y = y + height + row_gap;
    }

    /**
     * for (; items > 0; items--) {
     *     if (items == (rows - select_num))
     *         display_bevel_rect(y + 1, x + 5, width - 10, height - 2, fg, 1, vm);
     *     else
     *         display_bevel_rect(y, x, width, height, bg, 1, vm);
     *     y = y + height + row_gap;
     * }
     */
}

void _letter_refer(_letter_t * _lettr_p, const uint8_t * str_p, uint8_t _offs)
{
    if ((!_lettr_p) || (!str_p)) return;
    uint8_t str_len = strlen(str_p) + 1;

    if (_lettr_p->_len > str_len) _lettr_p->_len = _offs;
    if (_lettr_p->_len < _offs) _lettr_p->_len = _offs;

    memset(_lettr_p->letter, '\0', 32);
    snprintf(_lettr_p->letter, _lettr_p->_len, "%s", str_p);
    _lettr_p->_len++;
}

const uint8_t * _letter_get_str(_letter_t * _lettr_p)
{
    if (_lettr_p) return _lettr_p->letter;
    return " ";
}

dev_alerts_t message_tips[5] = {
    {
        .message_width = 50,
        .message_height = 30,
        .active = true,
        .reside_time = 300,
        .content_num = TIPS_BATTERY_LOW_20,
    },

    {
        .message_width = 50,
        .message_height = 30,
        .active = true,
        .reside_time = 0,
        .content_num = TIPS_BATTERY_LOW_10,
    },

    {
        .message_width = 50,
        .message_height = 30,
        .active = true,
        .reside_time = 0,
        .content_num = TIPS_BATTERY_LOW_05,
    },

    {
        .message_width = 50,
        .message_height = 30,
        .active = true,
        .reside_time = 0,
        .content_num = 3,
    },
};

void active_tips(dev_alerts_t * tips, uint32_t reside_time)
{
    tips->reside_time = reside_time;
    tips->active = true;
}

void inactive_tips(dev_alerts_t * tips)
{
    tips->reside_time = 0;
    tips->active = false;
}

void inactive_all_tips(dev_alerts_t tips[])
{
    uint8_t n = sizeof(message_tips) / sizeof(dev_alerts_t);

    for (uint8_t i = 0; i < n; i++) {
        tips[i].reside_time = 0;
        tips[i].active = false;
    }
}

void tips_timing(dev_alerts_t * tips)
{
    if (tips->reside_time > 0)
        tips->reside_time--;
}

void tips_all_timing(dev_alerts_t tips[])
{
    uint8_t n = sizeof(message_tips) / sizeof(dev_alerts_t);

    for (uint8_t i = 0; i < n; i++) {
        if (tips[i].reside_time > 0)
            tips[i].reside_time--;
    }
}

void display_tips(uint32_t y, uint32_t x, uint32_t tft_width, 
    uint8_t fg, uint8_t bg, uint8_t font_size, 
    dev_alerts_t * tips, uint8_t * vm)
{
    uint8_t str_length = 0;
    uint8_t str_height = 0;

    uint8_t tips_buf[4][32];
    uint8_t line    = 0;
    uint8_t postion = 0;
    uint8_t len     = 0;

    if ((tips->active == false) || (tips->reside_time <= 0)) return;

    for (uint8_t set = 0; set < 4; set++)
        memset(tips_buf[set], '\0', 32);

    for (uint8_t i = 0; i < strlen(tips_content[tips->content_num]); i++) {
        if (tips_content[tips->content_num][i] != '\n') {
            tips_buf[line][postion] = tips_content[tips->content_num][i];
            postion++;
        } else {
            line++;
            postion = 0;
        }
    }
    line++;

    for (uint8_t l = 0; l < line; l++) {
        len = string_valid_width(font_size, (uint8_t *)tips_buf[l]);
        if (len > str_length)
            str_length = len;
    }
    /*str_length = string_valid_width(font_size, (uint8_t *)tips_content[tips->content_num]);*/
    str_height = string_valid_height(font_size, (uint8_t *)tips_content[tips->content_num]);

    x = (int)((tft_width - str_length) / 2);

    display_bevel_rect(y, x, str_length + 4, str_height * line + 4 * line, bg, 1, vm);

    for (uint8_t l = 0; l < line; l++) {
        display_string_align(y + 2, x + 2, SPECIFY, 0, 0, fg, font_size, (uint8_t *)/*tips_content[tips->content_num]*/tips_buf[l], UNSELECT, vm);
        if (l != (line - 1))
            display_dotted_line(y + str_height + 4, x + 2, str_length, 2, 0, WHITE, vm);
        y = y + str_height + 4;
    }
}

const uint8_t bluetooth[] = {
    0x00,0x00,0x01,0xC0,0x01,0xE0,0x31,0xB0,0x19,0x98,0x0D,0x98,0x07,0xB0,0x03,0xE0,
    0x03,0xE0,0x07,0xB0,0x0D,0x98,0x19,0x98,0x31,0xB0,0x01,0xE0,0x01,0xC0,0x00,0x00,
};

const uint8_t poweroff_timer[] = {
    0x00,0x00,0x7D,0xBE,0x7D,0xBE,0x61,0x86,0x61,0x86,0x61,0x86,0x61,0x86,0x60,0x00,
    0x60,0xFE,0x60,0x92,0x60,0x92,0x60,0x9E,0x60,0x82,0x7E,0x82,0x7E,0xFE,0x00,0x00,
};

const uint8_t lighting[] = {
    0x00,0x00,0x01,0xF0,0x03,0xE0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x3F,0xFE,0x7F,0xFE,
    0x7F,0xFC,0x00,0xF8,0x01,0xF0,0x03,0xE0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x00,0x00,
};

const uint8_t lo[] = {
    0xFF,0xFC,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x03,0x00,0x00,0x60,0x03,0x00,0x00,
    0x60,0x01,0x80,0x00,0x60,0x79,0x80,0x00,0x60,0xFC,0xC0,0x00,0x61,0xCE,0xC0,0x00,
    0x61,0x86,0x60,0x00,0x61,0x86,0x60,0x00,0x61,0x86,0x30,0x00,0x61,0xCE,0x30,0x00,
    0x7E,0xFC,0x18,0x00,0x7E,0x78,0x18,0x00,0x00,0x00,0x00,0x00,
};

const uint8_t loz[] = {
    0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,
    0x60,0x00,0x00,0x00,0x60,0x78,0xFC,0x00,0x60,0xFC,0xFC,0x00,0x61,0xCE,0x0C,0x00,
    0x61,0x86,0x18,0x00,0x61,0x86,0x30,0x00,0x61,0x86,0x60,0x00,0x61,0xCE,0xC0,0x00,
    0x7E,0xFC,0xFC,0x00,0x7E,0x78,0xFC,0x00,0x00,0x00,0x00,0x00,
};

const uint8_t ruler_overflow[] = {
    0x80,0xc0,0xe0,0xf0,0xf0,0xe0,0xc0,0x80,
};

const uint8_t ac_desc[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x7f,0x06,0xe3,0x8e,0xc1,0xfc,0x00,0xf8,
};

const uint8_t dc_desc[] = {
    0xff,0xfe,0xff,0xfe,0x00,0x00,0x00,0x00,0xdb,0x6e,0xdb,0x6e,0x00,0x00,0x00,0x00,
};

const uint8_t ac_dc_desc[] = {
    0xff,0xfe,0xff,0xfe,0x00,0x00,0x3e,0x00,0x7f,0x06,0xe3,0x8e,0xc1,0xfc,0x00,0xf8,
};

const uint8_t trumpet[] = {
    0x00,0x00,0x00,0x00,0x00,0xC8,0x01,0xC4,0x03,0xD2,0x3F,0xCA,0x7F,0xCA,0x7F,0xCA,
    0x7F,0xCA,0x7F,0xCA,0x3F,0xCA,0x03,0xD2,0x01,0xC4,0x00,0xC8,0x00,0x00,0x00,0x00,
};

const sym_desc_t dmm_logo[] = {
    {
        .width = 16,
        .height = 16,
        .data = bluetooth,
    },

    {
        .width = 16,
        .height = 16,
        .data = poweroff_timer,
    },

    {
        .width = 16,
        .height = 16,
        .data = lighting,
    },

    {
        .width = 32,
        .height = 15,
        .data = lo,
    },

    {
        .width = 32,
        .height = 15,
        .data = loz,
    },

    {
        .width = 8,
        .height = 8,
        .data = ruler_overflow,
    },

    {
        .width = 16,
        .height = 8,
        .data = ac_desc,
    },

    {
        .width = 16,
        .height = 8,
        .data = dc_desc,
    },

    {
        .width = 16,
        .height = 8,
        .data = ac_dc_desc,
    },

    {
        .width = 16,
        .height = 16,
        .data = trumpet,
    },
};

sym_desc_t read_logo_data(uint8_t logo_name)
{
    return dmm_logo[logo_name];
}
