
#ifndef __DRAW_H__
#define __DRAW_H__

#include <math.h>
#include <stdlib.h>

#include "stm32f4xx.h"
#include "ili9486.h"
#include "time.h"

extern int dbuffer[];
extern int data[];

extern void draw_line(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2, unsigned int color);
extern void display_rectangle(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color);
extern void diaplay_lattice();

extern void create_data(unsigned int number, int arrary[]);
extern void extract_data(unsigned int number, unsigned int step, int arrary[]);
extern void display_wave(unsigned int number, unsigned int step, unsigned int color, int arrary[]);
extern void display_figure();

#endif
