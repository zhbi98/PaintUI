/**
 * @file capture.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "capture.h"
#include "display.h"
#include "usart.h"

/*********************
 *      DEFINES
 *********************/

#define BMP_WRITE_DATA(a_byte) \
    usart_send_byte(USART1, a_byte)

/**
 * 0x42, 0x4D,             // BM
 * 0x36, 0x58, 0x02, 0x00, // (320*240*2+54) 颜色 RGB565 的文件长度
 * 0x00, 0x00, 0x00, 0x00, // 保留
 * 0x36, 0x00, 0x00, 0x00, // 从哪里开始是数据，实际是就是文件头大小 54
 * 0x28, 0x00, 0x00, 0x00, // 信息头需要的字节数 40, 从这里开始是信息头, 前面是文件头
 * 0x40, 0x01, 0x00, 0x00, // 宽度
 * 0x10, 0xFF, 0xFF, 0xFF, // 高度可以为负, 但是图像将会会颠倒上下颠倒
 * 0x01, 0x00,             // 颜色平面数，设为 1
 * 0x10, 0x00,             // 像素 1 4 8 16 24 32
 * 0x00, 0x00, 0x00, 0x00, // 压缩类型, 0为不压缩
 * 0x00, 0x58, 0x02, 0x00, // 图像大小, 前面设为不压缩时可以为0, 要填的话就是文件长度-文件头
 * 0x00, 0x00, 0x00, 0x00, // 水平分辨率 0
 * 0x00, 0x00, 0x00, 0x00, // 垂直分辨率 0
 * 0x00, 0x00, 0x00, 0x00, // 颜色索引数 0
 * 0x00, 0x00, 0x00, 0x00  // 对图像显示有重要影响的颜色索引数码, 设为0表示都重要
 */

const uint8_t bmp_desc[54] = {
    0x42, 0x4D, 
    0x36, 0x84, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x36, 0x00, 0x00, 0x00, 
    0x28, 0x00, 0x00, 0x00,
    0x40, 0x01, 0x00, 0x00,
    0x10, 0xFF, 0xFF, 0xFF, 
    0x01, 0x00, 
    0x18, 0x00, 
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x84, 
    0x30, 0x00, 0x88, 0x13, 
    0x00, 0x00, 0x88, 0x13, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void _bmpdesc(uint8_t * desc_p, uint32_t _len)
{
    for (uint8_t i = 0; i < _len; i++)
        BMP_WRITE_DATA(desc_p[i]);
}

/**
 *        R  G  B
 * RED 0xff,00,00
 * 
 * Sending order:(windows storage mode)
 * send blue -> send green -> send red
 * 
 * example:
 * for (uint32_t send = 0; send < 320 * 240; send++) {
 *     BMP_WRITE_DATA((0xff0000 & 0x0000ff) >> 0);
 *     BMP_WRITE_DATA((0xff0000 & 0x00ff00) >> 8);
 *     BMP_WRITE_DATA((0xff0000 & 0xff0000) >> 16);
 * }
 */
static void _bmpcolor(uint8_t * vm, uint32_t _len)
{
    uint32_t color;

    for (uint32_t y = 0; y < TFT_HEIGHT; y++) {
        for (uint32_t x = 0; x < TFT_WIDTH; x++) {
            color = color_data[vm[y * TFT_WIDTH + x]];
            /*RGB565 to RGB888*/
            BMP_WRITE_DATA((color & 0x1F) << 3);
            BMP_WRITE_DATA(((color >> 5) & 0x3F) << 2);
            BMP_WRITE_DATA((color >> 11) << 3);
        }
    }
}

void capture()
{
    uint16_t _len = sizeof(bmp_desc) / sizeof(uint8_t);
    uint32_t size = TFT_WIDTH * TFT_HEIGHT;
    uint8_t _disp_p = req_rendererVM();

    _bmpdesc(bmp_desc, _len);
    _bmpcolor(_disp_p, size);
}
