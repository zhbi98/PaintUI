
#include "key.h"

void key_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(F1_KEY_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(F2_KEY_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(F3_KEY_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(F4_KEY_CLOCK, ENABLE);

    gpio_init.GPIO_Pin = F1_KEY_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(F1_KEY_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = F2_KEY_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(F2_KEY_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = F3_KEY_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(F3_KEY_GPIO, &gpio_init);

    gpio_init.GPIO_Pin = F4_KEY_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(F4_KEY_GPIO, &gpio_init);
}

struct key_event_t key_evt = {
    .press_long = false,
    .press_duration = 400,
    .active_time = 29,
};

unsigned char key_drive_code()
{
    unsigned char t = 0x00;

    t = (t << 1) | !F1_KEY_STATUS();
    t = (t << 1) |  F2_KEY_STATUS();
    t = (t << 1) |  F3_KEY_STATUS();
    t = (t << 1) |  F4_KEY_STATUS();
    t = (t << 1) | (0x01);
    t = (t << 1) | (0x01);
    t = (t << 1) | (0x01);
    t = (t << 1) | (0x01);

    return t;
}

void key_event_ticks()
{
    if (key_evt.press_duration != 0) {
        key_evt.press_duration--;
    }
    if (key_evt.active_time != 0) {
        key_evt.active_time--;
    }
}

unsigned char read_key_event()
{
    /**
     * [1110, 1111], <k1, k2, k3, k4, 1, 1, 1, 1>
     * Key follow the code:
     * Key <1> <0x7f>
     * Key <2> <0xbf>
     * Key <3> <0xdf>
     * Key <4> <0xef>
     */

    unsigned char drive_code = 0;
    unsigned char k = 0;
    static unsigned char plast = RELEASE;

    drive_code = key_drive_code();

    switch (drive_code) {
        case 0x7f:
            k = F1_KEY_EVT;
            // key pressed to display the effect
            if (widget[F1_MENUBAR_AREA].show)
                menubar_pressed(F1_KEY_EVT);
            break;
        case 0xbf:
            k = F2_KEY_EVT;
            // key pressed to display the effect
            if (widget[F2_MENUBAR_AREA].show)
                menubar_pressed(F2_KEY_EVT);
            break;
        case 0xdf:
            k = F3_KEY_EVT;
            // key pressed to display the effect
            if (widget[F3_MENUBAR_AREA].show)
                menubar_pressed(F3_KEY_EVT);
            break;
        case 0xef:
            k = F4_KEY_EVT;
            // key pressed to display the effect
            if (widget[F4_MENUBAR_AREA].show)
                menubar_pressed(F4_KEY_EVT);
            break;
        case 0x00:
            k = PREV_KEY_EVT;
            // key pressed to display the effect
            if (widget[PREV_MENUBAR_AREA].show)
                menubar_pressed(PREV_KEY_EVT);
            break;
        case 0x01:
            k = NEXT_KEY_EVT;
            // key pressed to display the effect
            if (widget[NEXT_MENUBAR_AREA].show)
                menubar_pressed(NEXT_KEY_EVT);
            break;
        default:
            k = RELEASE;
            break;
    }

    if (k == RELEASE) {
        key_evt.press_duration = 400;
    }

    // key 5 unsupport long press auto trigger active  
    if ((key_evt.press_duration <= 0)/* && (k != KEY5_EVT)*/) {
        key_evt.press_long = true;
    } else {
        key_evt.press_long = false;
    }

    key_event_ticks();

    if (key_evt.press_long == true) {
        if (key_evt.active_time <= 0) {
            key_evt.active_time = 29;
            return k;
        } else {
            return RELEASE;
        }
    }

    // Pressed event
    // if ((k != RELEASE) && (plast == RELEASE)) {
    //     plast = k;
    //     return k;
    // } else {
    //     plast = k;
    //     return RELEASE;
    // }

    // Released event 
    if ((k == RELEASE) && (plast != RELEASE)) {
        drive_code = plast;
        plast = RELEASE;
        return drive_code;
    } else {
        plast = k;
        return RELEASE;
    }
}
