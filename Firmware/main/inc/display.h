
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "display_string.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define TFT_WIDTH 320U
#define TFT_HEIGHT 240U
#define DISP_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT)

typedef struct {
    uint8_t  width;
    uint8_t height;
    const uint8_t * data;
} sym_desc_t;

enum {
	BLUETOOTH = 0,
	POWEROFF_TIMER,
	LIGHTING,
	LO,
	LOZ,
	RULER_OVERFLOW,
	AC_DESC,
	DC_DESC,
	AC_DC_DESC,
	TRUMPET,
};

typedef uint16_t sym_id_t;

enum {
	BLACK      = 0,
	WHITE      = 1,
	RED        = 2,
	GRAY       = 3,
	DARK_GREEN = 4,
	GREEN      = 5,
	DARK_BLUE  = 6,
	COLOR_MAX  = 7,
};

typedef uint16_t disp_color_t;

typedef struct {
    const uint32_t message_width;
    const uint32_t message_height;
    uint8_t active;
    uint32_t reside_time;
    const uint8_t content_num;
} dev_alerts_t;

typedef struct {
    uint8_t letter[32];
    uint8_t _len;
} _letter_t;

extern const uint16_t color_data[];
extern uint8_t display_buf[];
extern dev_alerts_t message_tips[];

uint8_t * tft_buf();
void display_pixel(uint32_t y, uint32_t x, uint8_t color, uint8_t * vm);
void display_line(uint32_t y1, uint32_t x1, 
    uint32_t y2, uint32_t x2, uint8_t color, uint8_t * vm);
void display_dotted_line(uint32_t y, uint32_t x, uint32_t lenth, uint8_t space, 
    uint8_t direction, uint8_t color, uint8_t * vm);
void display_hollow_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t color, uint8_t * vm);
void display_solid_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t color, uint8_t * vm);
void display_bevel_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint32_t color, uint8_t chamfer, uint8_t * vm);
void display_fillet_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint32_t color, uint8_t radius, uint8_t * vm);
void display_hollow_triangle(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t color, uint8_t * vm);
void _display_circle(uint16_t y, uint16_t x, uint16_t r, uint16_t color, uint8_t * vm);
void display_circle(uint16_t y, uint16_t x, uint16_t r, uint16_t color, uint8_t * vm);
void display_bookmark(int y, uint32_t x, uint32_t width, uint32_t height, 
    uint32_t color, uint8_t radian, uint8_t * vm);
void display_sym(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, 
    uint8_t logo_name, uint8_t status, uint8_t * vm);
void display_battery(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t power, uint8_t status, uint8_t * vm);
void display_recording_mark(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t status, uint8_t * vm);
void display_maxmin_mark(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t status, uint8_t * vm);
void display_hold_mark(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint8_t status, uint8_t * vm);
void display_barchart(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, 
    int8_t percentage, int32_t value_max, uint8_t * vm);
void display_dock(uint32_t y, uint32_t x, uint32_t width, uint32_t height, 
    uint8_t fg, uint8_t bg, uint32_t rows, uint8_t row_gap, uint8_t select_num, uint8_t * vm);
void active_tips(dev_alerts_t * tips, uint32_t reside_time);
void inactive_tips(dev_alerts_t * tips);
void inactive_all_tips(dev_alerts_t tips[]);
void tips_timing(dev_alerts_t * tips);
void tips_all_timing(dev_alerts_t tips[]);
void display_tips(uint32_t y, uint32_t x, uint32_t tft_width, 
    uint8_t fg, uint8_t bg, uint8_t font_size, 
    dev_alerts_t * tips, uint8_t * vm);
void _letter_refer(_letter_t * _lettr_p, const uint8_t * str_p, uint8_t _offs);
const uint8_t * _letter_get_str(_letter_t * _lettr_p);
sym_desc_t read_logo_data(uint8_t logo_name);

#endif
