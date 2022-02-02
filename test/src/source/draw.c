
#include "draw.h"

void draw_line(unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2, unsigned int color)
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
        display_pixel(row, col, color);
        display_pixel(row + 1, col + 1, color);
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

void display_rectangle(unsigned int y, unsigned int x, unsigned int width, unsigned int height, unsigned int color)
{
    draw_line(y, x, y, x + width, color);
    draw_line(y, x + width, y + height, x + width, color);
    draw_line(y + height, x + width, y + height, x, color);
    draw_line(y, x,  y + height, x, color);
}

void diaplay_lattice()
{
    unsigned int x, y;

    // draw axis
    //     y
    //     |
    // ----+---> x
    //     |
    for (x = 1; x < 480; x++) {
        display_pixel(160, x, orange);
    }
    for (y = 1; y < 320; y++) {
        display_pixel(y, 240, orange);
    }

    // draw lattice line
    for (y = 128; y >   0; y -= 32) {
        for (x = 1; x < 480; x++) {
            display_pixel(y, x, dimgray);
        }
    }
    // draw lattice line
    for (y = 192; y < 320; y += 32) {
        for (x = 1; x < 480; x++) {
            display_pixel(y, x, dimgray);
        }
    }

    // draw lattice column
    for (x = 208; x > 16; x -= 32) {
        for (y = 1; y < 320; y++) {
            display_pixel(y, x, dimgray);
        }
    }
    // under 32 draw one column
    for (y = 1; y < 320; y++) {
        display_pixel(y, 16, dimgray);
    }
    // draw lattice column
    for (x = 272; x < 480; x += 32) {
        for (y = 1; y < 320; y++) {
            display_pixel(y, x, dimgray);
        }
    }

    // draw frame
    display_rectangle(1, 1, 479, 319, dimgray);
}

void create_data(unsigned int number, int arrary[])
{
    unsigned int j = 0;

    // Generate and fill test data for the buffer
    for (int i = 0; i < number; i++) {
        // arrary[i] = sin(j * 3.14 / 180) * 50;
        arrary[i] = cos(j * 3.14 / 180) * 50 + sin(j * 3.14 / 180) * (rand() % 6);
        // arrary[i] = (adc_read() - 2048) * 3.2 / 4096 * 100;
        
        if (j > 360)
            j = 0;
        
        j++;
    }
}

void extract_data(unsigned int number, unsigned int step, int arrary[])
{
    unsigned int j = 0;

    // Data extraction,number points are 
    // evenly extracted from 1920 points
    for (int i = 0; i < number; i++) {
        arrary[i] = dbuffer[j];

        // Set the number of points
        j += step;
    }
}

void display_wave(unsigned int number, unsigned int step, unsigned int color, int arrary[])
{
    unsigned int j = 0;
 
    number /= step; 

    for (int i = 1; i < number; i++) {
        // display_pixel(160 - arrary[i], j, color);
        draw_line(160 - arrary[i], j, 160 - arrary[i + 1], j + step, color);
        // draw_line(160 - arrary[i] + 1, j, 160 - arrary[i + 1] + 1, j + 1, color);
        
        // Set the dot pitch to adjust the width of the waveform 
        // [j += 2, j += 3 ... j += n] [Expand the waveform]
        j += step;
    }    
}

// No data extraction
// as data source with
// three screen data,
// 1920 storage depth
// degrees
int dbuffer[1024];

// Data buffer
// after sampling
int data[480];

void display_figure()
{
    diaplay_lattice();

    // clear screen
    display_wave(479, 4, black, data);

    extract_data(480, 2, data);

    display_wave(479, 4, white, data);

    create_data(1024, dbuffer);
}
