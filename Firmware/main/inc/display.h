/**
 * @file display.h
 *
 */

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>
#include <stdint.h>
#include "alerts.h"

/*********************
 *      DEFINES
 *********************/

#define TFT_WIDTH 320U
#define TFT_HEIGHT 240U
#define rendererSIZE (TFT_WIDTH * TFT_HEIGHT)

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    const uint8_t * data;
    uint8_t width;
    uint8_t height;
} sym_desc_t;

enum {
	SYM_BLE = 0,
	SYM_POFF,
	SYM_LIGHTING,
	SYM_LO,
	SYM_LOZ,
	SYM_BCHT_OVE,
	SYM_AC,
	SYM_DC,
	SYM_ACDC,
	SYM_TRUMPET,
    _SYM_LAST,
};

typedef uint16_t sym_id_t;

enum {
	BLACK = 0,
	WHITE,
	RED,
	GRAY,
	DARK_GREEN,
	GREEN,
	DARK_BLUE,
	_COLOR_LAST,
};

typedef uint16_t disp_color_t;

typedef struct {
    uint8_t letter[32];
    uint8_t _len;
} _letter_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

uint8_t * req_rendererVM();
uint16_t * req_colorTrue();
void display_pixel(uint32_t y, uint32_t x, uint8_t color, uint8_t * vm);
void display_line(uint32_t y1, uint32_t x1, uint32_t y2, uint32_t x2, uint8_t color, uint8_t * vm);
void display_dotted_line(uint32_t y, uint32_t x, uint32_t lenth, uint8_t space, uint8_t dir, uint8_t color, uint8_t * vm);
void display_hollow_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint8_t color, uint8_t * vm);
void display_solid_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint8_t color, uint8_t * vm);
void display_bevel_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint32_t color, uint8_t chamfer, uint8_t * vm);
void display_fillet_rect(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint32_t color, uint8_t radius, uint8_t * vm);
void display_hollow_triangle(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint8_t color, uint8_t * vm);
void _display_circle(uint16_t y, uint16_t x, uint16_t r, uint16_t color, uint8_t * vm);
void display_circle(uint16_t y, uint16_t x, uint16_t r, uint16_t color, uint8_t * vm);
void display_sym(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, uint8_t _sym, uint8_t status, uint8_t * vm);
void display_battery(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint8_t fg, uint8_t bg, uint8_t power, uint8_t status, uint8_t * vm);
void display_barchart(uint32_t y, uint32_t x, uint8_t fg, uint8_t bg, int8_t _per, int32_t valmax, uint8_t * vm);
void display_dock(uint32_t y, uint32_t x, uint32_t width, uint32_t height, uint8_t fg, uint8_t bg, uint32_t rows, uint8_t row_gap, uint8_t linecur, uint8_t * vm);
void alerts_refer(uint32_t y, uint32_t x, uint32_t tft_width, uint8_t fg, uint8_t bg, uint8_t font_size, dev_alerts_t * alerts_p, uint8_t * vm);
void _letter_refer(_letter_t * _lettr_p, const uint8_t * str_p, uint8_t _offs);
const uint8_t * _letter_get_str(_letter_t * _lettr_p);
sym_desc_t sym_req_desc(uint8_t _sym);
void alerts_call(dev_alerts_t * alerts_p, const uint8_t * str_p, uint32_t _time);
void alerts_off(dev_alerts_t * alerts_p);
void alerts_offAll(dev_alerts_t _alerts[], uint8_t nr);
void alerts_tick_work(dev_alerts_t * alerts_p);
void alerts_tick_workAll(dev_alerts_t _alerts[], uint8_t nr);
bool alerts_get_state(dev_alerts_t * alerts_p);
bool alerts_is_active(dev_alerts_t _alerts[], uint8_t nr);

#endif
