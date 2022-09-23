
#include "display.h"

unsigned char display_buf[DISPLAY_BUF_SIZE];

const unsigned int color_data[] = {
    // Dark color
    /* BLACK_COLOR      = */ 0x0000,
    /* WHITE_COLOR      = */ 0xffff, // 0xb5d6
    /* RED_COLOR        = */ 0xf965, // 0xf800,
    /* GRAY_COLOR       = */ 0x2965,
    /* DARK_GREEN_COLOR = */ 0x4aa9,
    /* GREEN            = */ 0x07e0,
    /* DARK_BLUE        = */ 0x5351,

    // Light color  
    /* WHITE_COLOR      = */ 0xffff,
    /* BLACK_COLOR      = */ 0x0000, // 0xffff
    /* RED_COLOR        = */ 0xfa49, // 0xf9e7, 0xfa28
    /* GRAY_COLOR       = */ 0x94b2,
    /* DARK_BROWN_COLOR = */ 0x4208,
    /* GREEN            = */ 0x07e0,
    /* DARK_BLUE        = */ 0x8dff,
};

unsigned char * tft_buf()
{
    /**
     * This parameter is received using an array pointer
     * unsigned char (* tft_buf())[]
     */
    return display_buf;
}

void display_pixel(unsigned int y, unsigned int x, unsigned char color, unsigned char * vm)
{
    /**
     * Two colors
     * 
     * unsigned int index = (y * TFT_WIDTH + x) / 8;
     * unsigned char pxindex = (y * TFT_WIDTH + x) % 8;
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
     * const unsigned char split_byte[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
     * vm[index] = (vm[index] & split_byte[pxindex]) | (color << (7 - pxindex));
     */
    
    vm[y * TFT_WIDTH + x] = color;
}

void display_line(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2, unsigned char color, unsigned char * vm)
{
    unsigned int i;
    int xerr = 0, yerr = 0, dx, dy, distance;
    int increment_x, increment_y, row, col;

    dx = x2 - x1;
    dy = y2 - y1;

    row = y1;
    col = x1;

    if (dx > 0)
        increment_x = 1;
    else if (dx == 0)
        increment_x = 0;
    else {
        increment_x = -1;
        dx = - dx;
    }

    if (dy > 0)
        increment_y = 1;
    else if (dy == 0)
        increment_y = 0;
    else {
        increment_y = - 1;
        dy = -dy;
    }

    if (dx > dy)
        distance = dx;
    else
        distance = dy;

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

void display_dotted_line(unsigned int y, unsigned int x, unsigned int lenth, unsigned char space, unsigned char direction, unsigned char color, unsigned char * vm)
{
    unsigned int l;

    if (!direction) {
        for (l = 0; l < lenth; l = l + space)
            display_pixel(y, x + l, color, vm);
    } else {
        for (l = 0; l < lenth; l = l + space)
            display_pixel(y + l, x, color, vm);
    }
}

void display_hollow_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char color, unsigned char * vm)
{
    display_line(y, x, y, x + width, color, vm);
    display_line(y, x + width, y + height, x + width, color, vm);
    display_line(y + height, x + width, y + height, x, color, vm);
    display_line(y, x, y + height, x, color, vm);
}

void display_solid_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char color, unsigned char * vm)
{
    unsigned int i, j;

    for (i = 0; i < height; i++)
        for (j = 0; j < width; j++)
            display_pixel(y + i, x + j, color, vm);
}

void display_bevel_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char chamfer, unsigned char * vm)
{
    unsigned int i, j;

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

void display_fillet_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char radius, unsigned char * vm)
{
    unsigned int a, b;
    unsigned int j;

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

void display_hollow_triangle(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char color, unsigned char * vm)
{
    display_line(y + height, x, y, x + width / 2, color, vm);
    display_line(y, x + width / 2, y + height, x + width, color, vm);
    display_line(y + height, x + width, y + height, x, color, vm);
}

void display_bookmark(int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char radian, unsigned char * vm)
{
    unsigned char i, j;

    // Open to the left
    // display_bookmark(0, 0, 20, 16, WHITE, 8, vm);
    // for (i = 0; i < radian; i++) {
    //     for (j = 0; j < (width - i); j++) {
    //         display_pixel(y, (x + i + j), color, vm);
    //     }
    //     y++;
    // }
    // for (i = radian; i > 0; i--) {
    //     for (j = 0; j < (width - i); j++) {
    //         display_pixel(y, (x + i + j), color, vm);
    //     }
    //     y++;
    // }

    // Open to the right
    // display_bookmark(0, 0, 20, 16, WHITE, 8, vm);
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

void display_status_logo(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, unsigned char logo_name, unsigned char status, unsigned char * vm)
{
    unsigned int width, height;

    unsigned int total_byte = 0;
    unsigned int column = 0;
    unsigned int tx, ty;

    if (!status)
        return; // Do not show this logo

    ty = y;
    tx = x;

    width = dmm_logo[logo_name].width;
    height = dmm_logo[logo_name].height;

    // How many bytes are needed for a character
    total_byte = (int)((width + 7) / 8) * height;

    for (int i = 0; i < total_byte; i++) {
        for (int j = 0; j < 8; j++) {
            if (dmm_logo[logo_name].data[i] & (0x80 >> j)) {
                display_pixel(ty, tx, fg, vm);
            } else {
                // if (bg != 0)
                display_pixel(ty, tx, bg, vm);
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

void display_battery(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char power, unsigned char status, unsigned char * vm)
{
    unsigned char direction = 0;

    // power area range: 0 pixel to (width-5) pixel, express power 0%-100%
    power = power / (100 / (width - 5));
    if (power >= (width - 5))
        power = width - 5;

    // Recharge status
    if (status == true)
        fg = GREEN;

    if (direction) {
        // battery back ground
        display_solid_rect(y, x, width, height, bg, vm);
        // battery rim
        display_hollow_rect(y, x, width, height, fg, vm);
        display_hollow_rect(y + 1, x + 1, width - 2, height - 2, fg, vm);
        // display power area
        if (power < width / 4)
            display_solid_rect(y + 3, x + 3, power, height - 5, RED, vm);
        else
            display_solid_rect(y + 3, x + 3, power, height - 5, fg, vm);
        // display no power blank area
        display_solid_rect(y + 3, x + 3 + power, (width - 5 - power), height - 5, bg, vm);
        // display battery head
        display_solid_rect(y + 2, x + width + 1, 2, height - 3, fg, vm);
    } else {
        // battery back ground
        display_solid_rect(y, x, width, height, bg, vm);
        // battery rim
        display_hollow_rect(y, x, width, height, fg, vm);
        display_hollow_rect(y + 1, x + 1, width - 2, height - 2, fg, vm);
        // display power area
        if (power < width / 4)
            display_solid_rect(y + 3, x + 3 + (width - 5 - power), power, height - 5, RED, vm);
        else
            display_solid_rect(y + 3, x + 3 + (width - 5 - power), power, height - 5, fg, vm);
        // display no power blank area
        display_solid_rect(y + 3, x + 3, (width - 5 - power), height - 5, bg, vm);
        // display battery head
        // display_solid_rect(y + 2, x - 2, 2, height - 3, fg, vm);
        display_solid_rect(y + 4, x - 2, 2, height - 7, fg, vm);

        // battery right chamfer
        display_solid_rect(y, x, 1, 1, bg, vm);
        display_solid_rect(y + height, x, 1, 1, bg, vm);
        display_solid_rect(y, x + width, 1, 1, bg, vm);
        display_solid_rect(y + height, x + width, 1, 1, bg, vm);
    }
}

void display_recording_mark(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char status, unsigned char * vm)
{
    if (!status)
        return;

    display_solid_rect(y, x, width, height, bg, vm);
    display_mark_content(y + 2, x + 2, MANUAL_ALIGN, LAYOUT_R11, 0, "RECORDING", TEMP_CONTENT, fg, UNSELECT, vm);
}

void display_maxmin_mark(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char status, unsigned char * vm)
{
    if (!status)
        return;

    display_solid_rect(y, x, width, height, bg, vm);
    display_mark_content(y + 2, x + 2, MANUAL_ALIGN, LAYOUT_R11, 0, "MAX/MIN", TEMP_CONTENT, fg, UNSELECT, vm);
}

void display_hold_mark(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char status, unsigned char * vm)
{
    if (!status)
        return;

    display_solid_rect(y, x, width, height, bg, vm);
    display_mark_content(y + 2, x + 2, MANUAL_ALIGN, LAYOUT_R11, 0, "HOLD", TEMP_CONTENT, fg, UNSELECT, vm);
}

/**
 * [DC VOLTAGE, BASE (mV)]
 * 60
 * 600
 * 6000
 * 60000
 * 600000
 * 1000000
 * 
 * [AC VOLTAGE, BASE (mV)]
 * 600
 * 6000
 * 60000
 * 600000
 * 1000000
 * 
 * [DC CURRENT, BASE (uA)]
 * 600
 * 6000
 * 60000
 * 600000
 * 6000000
 * 10000000
 * 
 * [AC CURRENT, BASE (uA)]
 * 600
 * 6000
 * 60000
 * 600000
 * 6000000
 * 10000000
 * 
 * [RES, BASE (oumu)]
 * 600
 * 6000
 * 60000
 * 600000
 * 6000000
 * 60000000
 * 
 * [CAP, BASE (nF)]
 * 60
 * 600
 * 6000
 * 60000
 * 600000
 * 6000000
 * 60000000
 */

struct ruler_module_t {
    unsigned char    param_num;
    unsigned int    param_incr;

    unsigned int   ruler_width;
    unsigned char ruler_height;
    unsigned char  scale_width;
    unsigned char    scale_num;

    // 60(mV) / 245 = 0.25(mv/pix)
    float pixel_weight;
};

const struct ruler_module_t ruler_module[7][7] = {
    // [DC VOLTAGE, BASE (mV)]
    {
        {6, 10,  216, 12, 18, 12, 0},
        {6, 100, 216, 12, 18, 12, 0},
        {6, 1,   216, 12, 18, 12, 0},
        {6, 10,  216, 12, 18, 12, 0},
        {6, 100, 216, 12, 18, 12, 0},
        {5, 200, 220, 12, 22, 10, 0},
        {0, 0,   0,   0,  0,  0,  0},
    },

    // [AC VOLTAGE, BASE (mV)]
    {
        {6, 100, 216, 12, 18, 12, 0},
        {6, 1,   216, 12, 18, 12, 0},
        {6, 10,  216, 12, 18, 12, 0},
        {6, 100, 216, 12, 18, 12, 0},
        {5, 200, 220, 12, 22, 10, 0},
        {0, 0,   0,   0,  0,  0,  0},
        {0, 0,   0,   0,  0,  0,  0},
    },

    // [DC CURRENT, BASE (uA)]
    {
        {6, 100,  216, 12, 18, 12, 0},
        {6, 1000, 216, 12, 18, 12, 0},
        {6, 10,   216, 12, 18, 12, 0},
        {6, 100,  216, 12, 18, 12, 0},
        {6, 1,    216, 12, 18, 12, 0},
        {5, 2,    220, 12, 22, 10, 0},
        {0, 0,    0,   0,  0,  0,  0},
    },

    // [AC CURRENT, BASE (uA)]
    {
        {6, 100,  216, 12, 18, 12, 0},
        {6, 1000, 216, 12, 18, 12, 0},
        {6, 10,   216, 12, 18, 12, 0},
        {6, 100,  216, 12, 18, 12, 0},
        {6, 1,    216, 12, 18, 12, 0},
        {5, 2,    220, 12, 22, 10, 0},
        {0, 0,    0,   0,  0,  0,  0},
    },

    // [RES, BASE (oumu)]
    {
        {6, 100, 216, 12, 18, 12, 0}, 
        {6, 1,   216, 12, 18, 12, 0}, 
        {6, 10,  216, 12, 18, 12, 0}, 
        {6, 100, 216, 12, 18, 12, 0},
        {6, 1,   216, 12, 18, 12, 0},
        {6, 10,  216, 12, 18, 12, 0},
        {0, 0,   0,   0,  0,  0,  0},
    },

    // [CAP, BASE (nF)]
    {
        {6, 10,   216, 12, 18, 12, 0}, 
        {6, 100,  216, 12, 18, 12, 0}, 
        {6, 1,    216, 12, 18, 12, 0}, 
        {6, 10,   216, 12, 18, 12, 0}, 
        {6, 100,  216, 12, 18, 12, 0},
        {6, 1000, 216, 12, 18, 12, 0},
        {6, 10,   216, 12, 18, 12, 0},
    },
};

void display_ruler(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, unsigned char progress, unsigned char function, unsigned long range, unsigned char negative_value, unsigned char * vm)
{
    #define FONT_HEIGHT 16
    #define NEGATIVE_LENGTH 10

    unsigned char param_str[8];
    unsigned char scale_height = 10;
    unsigned int  temp_x = x;
    unsigned char offset_y = 0;

    if (negative_value == true) {
        display_solid_rect(y + FONT_HEIGHT + (ruler_module[function][range].ruler_height - 2), x, NEGATIVE_LENGTH - 3, 3, fg, vm);
    }

    for (unsigned char param_num = 0; param_num < (ruler_module[function][range].param_num + 1); param_num++) {
        sprintf(param_str, "%d", param_num * ruler_module[function][range].param_incr);
        display_widget_content(y, x + NEGATIVE_LENGTH + ruler_module[function][range].scale_width * 2 * param_num, MANUAL_ALIGN, 0, 0, param_str, TEMP_CONTENT, fg, UNSELECT, vm);
    }

    for (unsigned char scale_num = 0; scale_num < (ruler_module[function][range].scale_num + 1); scale_num++) {
        display_dotted_line(y + FONT_HEIGHT + offset_y, temp_x + NEGATIVE_LENGTH,     scale_height, 1, 1, fg, vm);
        display_dotted_line(y + FONT_HEIGHT + offset_y, temp_x + NEGATIVE_LENGTH + 1, scale_height, 1, 1, fg, vm);
        temp_x += ruler_module[function][range].scale_width;

        if (scale_num % 2 == 0) {
            scale_height = 5;
            offset_y = scale_height;
        } else {
            scale_height = 10;
            offset_y = 0;
        }
    }

    scale_height = 10;
    display_dotted_line(y + FONT_HEIGHT + scale_height,     x + NEGATIVE_LENGTH, (ruler_module[function][range].scale_width * ruler_module[function][range].scale_num + 2), 1, 0, fg, vm);
    display_dotted_line(y + FONT_HEIGHT + scale_height + 1, x + NEGATIVE_LENGTH, (ruler_module[function][range].scale_width * ruler_module[function][range].scale_num + 2), 1, 0, fg, vm);
    // display_dotted_line(y + FONT_HEIGHT + scale_height,     x + NEGATIVE_LENGTH, ruler_module[function][range].ruler_width + 2, 1, 0, fg, vm);
    // display_dotted_line(y + FONT_HEIGHT + scale_height + 1, x + NEGATIVE_LENGTH, ruler_module[function][range].ruler_width + 2, 1, 0, fg, vm);
    // red color progress
    display_solid_rect(y + FONT_HEIGHT + scale_height, x + NEGATIVE_LENGTH, progress, 6, fg, vm);
}

void display_ruler_percent_mode0(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, char percentage, int value_max, unsigned char * vm)
{
    #define FONT_HEIGHT 16
    #define NEGATIVE_LENGTH 10
    #define RULER_HEIGHT 12

    unsigned char param_str[8];
    unsigned char scale_height = 10;
    unsigned int  temp_x = x;
    unsigned char offset_y = 0;

    struct ruler_module_t ruler;

    if (percentage < 0) {
        display_solid_rect(y + FONT_HEIGHT + (RULER_HEIGHT - 2), x, NEGATIVE_LENGTH - 3, 3, fg, vm);
    }

    if ((value_max % 6) == 0) {
        ruler.param_num = 6;
        ruler.scale_num = 12;
        ruler.scale_width = 18;

        ruler.param_incr = value_max / 6;
    } else {
        ruler.param_num = 5;
        ruler.scale_num = 10;
        ruler.scale_width = 22;

        ruler.param_incr = value_max / 5;
    }

    for (unsigned char param_num = 0; param_num < (ruler.param_num + 1); param_num++) {
        sprintf(param_str, "%d", param_num * ruler.param_incr);
        display_widget_content(y, x + NEGATIVE_LENGTH + ruler.scale_width * 2 * param_num, MANUAL_ALIGN, 0, 0, param_str, TEMP_CONTENT, fg, UNSELECT, vm);
    }

    for (unsigned char scale_num = 0; scale_num < (ruler.scale_num + 1); scale_num++) {
        display_dotted_line(y + FONT_HEIGHT + offset_y, temp_x + NEGATIVE_LENGTH,     scale_height, 1, 1, fg, vm);
        display_dotted_line(y + FONT_HEIGHT + offset_y, temp_x + NEGATIVE_LENGTH + 1, scale_height, 1, 1, fg, vm);
        temp_x += ruler.scale_width;

        if (scale_num % 2 == 0) {
            scale_height = 5;
            offset_y = scale_height;
        } else {
            scale_height = 10;
            offset_y = 0;
        }
    }

    scale_height = 10;
    display_dotted_line(y + FONT_HEIGHT + scale_height,     x + NEGATIVE_LENGTH, (ruler.scale_width * ruler.scale_num + 2), 1, 0, fg, vm);
    display_dotted_line(y + FONT_HEIGHT + scale_height + 1, x + NEGATIVE_LENGTH, (ruler.scale_width * ruler.scale_num + 2), 1, 0, fg, vm);
    // red color progress
    if (abs(percentage) <= 100)
        display_solid_rect(y + FONT_HEIGHT + scale_height + 2, x + NEGATIVE_LENGTH, (ruler.scale_width * ruler.scale_num) * abs(percentage) / 100 + 2, 4, RED, vm);
    else {
        display_solid_rect(y + FONT_HEIGHT + scale_height + 2, x + NEGATIVE_LENGTH, ruler.scale_width * ruler.scale_num + 2, 4, RED, vm);
        display_status_logo(y + FONT_HEIGHT + 3, x + NEGATIVE_LENGTH + (ruler.scale_width * ruler.scale_num) + 4, WHITE, BLACK, RULER_OVERFLOW, 1, vm);
    }
}

struct bar_chart_t {
    unsigned char param_count;
    unsigned int  param_incr;
    unsigned char param_height;
    unsigned char scale_width;
    unsigned char scale_height;
    unsigned char scale_count;
    unsigned char negative_length;
};

void display_ruler_percent_mode(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, char percentage, int value_max, unsigned char * vm)
{
    struct bar_chart_t bar_chart;

    unsigned char param_string[8];
    unsigned char offset_y = 0;

    if ((value_max % 6) == 0) {
        bar_chart.param_count = 6;
        bar_chart.param_height = 15;
        bar_chart.param_incr = value_max / 6;
        bar_chart.scale_width = 4;
        bar_chart.scale_count = 60;
        bar_chart.negative_length = 10;
    } else {
        bar_chart.param_count = 5;
        bar_chart.param_height = 15;
        bar_chart.param_incr = value_max / 5;
        bar_chart.scale_width = 4;
        bar_chart.scale_count = 50;
        bar_chart.negative_length = 10;
    }

    if (percentage < 0)
        display_solid_rect(y + bar_chart.param_height + 11, x, bar_chart.negative_length - 4, 4, fg, vm);

    for (unsigned char i = 0; i < (bar_chart.param_count + 1); i++) {
        sprintf(param_string, "%d", i * bar_chart.param_incr);
        display_widget_content(y, x + bar_chart.negative_length + bar_chart.scale_width * 10 * i - 2, 
            MANUAL_ALIGN, 0, 0, param_string, TEMP_CONTENT, fg, UNSELECT, vm);
    }

    for (unsigned char i = 0; i < bar_chart.scale_count + 1; i++) {
        if (i % 5 == 0) {
            bar_chart.scale_height = 8;
            offset_y = 0;
        } else {
            bar_chart.scale_height = 4;
            offset_y = 4;
        }
        display_dotted_line(y + bar_chart.param_height + offset_y, x + bar_chart.negative_length + bar_chart.scale_width * i, bar_chart.scale_height, 1, 1, fg, vm);
    }
    bar_chart.scale_height = 8;

    for (unsigned char i = 0; i < bar_chart.scale_count + 1; i++)
        display_solid_rect(y + bar_chart.param_height + bar_chart.scale_height + 2, x + bar_chart.negative_length + bar_chart.scale_width * i - 1, 3, 6, fg, vm);

    // red color progress
    if (abs(percentage) <= 100)
        display_solid_rect(y + bar_chart.param_height + bar_chart.scale_height + 2, x + bar_chart.negative_length - 1, (bar_chart.scale_width * bar_chart.scale_count) * abs(percentage) / 100 + 3, 6, RED, vm);
    else
        display_status_logo(y + bar_chart.param_height + bar_chart.scale_height + 1, x + bar_chart.negative_length + (bar_chart.scale_width * bar_chart.scale_count) + 4, WHITE, BLACK, RULER_OVERFLOW, 1, vm);
}

void display_setting_dock(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned int rows, unsigned char row_gap, unsigned char select_num, unsigned char * vm)
{
    unsigned int color;
    unsigned char items = rows;

    for (; items > 0; items--) {
        if (items == (rows - select_num))
            color = fg;
        else
            color = bg;

        // display_solid_rect(y, x, width, height, color, vm);
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

struct message_tips_t message_tips[5] = {
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

void active_tips(struct message_tips_t * tips, unsigned int reside_time)
{
    tips->reside_time = reside_time;
    tips->active = true;
}

void inactive_tips(struct message_tips_t * tips)
{
    tips->reside_time = 0;
    tips->active = false;
}

void inactive_all_tips(struct message_tips_t tips[])
{
    unsigned char n = sizeof(message_tips) / sizeof(struct message_tips_t);

    for (unsigned char i = 0; i < n; i++) {
        tips[i].reside_time = 0;
        tips[i].active = false;
    }
}

void tips_timing(struct message_tips_t * tips)
{
    if (tips->reside_time > 0)
        tips->reside_time--;
}

void tips_all_timing(struct message_tips_t tips[])
{
    unsigned char n = sizeof(message_tips) / sizeof(struct message_tips_t);

    for (unsigned char i = 0; i < n; i++) {
        if (tips[i].reside_time > 0)
            tips[i].reside_time--;
    }
}

unsigned int second_convert_ticks(unsigned int second)
{
    #define TICKS_TIME_BASE 0.5
    return second / TICKS_TIME_BASE;
}

void display_tips(unsigned int y, unsigned int x, unsigned int tft_width, unsigned char fg, unsigned char bg, unsigned char font_size, struct message_tips_t * tips, unsigned char * vm)
{
    // unsigned char str_length;
    // unsigned char str_height;

    // if ((tips->active == false) || (tips->reside_time <= 0))
    //     return;

    // str_length = string_valid_width(font_size, (unsigned char *)tips_content[tips->content_num]);
    // str_height = string_valid_height(font_size, (unsigned char *)tips_content[tips->content_num]);

    // x = (int)((tft_width - str_length) / 2);

    // display_solid_rect(y, x, str_length + 4, str_height + 4, bg, vm);
    // display_hollow_rect(y, x, str_length + 4, str_height + 4, fg, vm);

    // display_string_auto_place(y + 2, x + 2, MANUAL_ALIGN, 0, 0, fg, font_size, (unsigned char *)tips_content[tips->content_num], UNSELECT, vm);

    unsigned char str_length = 0;
    unsigned char str_height = 0;

    unsigned char tips_buf[4][32];
    unsigned char line    = 0;
    unsigned char postion = 0;
    unsigned char len     = 0;

    if ((tips->active == false) || (tips->reside_time <= 0))
        return;

    for (unsigned char set = 0; set < 4; set++)
        memset(tips_buf[set], '\0', 32);

    for (unsigned char i = 0; i < strlen(tips_content[tips->content_num]); i++) {
        if (tips_content[tips->content_num][i] != '\n') {
            tips_buf[line][postion] = tips_content[tips->content_num][i];
            postion++;
        } else {
            line++;
            postion = 0;
        }
    }
    line++;

    for (unsigned char l = 0; l < line; l++) {
        len = string_valid_width(font_size, (unsigned char *)tips_buf[l]);
        if (len > str_length)
            str_length = len;
    }
    // str_length = string_valid_width(font_size, (unsigned char *)tips_content[tips->content_num]);
    str_height = string_valid_height(font_size, (unsigned char *)tips_content[tips->content_num]);

    x = (int)((tft_width - str_length) / 2);

    display_bevel_rect(y, x, str_length + 4, str_height * line + 4 * line, bg, 1, vm);
    // display_solid_rect(y, x, str_length + 4, str_height * line + 4 * line, bg, vm);
    // display_hollow_rect(y, x, str_length + 4, str_height * line + 4 * line, fg, vm);

    for (unsigned char l = 0; l < line; l++) {
        display_string_auto_place(y + 2, x + 2, MANUAL_ALIGN, 0, 0, fg, font_size, (unsigned char *)/*tips_content[tips->content_num]*/tips_buf[l], UNSELECT, vm);
        if (l != (line - 1))
            display_dotted_line(y + str_height + 4, x + 2, str_length, 2, 0, WHITE, vm);
        y = y + str_height + 4;
    }
}

const unsigned char bluetooth[] = {
    // 0x0c,0x00,0x0e,0x00,0x0f,0x00,0x8d,0x80,0xcc,0xc0,0x6c,0xc0,0x3d,0x80,0x1f,0x00,
    // 0x1f,0x00,0x3d,0x80,0x6c,0xc0,0xcc,0xc0,0x8d,0x80,0x0f,0x00,0x0e,0x00,0x0c,0x00,

    0x00,0x00,0x01,0xC0,0x01,0xE0,0x31,0xB0,0x19,0x98,0x0D,0x98,0x07,0xB0,0x03,0xE0,
    0x03,0xE0,0x07,0xB0,0x0D,0x98,0x19,0x98,0x31,0xB0,0x01,0xE0,0x01,0xC0,0x00,0x00,
};

const unsigned char poweroff_timer[] = {
    0x00,0x00,0x7D,0xBE,0x7D,0xBE,0x61,0x86,0x61,0x86,0x61,0x86,0x61,0x86,0x60,0x00,
    0x60,0xFE,0x60,0x92,0x60,0x92,0x60,0x9E,0x60,0x82,0x7E,0x82,0x7E,0xFE,0x00,0x00,
};

const unsigned char lighting[] = {
    // 0x01,0x00,0x03,0x00,0x03,0x00,0x07,0x00,0x07,0x00,0x0F,0x00,0x1F,0x00,0x1F,0xE0,
    // 0x3F,0xC0,0x07,0xC0,0x07,0x80,0x07,0x00,0x07,0x00,0x06,0x00,0x06,0x00,0x04,0x00,

    // 0x01,0xF8,0x03,0x30,0x06,0x60,0x0C,0xC0,0x19,0x80,0x33,0xFC,0x67,0xFE,0x40,0x02,
    // 0x7F,0xE6,0x3F,0xCC,0x01,0x98,0x03,0x30,0x06,0x60,0x0C,0xC0,0x19,0x80,0x3F,0x00,

    0x00,0x00,0x01,0xF0,0x03,0xE0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x3F,0xFE,0x7F,0xFE,
    0x7F,0xFC,0x00,0xF8,0x01,0xF0,0x03,0xE0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x00,0x00,
};

const unsigned char lo[] = {
    0xFF,0xFC,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x03,0x00,0x00,0x60,0x03,0x00,0x00,
    0x60,0x01,0x80,0x00,0x60,0x79,0x80,0x00,0x60,0xFC,0xC0,0x00,0x61,0xCE,0xC0,0x00,
    0x61,0x86,0x60,0x00,0x61,0x86,0x60,0x00,0x61,0x86,0x30,0x00,0x61,0xCE,0x30,0x00,
    0x7E,0xFC,0x18,0x00,0x7E,0x78,0x18,0x00,0x00,0x00,0x00,0x00,
};

const unsigned char loz[] = {
    0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,
    0x60,0x00,0x00,0x00,0x60,0x78,0xFC,0x00,0x60,0xFC,0xFC,0x00,0x61,0xCE,0x0C,0x00,
    0x61,0x86,0x18,0x00,0x61,0x86,0x30,0x00,0x61,0x86,0x60,0x00,0x61,0xCE,0xC0,0x00,
    0x7E,0xFC,0xFC,0x00,0x7E,0x78,0xFC,0x00,0x00,0x00,0x00,0x00,
};

const unsigned char ruler_overflow[] = {
    0x80,0xc0,0xe0,0xf0,0xf0,0xe0,0xc0,0x80,
};

const unsigned char ac_desc[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x7f,0x06,0xe3,0x8e,0xc1,0xfc,0x00,0xf8,
};

const unsigned char dc_desc[] = {
    0xff,0xfe,0xff,0xfe,0x00,0x00,0x00,0x00,0xdb,0x6e,0xdb,0x6e,0x00,0x00,0x00,0x00,
};

const unsigned char ac_dc_desc[] = {
    0xff,0xfe,0xff,0xfe,0x00,0x00,0x3e,0x00,0x7f,0x06,0xe3,0x8e,0xc1,0xfc,0x00,0xf8,
};

const unsigned char trumpet[] = {
    0x00,0x00,0x00,0x00,0x00,0xC8,0x01,0xC4,0x03,0xD2,0x3F,0xCA,0x7F,0xCA,0x7F,0xCA,
    0x7F,0xCA,0x7F,0xCA,0x3F,0xCA,0x03,0xD2,0x01,0xC4,0x00,0xC8,0x00,0x00,0x00,0x00,
};

const struct logo_data_t dmm_logo[] = {
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

struct logo_data_t read_logo_data(unsigned char logo_name)
{
    return dmm_logo[logo_name];
}
