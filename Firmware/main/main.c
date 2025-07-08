
#include "stm32f4xx.h"

#include "key.h"
#include "time.h"
#include "display.h"

#include "key_doing.h"
#include "display_controller.h"

#include "setting.h"
#include "usart.h"

void hw_module_init()
{
    ili9341_init();
    usart_init();
    key_gpio_init();
}

void sw_module_init()
{
    _Area_init();
    act_bar_set_func(&_dmm_actbar, 
        DMM_VOLTAGE_V);
    tft_clear(BLACK);
    regu_LR_move(0);
}

int main()
{
    hw_module_init();
    sw_module_init();

    for (;;) {
        key_event_doing();
        display_flush(req_rendererVM());
        tft_flush(req_rendererVM());
    }
}
