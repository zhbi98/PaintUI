/**
 * @file ext.h
 *
 */

#ifndef __EXT_H__
#define __EXT_H__

/*********************
 *      INCLUDES
 *********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * When you display a string, you can specify another 
 * Color for a field, such as Hello, # 0xFF00 Red # Color
 */
void textarea_string(uint32_t y, uint32_t x, uint32_t fg, uint32_t bg, 
    uint8_t font_size, uint8_t * string, uint8_t * vm);

#endif
