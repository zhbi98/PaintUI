
#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__

#include "usart.h"
#include "display.h"

#define BMP_WRITE_DATA(a_byte) usart_send_byte(CURRENT_USART, a_byte)

extern const uint8_t bmp_desc[];

extern void bmp_write_desc(uint8_t * desc, uint32_t length);
extern void bmp_write_color(uint8_t * vm, uint32_t length);
extern void image_shot();

#endif
