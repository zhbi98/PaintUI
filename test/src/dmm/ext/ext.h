/**
 * @file ext.h
 *
 */

#ifndef __EXT_H__
#define __EXT_H__

/**
 * When you display a string, you can specify another 
 * Color for a field, such as Hello, # 0xFF00 Red # Color
 */
void textarea_string(unsigned int y, unsigned int x, unsigned int fg, unsigned int bg, 
    unsigned char font_size, unsigned char * string, unsigned char * vm);

#endif
