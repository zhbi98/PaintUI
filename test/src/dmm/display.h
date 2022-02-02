
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "display_string.h"

#define TFT_WIDTH        320U
#define TFT_HEIGHT       240U
#define DISPLAY_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT)

struct logo_data_t {
    unsigned char  width;
    unsigned char height;

    const unsigned char * data;
};

enum logo_name {
	BLUETOOTH,
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

enum color_name {
	BLACK      = 0,
	WHITE      = 1,
	RED        = 2,
	GRAY       = 3,
	DARK_GREEN = 4,
	GREEN      = 5,
	DARK_BLUE  = 6,
	COLOR_MAX  = 7,
};

struct message_tips_t {
    const unsigned int message_width;
    const unsigned int message_height;
    unsigned char active;
    unsigned int reside_time;
    const unsigned char content_num;
};

extern const unsigned int color_data[];

extern const unsigned char bluetooth[];
extern const unsigned char poweroff_timer[];
extern const unsigned char lighting[];
extern const unsigned char lo[];
extern const unsigned char loz[];
extern const unsigned char ruler_overflow[];
extern const unsigned char ac_desc[];
extern const unsigned char dc_desc[];
extern const unsigned char ac_dc_desc[];
extern const struct logo_data_t dmm_logo[];

extern unsigned char display_buf[];

extern struct message_tips_t message_tips[];

extern unsigned char * tft_buf();
extern void display_pixel(unsigned int y, unsigned int x, unsigned char color, unsigned char * vm);
extern void display_line(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2, unsigned char color, unsigned char * vm);

extern void display_dotted_line(unsigned int y, unsigned int x, unsigned int lenth, unsigned char step, unsigned char direction, unsigned char color, unsigned char * vm);
extern void display_hollow_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char color, unsigned char * vm);
extern void display_solid_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char color, unsigned char * vm);
extern void display_bevel_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char chamfer, unsigned char * vm);
extern void display_fillet_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char radius, unsigned char * vm);
extern void display_hollow_triangle(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char color, unsigned char * vm);
extern void display_bookmark(int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char radian, unsigned char * vm);

extern void display_status_logo(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, unsigned char logo_name, unsigned char status, unsigned char * vm);

extern void display_battery(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char power, unsigned char status, unsigned char * vm);
extern void display_recording_mark(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char status, unsigned char * vm);
extern void display_maxmin_mark(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char status, unsigned char * vm);
extern void display_hold_mark(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned char status, unsigned char * vm);

extern void display_ruler(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, unsigned char progress, unsigned char function, unsigned long range, unsigned char negative_value, unsigned char * vm);
extern void display_ruler_percent_mode(unsigned int y, unsigned int x, unsigned char fg, unsigned char bg, char percentage, int value_max, unsigned char * vm);

extern void display_setting_dock(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned char fg, unsigned char bg, unsigned int rows, unsigned char row_gap, unsigned char select_num, unsigned char * vm);

extern void active_tips(struct message_tips_t * tips, unsigned int reside_time);
extern void inactive_tips(struct message_tips_t * tips);
extern void inactive_all_tips(struct message_tips_t tips[]);
extern void tips_timing(struct message_tips_t * tips);
extern void tips_all_timing(struct message_tips_t tips[]);
extern unsigned int second_convert_ticks(unsigned int second);
extern void display_tips(unsigned int y, unsigned int x, unsigned int tft_width, unsigned char fg, unsigned char bg, unsigned char font_size, struct message_tips_t * tips, unsigned char * vm);

extern struct logo_data_t read_logo_data(unsigned char logo_name);

#endif
