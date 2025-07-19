
#include "ili9486.h"

static void ili9486_fsmc_init()
{
    FSMC_NORSRAMInitTypeDef fsmc_norsram_init;
    FSMC_NORSRAMTimingInitTypeDef fsmc_norsramtiming_init;

    RCC_AHB3PeriphClockCmd(FSMC_CLOCK, ENABLE);

    fsmc_norsramtiming_init.FSMC_AddressSetupTime = 0x04;
    fsmc_norsramtiming_init.FSMC_DataSetupTime = 0x0b;
    fsmc_norsramtiming_init.FSMC_AccessMode = FSMC_AccessMode_B;
    fsmc_norsramtiming_init.FSMC_AddressHoldTime = 0;
    fsmc_norsramtiming_init.FSMC_BusTurnAroundDuration = 0;
    fsmc_norsramtiming_init.FSMC_CLKDivision = 0;
    fsmc_norsramtiming_init.FSMC_DataLatency = 0;

    fsmc_norsram_init.FSMC_Bank = FSMC_BANK1_NORSRAM;
    fsmc_norsram_init.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    fsmc_norsram_init.FSMC_MemoryType = FSMC_MemoryType_NOR;
    fsmc_norsram_init.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    fsmc_norsram_init.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    fsmc_norsram_init.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    fsmc_norsram_init.FSMC_WrapMode = FSMC_WrapMode_Disable;
    fsmc_norsram_init.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    fsmc_norsram_init.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    fsmc_norsram_init.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    fsmc_norsram_init.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    fsmc_norsram_init.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    fsmc_norsram_init.FSMC_ReadWriteTimingStruct = &fsmc_norsramtiming_init;
    fsmc_norsram_init.FSMC_WriteTimingStruct = &fsmc_norsramtiming_init;

    FSMC_NORSRAMInit(&fsmc_norsram_init);
    FSMC_NORSRAMCmd(FSMC_BANK1_NORSRAM, ENABLE);

    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(ILI9486_RS_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_RD_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_WR_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_CS_CLOCK, ENABLE);

    RCC_AHB1PeriphClockCmd(ILI9486_RST_CLOCK, ENABLE);
    // RCC_AHB1PeriphClockCmd(ILI9486_BL_CLOCK, ENABLE);

    RCC_AHB1PeriphClockCmd(ILI9486_D0_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D1_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D2_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D3_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D4_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D5_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D6_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D7_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D8_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D9_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D10_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D11_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D12_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D13_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D14_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9486_D15_CLOCK, ENABLE);

    GPIO_PinAFConfig(ILI9486_RS_GPIO, ILI9486_RS_SRC, ILI9486_RS_AF);
    GPIO_PinAFConfig(ILI9486_RD_GPIO, ILI9486_RD_SRC, ILI9486_RD_AF);
    GPIO_PinAFConfig(ILI9486_WR_GPIO, ILI9486_WR_SRC, ILI9486_WR_AF);
    GPIO_PinAFConfig(ILI9486_CS_GPIO, ILI9486_CS_SRC, ILI9486_CS_AF);

    GPIO_PinAFConfig(ILI9486_D0_GPIO, ILI9486_D0_SRC, ILI9486_D0_AF);
    GPIO_PinAFConfig(ILI9486_D1_GPIO, ILI9486_D1_SRC, ILI9486_D1_AF);
    GPIO_PinAFConfig(ILI9486_D2_GPIO, ILI9486_D2_SRC, ILI9486_D2_AF);
    GPIO_PinAFConfig(ILI9486_D3_GPIO, ILI9486_D3_SRC, ILI9486_D3_AF);
    GPIO_PinAFConfig(ILI9486_D4_GPIO, ILI9486_D4_SRC, ILI9486_D4_AF);
    GPIO_PinAFConfig(ILI9486_D5_GPIO, ILI9486_D5_SRC, ILI9486_D5_AF);
    GPIO_PinAFConfig(ILI9486_D6_GPIO, ILI9486_D6_SRC, ILI9486_D6_AF);
    GPIO_PinAFConfig(ILI9486_D7_GPIO, ILI9486_D7_SRC, ILI9486_D7_AF);
    GPIO_PinAFConfig(ILI9486_D8_GPIO, ILI9486_D8_SRC, ILI9486_D8_AF);
    GPIO_PinAFConfig(ILI9486_D9_GPIO, ILI9486_D9_SRC, ILI9486_D9_AF);
    GPIO_PinAFConfig(ILI9486_D10_GPIO, ILI9486_D10_SRC, ILI9486_D10_AF);
    GPIO_PinAFConfig(ILI9486_D11_GPIO, ILI9486_D11_SRC, ILI9486_D11_AF);
    GPIO_PinAFConfig(ILI9486_D12_GPIO, ILI9486_D12_SRC, ILI9486_D12_AF);
    GPIO_PinAFConfig(ILI9486_D13_GPIO, ILI9486_D13_SRC, ILI9486_D13_AF);
    GPIO_PinAFConfig(ILI9486_D14_GPIO, ILI9486_D14_SRC, ILI9486_D14_AF);
    GPIO_PinAFConfig(ILI9486_D15_GPIO, ILI9486_D15_SRC, ILI9486_D15_AF);

    gpio_init.GPIO_Pin   = ILI9486_RS_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_RS_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_RD_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_RD_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_WR_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_WR_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_CS_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_CS_GPIO, &gpio_init);


    gpio_init.GPIO_Pin   = ILI9486_RST_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ILI9486_RST_GPIO, &gpio_init);

    // gpio_init.GPIO_Pin   = ILI9486_BL_PIN;
    // gpio_init.GPIO_OType = GPIO_OType_PP;
    // gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    // gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(ILI9486_BL_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D0_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D0_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D1_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D1_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D2_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D2_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D3_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D3_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D4_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D4_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D5_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D5_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D6_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D6_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D7_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D7_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D8_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D8_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D9_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D9_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D10_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D10_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D11_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D11_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D12_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D12_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D13_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D13_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D14_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D14_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9486_D15_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9486_D15_GPIO, &gpio_init);
}

void ili9486_write_command(uint16_t command)
{
    GPIO_ResetBits(ILI9486_RS_GPIO, ILI9486_RS_PIN);

    * (__IO uint16_t *)(ILI9486_WRITE_COMMAND) = command;
}

void ili9486_write_data(uint16_t dat_a)
{
    GPIO_SetBits(ILI9486_RS_GPIO, ILI9486_RS_PIN);

    * (__IO uint16_t *)(ILI9486_WRITE_DATA) = dat_a;
}

void ili9486_write_register(uint32_t register_address, uint32_t register_value)
{
    ili9486_write_command(register_address);
    ili9486_write_data(register_value);
}

void ili9486_reset()
{
    GPIO_SetBits(ILI9486_RST_GPIO, ILI9486_RST_PIN);
    sleep_ms(50);
    GPIO_ResetBits(ILI9486_RST_GPIO, ILI9486_RST_PIN);      
    sleep_ms(50);
    GPIO_SetBits(ILI9486_RST_GPIO, ILI9486_RST_PIN);
    sleep_ms(50);
}

void ili9486_direction(uint8_t direction)
{
    ili9486_write_command(0x36);

    switch (direction) {
        // +----- x 
        // |
        // |
        // y              horizontal
        case 0 : ili9486_write_data(0xa8); break;
        // y -----+
        //        |
        //        |
        //        x       vertical
        case 1 : ili9486_write_data(0x08); break;
        //        y
        //        |
        //        |
        // x -----+ 0x08  horizontal
        case 2 : ili9486_write_data(0x68); break;
        // x
        // |
        // |
        // +----- y       vertical
        case 3 : ili9486_write_data(0xc8); break;
    }
}

void ili9486_init()
{
    ili9486_fsmc_init();
    sleep_ms(500);
    ili9486_reset();

    ili9486_write_command(0xb0);
    ili9486_write_data(0x00);
  
    ili9486_write_command(0x3a);
    ili9486_write_data(0x55);

    ili9486_write_command(0xe0);
    ili9486_write_data(0x0f);
    ili9486_write_data(0x1f);
    ili9486_write_data(0x1c);
    ili9486_write_data(0x0c);
    ili9486_write_data(0x0f);
    ili9486_write_data(0x08);
    ili9486_write_data(0x48);
    ili9486_write_data(0x98);
    ili9486_write_data(0x37);
    ili9486_write_data(0x0a);
    ili9486_write_data(0x13);
    ili9486_write_data(0x04);
    ili9486_write_data(0x11);
    ili9486_write_data(0x0d);
    ili9486_write_data(0x00);

    ili9486_write_command(0xe1);
    ili9486_write_data(0x0f);
    ili9486_write_data(0x32);
    ili9486_write_data(0x2e);
    ili9486_write_data(0x0b);
    ili9486_write_data(0x0d);
    ili9486_write_data(0x05);
    ili9486_write_data(0x47);
    ili9486_write_data(0x75);
    ili9486_write_data(0x37);
    ili9486_write_data(0x06);
    ili9486_write_data(0x10);
    ili9486_write_data(0x03);
    ili9486_write_data(0x24);
    ili9486_write_data(0x20);
    ili9486_write_data(0x00);

    ili9486_write_command(0xe2);
    ili9486_write_data(0x0f);
    ili9486_write_data(0x32);
    ili9486_write_data(0x2e);
    ili9486_write_data(0x0b);
    ili9486_write_data(0x0d);
    ili9486_write_data(0x05);
    ili9486_write_data(0x47);
    ili9486_write_data(0x75);
    ili9486_write_data(0x37);
    ili9486_write_data(0x06);
    ili9486_write_data(0x10);
    ili9486_write_data(0x03);
    ili9486_write_data(0x24);
    ili9486_write_data(0x20);
    ili9486_write_data(0x00);
    // direction seting
    // ili9486_write_command(0x36);
    // ili9486_write_data(0xa8);
    if (HORIZONTAL)
        ili9486_direction(0);
    else
        ili9486_direction(1);

    ili9486_write_command(0x38);

    ili9486_write_command(0xb1);
    ili9486_write_data(0xb0);
    ili9486_write_data(0x11);

    ili9486_write_command(0xc2);
    ili9486_write_data(0x55); 

    ili9486_write_command(0xb4);
    ili9486_write_data(0x02);

    ili9486_write_command(0xb6);
    ili9486_write_data(0x02);
    ili9486_write_data(0x22);
    ili9486_write_data(0x3b);

    ili9486_write_command(0x11);
    ili9486_write_command(0x29);

    ili9486_clear(white);
}

void display_position(uint32_t y, uint32_t x)
{
    uint8_t seting_x = 0x2a;
    uint8_t seting_y = 0x2b;

    y = y - 1;
    x = x - 1;

    ili9486_write_command(seting_x);
    ili9486_write_data(x >> 8);
    ili9486_write_data(0x00ff & x);
    ili9486_write_data((x + 1) >> 8);
    ili9486_write_data((x + 1));
    
    ili9486_write_command(seting_y);
    ili9486_write_data(y >> 8);
    ili9486_write_data(0x00ff & y);
    ili9486_write_data((y + 1) >> 8);
    ili9486_write_data((y + 1));
}

void display_region(uint32_t y, uint32_t x, uint32_t width, uint32_t height)
{
    uint8_t seting_x = 0x2a;
    uint8_t seting_y = 0x2b;

    y = y - 1;
    x = x - 1;

    ili9486_write_command(seting_x);
    ili9486_write_data(x >> 8);
    ili9486_write_data(0x00ff & x);
    ili9486_write_data((x + width - 1) >> 8);
    ili9486_write_data((x + width - 1));

    ili9486_write_command(seting_y);
    ili9486_write_data(y >> 8);
    ili9486_write_data(0x00ff & y);
    ili9486_write_data((y + height - 1) >> 8);
    ili9486_write_data((y + height - 1));
}
