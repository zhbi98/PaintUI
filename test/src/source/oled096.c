
#include "oled096.h"

// oled 0.96 display video memory
// oled_vm[128 * 8] is 128 * 8(page)
unsigned char oled_vm[1024];

static void oled096_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(OLED096_D0_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OLED096_D1_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OLED096_RS_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OLED096_DC_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OLED096_CS_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = OLED096_D0_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(OLED096_D0_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = OLED096_D1_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_Init(OLED096_D1_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = OLED096_RS_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(OLED096_RS_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = OLED096_DC_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(OLED096_DC_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = OLED096_CS_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(OLED096_CS_GPIO, &gpio_init);
}

void oled096_send_bit(unsigned char a_bit)
{
    if (a_bit)
        GPIO_SetBits(OLED096_D1_GPIO, OLED096_D1_PIN);
    else
        GPIO_ResetBits(OLED096_D1_GPIO, OLED096_D1_PIN);
}

void oled096_send_byte(unsigned char a_byte)
{
    unsigned char write;

    GPIO_ResetBits(OLED096_CS_GPIO, OLED096_CS_PIN);
    for (write = 0; write < 8; write++) {
        GPIO_ResetBits(OLED096_D0_GPIO, OLED096_D0_PIN);
        oled096_send_bit((a_byte << write) & 0x80);
        sleep_us(1);
        GPIO_SetBits(OLED096_D0_GPIO, OLED096_D0_PIN);
    }
    GPIO_SetBits(OLED096_CS_GPIO, OLED096_CS_PIN);
}

void write_command(unsigned char command)
{
    GPIO_ResetBits(OLED096_DC_GPIO, OLED096_DC_PIN);
    oled096_send_byte(command);

}

void write_data(unsigned char dat_a)
{
    GPIO_SetBits(OLED096_DC_GPIO, OLED096_DC_PIN);
    oled096_send_byte(dat_a);
}

void clean(unsigned char dat_a)
{
    unsigned char x, page;

    for (page = 0; page < 8; page++) {
        write_command(0xb0 + page);
        write_command(0x02);
        write_command(0x10);
        for (x = 0; x < 128; x++)
            write_data(dat_a);
    }
}

void oled096_init()
{
    oled096_gpio_init();

    GPIO_ResetBits(OLED096_RS_GPIO, OLED096_RS_PIN);
    sleep_ms(1);
    GPIO_SetBits(OLED096_RS_GPIO, OLED096_RS_PIN);

    write_command(0xae);
    write_command(0xd5);
    write_command(0x80);
    write_command(0xa8);
    write_command(0x3f);
    write_command(0xd3);
    write_command(0x00);
    write_command(0x40);
    write_command(0xa1);
    write_command(0xc8);
    write_command(0xda);
    write_command(0x12);
    write_command(0x81);
    write_command(0xcf);
    write_command(0xd9);
    write_command(0xdb);
    write_command(0x30);
    write_command(0xa4);
    write_command(0xa6);
    write_command(0x8d);
    write_command(0x14);
    write_command(0xaf);
    clean(0x00);
    sleep_ms(1);
}

void display_on()
{
    write_command(0x8d);
    write_command(0x14);
    write_command(0xaf);
}

void display_off()
{
    write_command(0x8d);
    write_command(0x10);
    write_command(0xae);
}

void display_pixel(unsigned char y, unsigned char x, unsigned char color, unsigned char vm[])
{
    unsigned char page;
    unsigned char bit;

    page = y / 8;
    bit = y % 8;

    vm[page * 128 + x] |= ((color & 0x01) << bit);
}

void send_display_memory(unsigned char vm[])
{
    unsigned int x, page;
    unsigned int v = 0;

    for (page = 0; page < 8; page++) {
        write_command(0xb0 + page);
        write_command(0x02);
        write_command(0x10);
        for (x = 0; x < 128; x++) {
            write_data(vm[v]);
            v++;
        }
    }   
}

void display_position(unsigned char y, unsigned char x)
{
    unsigned char page;

    page = (y * 2) - 2;
    x = (x * 8) - 8;

    write_command(0xb0 + page);
    write_command(((x & 0xf0) >> 4) | 0x10);
    write_command((x & 0x0f) | 0x01);
}

void display_character(unsigned char y, unsigned char x, unsigned char character)
{       
    unsigned char column = 0;
    unsigned char page;

    character = character - ' ';

    display_position(y, x);

    for(column = 0; column < 8; column++) {
        write_data(f8x16[(character * 16) + column]);
    }

    page = (y * 2) - 1;
    x = (x * 8) - 8;

    write_command(0xb0 + page);
    write_command(((x & 0xf0) >> 4) | 0x10);
    write_command((x & 0x0f) | 0x01);

    for(column = 0; column < 8; column++) {                                                                                                                                                 
        write_data(f8x16[(character * 16) + column + 8]);
    }
}

void display_string(unsigned char y, unsigned char x, const unsigned char * string)
{
    unsigned char bits = 0;

    while (string[bits] != '\0') {
        display_character(y, x, string[bits]);
        
        bits++;
        x++;
    }
}

void display_value(unsigned char y, unsigned char x, unsigned char *format, ...)
{
    unsigned char value[16];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    display_string(y, x, value);
}

void display_bevel_rectangle(unsigned char y, unsigned char x, unsigned char width, unsigned char height, unsigned char radian, unsigned char vm[])
{
    unsigned char i, j;

    for (i = radian; i > 0; i--) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, black, vm);
        }
        y++;
    }
    for (i = 0; i < (height - radian * 2); i++) {
        for (j = 0; j < width; j++) {
            display_pixel(y, x + j, black, vm);
        }
        y++;
    }
    for (i = 0; i < radian + 1; i++) {
        for (j = 0; j < (width - i * 2); j++) {
            display_pixel(y, x + i + j, black, vm);
        }
        y++;
    }
}
