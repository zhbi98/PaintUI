
#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__

#include "usart.h"
#include "display.h"

#define BMP_WRITE_DATA(a_byte) usart_send_byte(CURRENT_USART, a_byte)

extern const unsigned char bmp_desc[];

extern void bmp_write_desc(unsigned char * desc, unsigned int length);
extern void bmp_write_color(unsigned char * vm, unsigned int length);
extern void image_shot();

#endif
