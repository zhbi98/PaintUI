/**
 * @file display.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <math.h>
#include "display_string.h"
#include "menu_str.h"
#include "display.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    uint8_t param_cnt;
    uint32_t param_incr;
    uint8_t param_height;
    uint8_t scale_width;
    uint8_t scale_height;
    uint8_t scale_count;
    uint8_t sigh_len;
} bar_chart_t;

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static uint8_t rendererVM[rendererSIZE] = {0};
static const sym_desc_t sym_descs[];

static const 
uint16_t colorTrue[] = {
    /**< Dark color*/
    0x0000,/**< Black Color*/
    0xFFFF,/**< White Color*/
    0xF965,/**< Red Color*/
    0x5AEB,/**< Gray Color*/
    0x4AA9,/**< Dark Green Color*/
    0x07E0,/**< Green*/
    0x5351,/**< Dark Blue*/

    /**< Light color*/
    0xFFFF,/**< White Color*/
    0x0000,/**< Black Color*/
    0xFA49,/**< Red Color*/
    0x5AEB,/**< Gray Color*/
    0x4208,/**< Dark Brown Color*/
    0x07E0,/**< Green*/
    0x8DFF,/**< Dark Blue*/
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Retrieves the pointer to renderer video memory buffer
 * @return uint8_t* Pointer to the renderer's video memory buffer
 */
uint8_t * req_rendererVM()
{
    /**
     * This parameter is received using an array pointer
     * uint8_t (* req_rendererVM())[]
     */
    return rendererVM;
}

/**
 * Retrieves the pointer to the true color palette buffer, Buffer size 
 * depends on the current color palette configuration
 * @return uint16_t* Pointer to the true color palette array
 */
uint16_t * req_colorTrue()
{
    return colorTrue;
}

/**
 * Writes a pixel color value to the specified video memory location
 * @param y Vertical coordinate (row) of the pixel
 * @param x Horizontal coordinate (column) of the pixel 
 * @param color 8-bit color value to write
 * @param vm Pointer to video memory buffer
 */
void display_pixel(uint32_t y, uint32_t x, uint8_t color, uint8_t * vm)
{
    /**
     * Two colors
     * 
     * uint32_t idx = (y * TFT_WIDTH + x) / 8;
     * uint8_t pxindex = (y * TFT_WIDTH + x) % 8;
     *
     * # method 1:
     * vm[idx] = (vm[idx] & (~(0x01 << (7 - pxindex)))) | (color << (7 - pxindex));
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
     * case 0: vm[idx] = (vm[idx] & 0x7f) | (color << (7 - pxindex)); break;
     * case 1: vm[idx] = (vm[idx] & 0xbf) | (color << (7 - pxindex)); break;
     * case 2: vm[idx] = (vm[idx] & 0xdf) | (color << (7 - pxindex)); break;
     * case 3: vm[idx] = (vm[idx] & 0xef) | (color << (7 - pxindex)); break;
     * case 4: vm[idx] = (vm[idx] & 0xf7) | (color << (7 - pxindex)); break;
     * case 5: vm[idx] = (vm[idx] & 0xfb) | (color << (7 - pxindex)); break;
     * case 6: vm[idx] = (vm[idx] & 0xfd) | (color << (7 - pxindex)); break;
     * case 7: vm[idx] = (vm[idx] & 0xfe) | (color << (7 - pxindex)); break;
     * }
     *
     * # method 3:
     * const uint8_t split_byte[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
     * vm[idx] = (vm[idx] & split_byte[pxindex]) | (color << (7 - pxindex));
     */
    
    vm[y * TFT_WIDTH + x] = color;
}

/**
 * Draws a straight line between two points in video memory using Bresenham's algorithm
 * @param y1 Vertical coordinate of starting point (row)
 * @param x1 Horizontal coordinate of starting point (column)
 * @param y2 Vertical coordinate of ending point (row)
 * @param x2 Horizontal coordinate of ending point (column)
 * @param color 8-bit color value for the line
 * @param vm Pointer to video memory buffer
 */
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

/**
 * Draws a dotted line in video memory with specified spacing
 * @param y Vertical starting coordinate (row)
 * @param x Horizontal starting coordinate (column)
 * @param length Total length of the dotted line in pixels
 * @param space Spacing between dots in pixels
 * @param dir Direction flag (0=horizontal, 1=vertical)
 * @param color 8-bit color value for the dots
 * @param vm Pointer to video memory buffer
 */
void display_dotted_line(uint32_t y, uint32_t x, 
    uint32_t lenth, uint8_t space, uint8_t dir, 
    uint8_t color, uint8_t * vm)
{
    if (!dir) {
        for (uint32_t l = 0; l < lenth; l = l + space)
            display_pixel(y, x + l, color, vm);
    } else {
        for (uint32_t l = 0; l < lenth; l = l + space)
            display_pixel(y + l, x, color, vm);
    }
}

/**
 * Draws a hollow rectangle in video memory using four line segments
 * @param y Top-left vertical coordinate (row)
 * @param x Top-left horizontal coordinate (column)
 * @param width Width of the rectangle in pixels
 * @param height Height of the rectangle in pixels
 * @param color 8-bit color value for the rectangle border
 * @param vm Pointer to video memory buffer
 */
void display_hollow_rect(uint32_t y, uint32_t x, 
    uint32_t width, uint32_t height, uint8_t color, uint8_t * vm)
{
    display_line(y, x, y, x + width, color, vm);
    display_line(y, x + width, y + height, x + width, color, vm);
    display_line(y + height, x + width, y + height, x, color, vm);
    display_line(y, x, y + height, x, color, vm);
}

/**
 * Draws a solid filled rectangle in video memory
 * @param y Top-left vertical coordinate (row)
 * @param x Top-left horizontal coordinate (column) 
 * @param width Width of the rectangle in pixels
 * @param height Height of the rectangle in pixels
 * @param color 8-bit color value for the rectangle
 * @param vm Pointer to video memory buffer
 */
void display_solid_rect(uint32_t y, uint32_t x, 
    uint32_t width, uint32_t height, uint8_t color, uint8_t * vm)
{
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++)
            display_pixel(y + i, x + j, color, vm);
    }
}

/**
 * Draws a beveled rectangle with chamfered edges in video memory
 * @param y Top-left vertical coordinate (row)
 * @param x Top-left horizontal coordinate (column)
 * @param width Width of the rectangle in pixels
 * @param height Height of the rectangle in pixels 
 * @param color 8-bit color value for the rectangle
 * @param chamfer Size of the chamfered edges in pixels
 * @param vm Pointer to video memory buffer
 */
void display_bevel_rect(uint32_t y, uint32_t x, 
    uint32_t width, uint32_t height, uint32_t color, 
    uint8_t chamfer, uint8_t * vm)
{
    for (uint32_t i = chamfer; i > 0; i--) {
        for (uint32_t j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, color, vm);
        }
        y++;
        height--;
    }
    for (uint32_t i = 0; i < (height - chamfer * 2); i++) {
        for (uint32_t j = 0; j < width; j++) {
            display_pixel(y, x + j, color, vm);
        }
        y++;
    }
    for (uint32_t i = 0; i < chamfer + 1; i++) {
        for (uint32_t j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, color, vm);
        }
        y++;
    }
}

/**
 * Draws a rectangle with rounded corners (fillet) in video memory
 * @param y Top-left vertical coordinate (row)
 * @param x Top-left horizontal coordinate (column)
 * @param width Total width of the rectangle in pixels
 * @param height Total height of the rectangle in pixels
 * @param color 8-bit color value for the rectangle
 * @param radius Corner rounding radius in pixels
 * @param vm Pointer to video memory buffer
 */
void display_fillet_rect(uint32_t y, uint32_t x, 
    uint32_t width, uint32_t height, uint32_t color, 
    uint8_t radius, uint8_t * vm)
{
    uint32_t a = 0, b = 0;
    uint32_t j = 0;

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

/**
 * Draws a hollow triangle outline in video memory
 * @param y Bottom-left vertical coordinate (row)
 * @param x Bottom-left horizontal coordinate (column)
 * @param width Base width of the triangle in pixels
 * @param height Height of the triangle in pixels
 * @param color 8-bit color value for the triangle outline
 * @param vm Pointer to video memory buffer
 */
void display_hollow_triangle(uint32_t y, uint32_t x, 
    uint32_t width, uint32_t height, uint8_t color, uint8_t * vm)
{
    display_line(y + height, x, y, x + width / 2, color, vm);
    display_line(y, x + width / 2, y + height, x + width, color, vm);
    display_line(y + height, x + width, y + height, x, color, vm);
}

/**
 * Draws a circle outline using Bresenham's algorithm
 * @param y Vertical center coordinate of the circle
 * @param x Horizontal center coordinate of the circle 
 * @param r Radius of the circle in pixels
 * @param color 16-bit color value for the circle
 * @param vm Pointer to video memory buffer
 */
void _display_circle(uint16_t y, uint16_t x, uint16_t r, 
    uint16_t color, uint8_t * vm)
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

/**
 * Draws a circle outline using Bresenham's algorithm
 * @param y Vertical center coordinate of the circle
 * @param x Horizontal center coordinate of the circle 
 * @param r Radius of the circle in pixels
 * @param color 16-bit color value for the circle
 * @param vm Pointer to video memory buffer
 */
void display_circle(uint16_t y, uint16_t x, uint16_t r, 
    uint16_t color, uint8_t * vm)
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

/**
 * Displays a single character on screen using a bitmap font.
 * @param y Starting Y coordinate (top position).
 * @param x Starting X coordinate (left position).
 * @param width Width of each character in pixels.
 * @param height Height of each character in pixels.
 * @param fg Foreground color (pixel on).
 * @param bg Background color (pixel off, 0 means transparent).
 * @param start_char First character in font library.
 * @param character Character to display.
 * @param fontlib Pointer to font bitmap data.
 * @param vm Pointer to video memory/framebuffer.
 */
void display_sym(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, 
    uint8_t _sym, uint8_t status, uint8_t * vm)
{
    uint32_t width = 0, height = 0;

    uint32_t total_byte = 0; /*Total bytes per character in font data*/
    uint32_t column = 0; /*Font data address offset*/
    uint32_t tx, ty; /*Current column counter*/

    if (!status) return; /*Do not show this logo*/

    ty = y;
    tx = x;

    width = sym_descs[_sym].width;
    height = sym_descs[_sym].height;

    /*How many bytes are needed for a character*/
    total_byte = (int)((width + 7) / 8) * height;

    for (int i = 0; i < total_byte; i++) {
        for (int j = 0; j < 8; j++) {
            if (sym_descs[_sym].data[i] & (0x80 >> j)) {
                display_pixel(ty, tx, fg, vm);
            } else {
                if (1/*bg != 0*/) display_pixel(ty, tx, bg, vm);
            }
            tx++;
            column++;
            if (column >= width) {
                column = 0; /*Reset column counter*/
                ty++; /*Move to next line*/
                tx = x; /*Reset x position*/
                break; /*Skip remaining bits in this byte*/
            }
        }
    }
}

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _time Duration in ticks for the alert to remain active
 */
void display_battery(uint32_t y, uint32_t x, 
    uint32_t width, uint32_t height, uint8_t fg, uint8_t bg, 
    uint8_t power, uint8_t status, uint8_t * vm)
{
    uint8_t dir = 0;

    /*power area range: 0 pixel to (width-5) pixel, express power 0%-100%*/
    power = power / (100 / (width - 5));
    if (power >= (width - 5))
        power = width - 5;

    /*Recharge status*/
    if (status) fg = GREEN;

    if (dir) {
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
        if (power < width / 4) 
            display_solid_rect(y + 3, x + 3 + (width - 5 - power), power, height - 5, RED, vm);
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

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _time Duration in ticks for the alert to remain active
 */
void display_barchart(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, 
    int8_t _per, int32_t valmax, uint8_t * vm)
{
    uint8_t param_string[8] = {0};
    bar_chart_t bar_chart = {0};
    uint8_t offset_y = 0;

    if ((valmax % 6) == 0) {
        bar_chart.param_cnt = 6;
        bar_chart.param_height = 15;
        bar_chart.param_incr = valmax / 6;
        bar_chart.scale_width = 4;
        bar_chart.scale_count = 60;
        bar_chart.sigh_len = 10;
    } else {
        bar_chart.param_cnt = 5;
        bar_chart.param_height = 15;
        bar_chart.param_incr = valmax / 5;
        bar_chart.scale_width = 4;
        bar_chart.scale_count = 50;
        bar_chart.sigh_len = 10;
    }

    if (_per < 0) display_solid_rect(
        y + bar_chart.param_height + 11, x, 
        bar_chart.sigh_len - 4, 4, fg, vm);

    for (uint8_t i = 0; i < (bar_chart.param_cnt + 1); i++) {
        sprintf(param_string, "%d", i * bar_chart.param_incr);
        display_N1string(y, x + bar_chart.sigh_len + bar_chart.scale_width * 10 * i - 2, 
            ALIGN_SPECIFY, 0, 0, param_string, _MENU_LAST, fg, INVE_NONE, vm);
    }

    for (uint8_t i = 0; i < bar_chart.scale_count + 1; i++) {
        if (i % 5 == 0) {
            bar_chart.scale_height = 8;
            offset_y = 0;
        } else {
            bar_chart.scale_height = 4;
            offset_y = 4;
        }

        display_dotted_line(y + bar_chart.param_height + offset_y, 
            x + bar_chart.sigh_len + bar_chart.scale_width * i, 
            bar_chart.scale_height, 1, 1, fg, vm);
    }
    bar_chart.scale_height = 8;

    for (uint8_t i = 0; i < bar_chart.scale_count + 1; i++) {
        display_solid_rect(y + bar_chart.param_height + bar_chart.scale_height + 2, 
            x + bar_chart.sigh_len + bar_chart.scale_width * i - 1, 3, 6, fg, vm);
    }

    /*Red color progress*/
    if (abs(_per) <= 100) {
        display_solid_rect(y + bar_chart.param_height + bar_chart.scale_height + 2, 
            x + bar_chart.sigh_len - 1, (bar_chart.scale_width * bar_chart.scale_count) * \
            abs(_per) / 100 + 3, 6, RED, vm);
    } else {
        display_sym(y + bar_chart.param_height + bar_chart.scale_height + 1, 
            x + bar_chart.sigh_len + (bar_chart.scale_width * bar_chart.scale_count) + 4, 
            WHITE, BLACK, SYM_BCHT_OVE, 1, vm);
    }
}

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _time Duration in ticks for the alert to remain active
 */
void display_dock(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint32_t rows, uint8_t row_gap, 
    uint8_t linecur, uint8_t * vm)
{
    uint32_t color;
    uint8_t items = rows;

    for (; items > 0; items--) {
        if (items == (rows - linecur)) color = fg;
        else color = bg;
        display_bevel_rect(y, x, width, height, color, 1, vm);
        y = y + height + row_gap;
    }

    /**
     * for (; items > 0; items--) {
     *     if (items == (rows - linecur))
     *         display_bevel_rect(y + 1, x + 5, width - 10, height - 2, fg, 1, vm);
     *     else
     *         display_bevel_rect(y, x, width, height, bg, 1, vm);
     *     y = y + height + row_gap;
     * }
     */
}

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _time Duration in ticks for the alert to remain active
 */
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

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _time Duration in ticks for the alert to remain active
 */
const uint8_t * _letter_get_str(_letter_t * _lettr_p)
{
    if (_lettr_p) return _lettr_p->letter;
    return " ";
}

/**
 * Finds the first occurrence of a character in a string.
 * @param str pointer to a string.
 * @param ch pointer to a character.
 * @param n data size.
 * @return index.
 */
static uint16_t _strchr(const int8_t * str, 
    int8_t ch, uint16_t * cur_p, uint16_t n)
{
    uint16_t i = 0;

    for (i = 0; i < n; i++) {
        if (str[i] == ch) {
            *cur_p = i;
            return true;
        }
    }
    return false;
}

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _tick Duration in ticks for the alert to remain active
 */
void alerts_refer(uint32_t y, uint32_t x, uint32_t tft_width, 
    uint8_t fg, uint8_t bg, uint8_t font_size, 
    dev_alerts_t * alerts_p, uint8_t * vm)
{
    const uint8_t * str_p = NULL;
    uint8_t str_high = 0;
    uint8_t str_len = 0;
    uint8_t line = 1;
    uint8_t byte = 0;

    if (!alerts_p->active || !alerts_p->_tick) return;
    uint16_t _spec = strlen(alerts_p->specify);

    /*If a special display is specified, 
    the specified content is executed*/
    if (_spec > 0) str_p = alerts_p->specify;
    else str_p = tips_content[alerts_p->stridx];

    /*Calculates the heigh required for a line 
    of string to appear on the screen*/
    str_high = string_valid_height(font_size, str_p);

    while (str_p[byte] != '\0') {
        if (str_p[byte] == '\n') line++;
        byte++;
    }

    uint8_t str[48] = {0};
    uint16_t _start = 0;
    uint16_t _end = 0;
    uint16_t _len = 0;
    uint16_t len = 0;

    /**
     * Extract the string line by line, selecting the line 
     * with the longest length as the final display width
     */
    for (uint8_t _line = 0; _line < line; _line++) {
        if (_line != (line - 1)) {
            _strchr(&str_p[_start], '\n', 
                &_end, byte - _start);
            _end += _start;
            _len = _end - _start;
        } else _len = byte - _end;

        memset(str, '\0', 48);
        strncpy(str, &str_p[_start], _len);

        /*Calculates the width required for a line 
        of string to appear on the screen*/
        len = string_valid_width(font_size, str);
        if (len > str_len) str_len = len;
        _start = _end + 1;
    }

    uint16_t bg_high = (str_high + 6) * line;
    uint16_t bg_wid = str_len + 6;

    /**To color the background*/
    x += ((tft_width - bg_wid) / 2);
    display_bevel_rect(y, x, bg_wid, 
        bg_high, bg, 4, vm);

    _start = 0; _end = 0; _len = 0;

    /**Extract and display the contents line by 
     * line according to the carriage return*/
    for (uint8_t _line = 0; _line < line; _line++) {
        if (_line != (line - 1)) {
            _strchr(&str_p[_start], '\n', 
                &_end, byte - _start);
            _end += _start;
            _len = _end - _start;
        } else _len = byte - _end;

        memset(str, '\0', 48);
        strncpy(str, &str_p[_start], _len);

        /**Extract and display the contents line by 
         * line according to the carriage return*/
        display_string_align(y + 2, x + 3, 
            ALIGN_SPECIFY, 0, 0, fg, font_size, 
            str, INVE_NONE, vm);

        if (_line != (line - 1)) { /*Draw the divider line*/
            display_dotted_line(y + str_high + 4, 
                x + 2, str_len, 2, 0, fg, vm);
        }

        y += (str_high + 4);
        _start = _end + 1;
    }
}

/**
 * Activates a device alert with specified duration
 * @param alerts_p Pointer to the device alert structure
 * @param _tick Duration in ticks for the alert to remain active
 */
void alerts_call(dev_alerts_t * alerts_p, 
    const uint8_t * str_p, uint32_t _tick)
{
    if (str_p != NULL) {
        memset(alerts_p->specify, '\0', 64);
        strcpy(alerts_p->specify, str_p);
    }

    alerts_p->_tick = _tick;
    alerts_p->active = true;
}

/**
 * Deactivates a single device alert
 * @param alerts_p Pointer to the device alert structure to deactivate
 */
void alerts_off(dev_alerts_t * alerts_p)
{
    memset(alerts_p->specify, '\0', 64);
    alerts_p->active = false;
    alerts_p->_tick = 0;
}

/**
 * Deactivates all device _alerts in an array
 * @param _alerts Array of device alert structures to deactivate
 * Note: Array size is determined at runtime using sizeof
 */
void alerts_offAll(dev_alerts_t _alerts[], uint8_t nr)
{
    uint8_t _all = nr;
    for (uint8_t i = 0; i < _all; i++) {
        memset(_alerts[i].specify, '\0', 64);
        _alerts[i].active = false;
        _alerts[i]._tick = 0;
    }
}

/**
 * Decrements the timer for a single active alert
 * @param alerts_p Pointer to the device alert structure to process
 * Only decrements if time remaining is greater than 0
 */
void alerts_tick_work(dev_alerts_t * alerts_p)
{
    if (alerts_p->_tick > 0)
        alerts_p->_tick--;
}

/**
 * Decrements timers for all active _alerts in an array
 * @param _alerts Array of device alert structures to process
 * Note: Array size is determined at runtime using sizeof
 */
void alerts_tick_workAll(dev_alerts_t _alerts[], uint8_t nr)
{
    uint8_t _all = nr;

    for (uint8_t i = 0; i < _all; i++) {
        if (_alerts[i]._tick > 0)
            _alerts[i]._tick--;
    }
}

/**
 * Decrements timers for all active _alerts in an array
 * @param _alerts Array of device alert structures to process
 * Note: Array size is determined at runtime using sizeof
 */
bool alerts_get_state(dev_alerts_t * alerts_p)
{
    if (!alerts_p->active) return false;
    if (!alerts_p->_tick) return false;
    return true;
}

/**
 * Decrements timers for all active _alerts in an array
 * @param _alerts Array of device alert structures to process
 * Note: Array size is determined at runtime using sizeof
 */
bool alerts_is_active(dev_alerts_t _alerts[], uint8_t nr)
{
    uint8_t _all = nr;
    for (uint8_t i = 0; i < _all; i++)
        if (_alerts[i]._tick > 0) return true;
    return false;
}

/**********************
 *  STATIC VARIABLES
 **********************/

static const uint8_t ble_desc[] = {
0x00,0x00,0x01,0xC0,0x01,0xE0,0x31,0xB0,0x19,0x98,0x0D,0x98,0x07,0xB0,0x03,0xE0,
0x03,0xE0,0x07,0xB0,0x0D,0x98,0x19,0x98,0x31,0xB0,0x01,0xE0,0x01,0xC0,0x00,0x00,
};

static const uint8_t poff_desc[] = {
0x00,0x00,0x7D,0xBE,0x7D,0xBE,0x61,0x86,0x61,0x86,0x61,0x86,0x61,0x86,0x60,0x00,
0x60,0xFE,0x60,0x92,0x60,0x92,0x60,0x9E,0x60,0x82,0x7E,0x82,0x7E,0xFE,0x00,0x00,
};

static const uint8_t lighting_desc[] = {
0x00,0x00,0x01,0xF0,0x03,0xE0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x3F,0xFE,0x7F,0xFE,
0x7F,0xFC,0x00,0xF8,0x01,0xF0,0x03,0xE0,0x07,0xC0,0x0F,0x80,0x1F,0x00,0x00,0x00,
};

static const uint8_t lo_desc[] = {
0xFF,0xFC,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x03,0x00,0x00,0x60,0x03,0x00,0x00,
0x60,0x01,0x80,0x00,0x60,0x79,0x80,0x00,0x60,0xFC,0xC0,0x00,0x61,0xCE,0xC0,0x00,
0x61,0x86,0x60,0x00,0x61,0x86,0x60,0x00,0x61,0x86,0x30,0x00,0x61,0xCE,0x30,0x00,
0x7E,0xFC,0x18,0x00,0x7E,0x78,0x18,0x00,0x00,0x00,0x00,0x00,
};

static const uint8_t loz_desc[] = {
0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,
0x60,0x00,0x00,0x00,0x60,0x78,0xFC,0x00,0x60,0xFC,0xFC,0x00,0x61,0xCE,0x0C,0x00,
0x61,0x86,0x18,0x00,0x61,0x86,0x30,0x00,0x61,0x86,0x60,0x00,0x61,0xCE,0xC0,0x00,
0x7E,0xFC,0xFC,0x00,0x7E,0x78,0xFC,0x00,0x00,0x00,0x00,0x00,
};

static const uint8_t bcht_ove_desc[] = {
0x80,0xc0,0xe0,0xf0,0xf0,0xe0,0xc0,0x80,
};

static const uint8_t ac_desc[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x7f,0x06,0xe3,0x8e,0xc1,0xfc,0x00,0xf8,
};

static const uint8_t dc_desc[] = {
0xff,0xfe,0xff,0xfe,0x00,0x00,0x00,0x00,0xdb,0x6e,0xdb,0x6e,0x00,0x00,0x00,0x00,
};

static const uint8_t ac_dc_desc[] = {
0xff,0xfe,0xff,0xfe,0x00,0x00,0x3e,0x00,0x7f,0x06,0xe3,0x8e,0xc1,0xfc,0x00,0xf8,
};

static const uint8_t trumpet_desc[] = {
0x00,0x00,0x00,0x00,0x00,0xC8,0x01,0xC4,0x03,0xD2,0x3F,0xCA,0x7F,0xCA,0x7F,0xCA,
0x7F,0xCA,0x7F,0xCA,0x3F,0xCA,0x03,0xD2,0x01,0xC4,0x00,0xC8,0x00,0x00,0x00,0x00,
};

const sym_desc_t sym_descs[] = {
    {
        .width = 16,
        .height = 16,
        .data = ble_desc,
    },

    {
        .width = 16,
        .height = 16,
        .data = poff_desc,
    },

    {
        .width = 16,
        .height = 16,
        .data = lighting_desc,
    },

    {
        .width = 32,
        .height = 15,
        .data = lo_desc,
    },

    {
        .width = 32,
        .height = 15,
        .data = loz_desc,
    },

    {
        .width = 8,
        .height = 8,
        .data = bcht_ove_desc,
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
        .data = trumpet_desc,
    },
};

/**
 * Reads and logs the valid width of each character in a font range.
 * @param font_size - Index of the font in the en_font array.
 * @param finish_character - Last character in the range to check.
 */
sym_desc_t sym_req_desc(uint8_t _sym)
{
    return sym_descs[_sym];
}
