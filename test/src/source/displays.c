
#include "displays.h"

void display_pixels(unsigned int y, unsigned int x, unsigned int color, unsigned char *vm)
{
    vm[y * SCREEN_WIDTH + x] = color;
}

void display_lines(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2, unsigned int color, unsigned char *vm)
{
    unsigned int i;
    int xerr = 0, yerr = 0, dx, dy, distance;
    int increment_x, increment_y, row, col;

    dx = x2 - x1;
    dy = y2 - y1;

    row = y1;
    col = x1;

    if (dx > 0) {
        increment_x = 1;
    } else if (dx == 0) {
        increment_x = 0;
    } else {
        increment_x = -1;
        dx = - dx;
    }

    if (dy > 0) {
        increment_y = 1;
    } else if (dy == 0) {
        increment_y = 0;
    } else {
        increment_y = - 1;
        dy = -dy;
    }

    if (dx > dy)
        distance = dx;
    else
        distance = dy;

    for (i = 0; i <= distance + 1; i++) {
        display_pixels(row, col, color, vm);
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

void display_dotline(unsigned int y, unsigned int x, unsigned int lenth, unsigned char step, unsigned char direct, unsigned int color, unsigned char *vm)
{
    unsigned int l;

    if (!direct) {
        for (l = 0; l < lenth; l = l + step) {
            display_pixels(y, x + l, color, vm);
        }
    } else {
        for (l = 0; l < lenth; l = l + step) {
            display_pixels(y + l, x, color, vm);
        }
    }
}

void display_rrect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char *vm)
{
    width -= 1;
    height -= 1;
    
    display_lines(y, x, y, x + width, color, vm);
    display_lines(y, x + width, y + height, x + width, color, vm);
    display_lines(y + height, x + width, y + height, x, color, vm);
    display_lines(y, x,  y + height, x, color, vm);
}

void display_srect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char *vm)
{
    unsigned int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            display_pixels(y + i, x + j, color, vm);
        }
    }
}

void display_bevel_rect(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char radian, unsigned char *vm)
{
    unsigned int i, j;

    for (i = radian; i > 0; i--) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixels(y, x + i + j, color, vm);
        }
        y++;
    }
    for (i = 0; i < (height - radian * 2); i++) {
        for (j = 0; j < width; j++) {
            display_pixels(y, x + j, color, vm);
        }
        y++;
    }
    for (i = 0; i < radian + 1; i++) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixels(y, x + i + j, color, vm);
        }
        y++;
    }
}

void display_rtriangle(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color, unsigned char *vm)
{
    display_lines(y + height, x, y, x + width / 2, color, vm);
    display_lines(y, x + width / 2, y + height, x + width, color, vm);
    display_lines(y + height, x + width, y + height, x, color, vm);
}

void display_characters(unsigned int y, unsigned int x, unsigned int color, unsigned char character, unsigned char *font, unsigned char *vm)
{
    unsigned char font_h;
    unsigned char font_w;
    unsigned char font_c[CHARACTER_HEIGH];

    x = (x * 8) - 8 + 1;
    y = (y * 16) - 16 + 1;

    character = character - ' ';

    for (font_h = 0; font_h < CHARACTER_HEIGH; font_h++)
        font_c[font_h] = font[CHARACTER_HEIGH * character + font_h];

    for (font_h = 0; font_h < CHARACTER_HEIGH; font_h++) {
        for (font_w = 0; font_w < CHARACTER_WIDTH; font_w++) {
            if (font_c[font_h] & (0x80 >> font_w)) {
                display_pixels(y + font_h, x + font_w, color, vm);
            }
        }
    }
}

void display_strings(unsigned int y, unsigned int x, unsigned int color, unsigned char *string, unsigned char *font, unsigned char *vm)
{
    unsigned char bits = 0;

    while (string[bits] != '\0') {
        display_characters(y, x, color, string[bits], font, vm);

        sleep_ms(10);
        bits++;
        x++;
    }
}

void display_values(unsigned int y, unsigned int x, unsigned int color, unsigned char *font, unsigned char *vm, unsigned char *format, ...)
{
    unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_strings(y, x, color, value, font, vm);
}
