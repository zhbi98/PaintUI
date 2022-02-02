
#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__

#include <stdio.h>
#include <stdarg.h>

#define SCREEN_WIDTH 320 
#define CHARACTER_WIDTH  8
#define CHARACTER_HEIGH 16

extern void display_pixels(unsigned int y, unsigned int x, unsigned int color, unsigned char *vm);
extern void display_lines(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2, unsigned int color, unsigned char *vm);
extern void display_dotline(unsigned int y, unsigned int x, unsigned int lenth, unsigned char step, unsigned char direct, unsigned int color, unsigned char *vm);
extern void display_rrect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char *vm);
extern void display_srect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char *vm);
extern void display_bevel_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char radian, unsigned char *vm);
extern void display_rtriangle(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char *vm);
extern void display_characters(unsigned int y, unsigned int x, unsigned int color, unsigned char character, unsigned char *font, unsigned char *vm);
extern void display_strings(unsigned int y, unsigned int x, unsigned int color, unsigned char *string, unsigned char *font, unsigned char *vm);
extern void display_values(unsigned int y, unsigned int x, unsigned int color, unsigned char *font, unsigned char *vm, unsigned char *format, ...);

#endif
