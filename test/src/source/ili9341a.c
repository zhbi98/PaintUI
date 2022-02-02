
#include "ili9341a.h"

static void ili9341_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(ILI9341_RS_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_RD_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_WR_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_CS_CLOCK, ENABLE);

    RCC_AHB1PeriphClockCmd(ILI9341_RST_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_BL_CLOCK, ENABLE);

    RCC_AHB1PeriphClockCmd(ILI9341_D0_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D1_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D2_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D3_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D4_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D5_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D6_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D7_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D8_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D9_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D10_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D11_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D12_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D13_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D14_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(ILI9341_D15_CLOCK, ENABLE);

    GPIO_PinAFConfig(ILI9341_RS_GPIO, ILI9341_RS_SRC, ILI9341_RS_AF);
    GPIO_PinAFConfig(ILI9341_RD_GPIO, ILI9341_RD_SRC, ILI9341_RD_AF);
    GPIO_PinAFConfig(ILI9341_WR_GPIO, ILI9341_WR_SRC, ILI9341_WR_AF);
    GPIO_PinAFConfig(ILI9341_CS_GPIO, ILI9341_CS_SRC, ILI9341_CS_AF);

    GPIO_PinAFConfig(ILI9341_D0_GPIO, ILI9341_D0_SRC, ILI9341_D0_AF);
    GPIO_PinAFConfig(ILI9341_D1_GPIO, ILI9341_D1_SRC, ILI9341_D1_AF);
    GPIO_PinAFConfig(ILI9341_D2_GPIO, ILI9341_D2_SRC, ILI9341_D2_AF);
    GPIO_PinAFConfig(ILI9341_D3_GPIO, ILI9341_D3_SRC, ILI9341_D3_AF);
    GPIO_PinAFConfig(ILI9341_D4_GPIO, ILI9341_D4_SRC, ILI9341_D4_AF);
    GPIO_PinAFConfig(ILI9341_D5_GPIO, ILI9341_D5_SRC, ILI9341_D5_AF);
    GPIO_PinAFConfig(ILI9341_D6_GPIO, ILI9341_D6_SRC, ILI9341_D6_AF);
    GPIO_PinAFConfig(ILI9341_D7_GPIO, ILI9341_D7_SRC, ILI9341_D7_AF);
    GPIO_PinAFConfig(ILI9341_D8_GPIO, ILI9341_D8_SRC, ILI9341_D8_AF);
    GPIO_PinAFConfig(ILI9341_D9_GPIO, ILI9341_D9_SRC, ILI9341_D9_AF);
    GPIO_PinAFConfig(ILI9341_D10_GPIO, ILI9341_D10_SRC, ILI9341_D10_AF);
    GPIO_PinAFConfig(ILI9341_D11_GPIO, ILI9341_D11_SRC, ILI9341_D11_AF);
    GPIO_PinAFConfig(ILI9341_D12_GPIO, ILI9341_D12_SRC, ILI9341_D12_AF);
    GPIO_PinAFConfig(ILI9341_D13_GPIO, ILI9341_D13_SRC, ILI9341_D13_AF);
    GPIO_PinAFConfig(ILI9341_D14_GPIO, ILI9341_D14_SRC, ILI9341_D14_AF);
    GPIO_PinAFConfig(ILI9341_D15_GPIO, ILI9341_D15_SRC, ILI9341_D15_AF);

    gpio_init.GPIO_Pin   = ILI9341_RS_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_RS_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_RD_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_RD_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_WR_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_WR_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_CS_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_CS_GPIO, &gpio_init);


    gpio_init.GPIO_Pin   = ILI9341_RST_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ILI9341_RST_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_BL_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ILI9341_BL_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D0_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D0_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D1_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D1_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D2_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D2_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D3_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D3_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D4_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D4_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D5_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D5_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D6_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D6_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D7_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D7_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D8_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D8_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D9_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D9_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D10_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D10_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D11_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D11_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D12_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D12_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D13_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D13_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D14_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D14_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = ILI9341_D15_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(ILI9341_D15_GPIO, &gpio_init);
}

static void ili9341_fsmc_init()
{
    FSMC_NORSRAMInitTypeDef  fsmc_norsram_init;
    FSMC_NORSRAMTimingInitTypeDef  fsmc_norsramtiming_init;     
    
    RCC_AHB3PeriphClockCmd(FSMC_CLOCK, ENABLE);

    fsmc_norsramtiming_init.FSMC_AddressSetupTime      = 0x09;
    fsmc_norsramtiming_init.FSMC_DataSetupTime         = 0x08;
    fsmc_norsramtiming_init.FSMC_AccessMode            = FSMC_AccessMode_A; 
    fsmc_norsramtiming_init.FSMC_AddressHoldTime       = 0x00;
    fsmc_norsramtiming_init.FSMC_BusTurnAroundDuration = 0x00;
    fsmc_norsramtiming_init.FSMC_CLKDivision           = 0x00;
    fsmc_norsramtiming_init.FSMC_DataLatency           = 0x00;  

    fsmc_norsram_init.FSMC_Bank                  = FSMC_BANK1_NORSRAM;
    fsmc_norsram_init.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
    fsmc_norsram_init.FSMC_MemoryType            = FSMC_MemoryType_SRAM;
    fsmc_norsram_init.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
    fsmc_norsram_init.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
    fsmc_norsram_init.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
    fsmc_norsram_init.FSMC_WrapMode              = FSMC_WrapMode_Disable;
    fsmc_norsram_init.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;
    fsmc_norsram_init.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
    fsmc_norsram_init.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
    fsmc_norsram_init.FSMC_ExtendedMode          = FSMC_ExtendedMode_Disable;
    fsmc_norsram_init.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
    fsmc_norsram_init.FSMC_ReadWriteTimingStruct = &fsmc_norsramtiming_init;
    fsmc_norsram_init.FSMC_WriteTimingStruct     = &fsmc_norsramtiming_init;  
    
    FSMC_NORSRAMInit (&fsmc_norsram_init); 
    FSMC_NORSRAMCmd (FSMC_BANK1_NORSRAM, ENABLE);       
}

void ili9341_write_command(uint16_t command)
{
    GPIO_ResetBits(ILI9341_RS_GPIO, ILI9341_RS_PIN);

    *(__IO uint16_t *)(ILI9341_WRITE_COMMAND) = command;
}

void ili9341_write_data(uint16_t dat_a)
{
    GPIO_SetBits(ILI9341_RS_GPIO, ILI9341_RS_PIN);

    *(__IO uint16_t *)(ILI9341_WRITE_DATA) = dat_a;
}

void ili94341_write_register(unsigned int register_address, unsigned int register_value)
{
    ili9341_write_command(register_address);
    ili9341_write_data(register_value);
}

void ili9341_reset()
{
    GPIO_SetBits(ILI9341_RST_GPIO, ILI9341_RST_PIN);
    sleep_ms(50);
    GPIO_ResetBits(ILI9341_RST_GPIO, ILI9341_RST_PIN);      
    sleep_ms(50);
    GPIO_SetBits(ILI9341_RST_GPIO, ILI9341_RST_PIN);
    sleep_ms(50);
}

void ili9341_backlight(unsigned char state)
{
    if (state)
        GPIO_ResetBits(ILI9341_BL_GPIO, ILI9341_BL_PIN);   
    else
        GPIO_SetBits(ILI9341_BL_GPIO, ILI9341_BL_PIN);     
}

void ili9341_direction(unsigned char direction)
{
    ili9341_write_command(0x36);

    switch (direction) {
        // +----- x 
        // |
        // |
        // y              horizontal
        case 0 : ili9341_write_data(0xa8); break;
        // y -----+
        //        |
        //        |
        //        x       vertical
        case 1 : ili9341_write_data(0x08); break;
        //        y
        //        |
        //        |
        // x -----+ 0x08  horizontal
        case 2 : ili9341_write_data(0x68); break;
        // x
        // |
        // |
        // +----- y       vertical
        case 3 : ili9341_write_data(0xc8); break;
    }
}

void ili9341_init()
{
    ili9341_gpio_init();
    ili9341_fsmc_init();
    sleep_ms(200);
    ili9341_reset();
// -----------------------------------
    // ili9341_write_command(0xcf);
    // ili9341_write_data(0x00); 
    // ili9341_write_data(0xc1); 
    // ili9341_write_data(0x30); 
    // ili9341_write_command(0xed);  
    // ili9341_write_data(0x64); 
    // ili9341_write_data(0x03); 
    // ili9341_write_data(0x12); 
    // ili9341_write_data(0x81); 

    // ili9341_write_command(0xe8);  
    // ili9341_write_data(0x85); 
    // ili9341_write_data(0x10); 
    // ili9341_write_data(0x7a); 

    // ili9341_write_command(0xcb);  
    // ili9341_write_data(0x39); 
    // ili9341_write_data(0x2c); 
    // ili9341_write_data(0x00); 
    // ili9341_write_data(0x34); 
    // ili9341_write_data(0x02);

    // ili9341_write_command(0xf7);  
    // ili9341_write_data(0x20); 
    // ili9341_write_command(0xea);  
    // ili9341_write_data(0x00); 
    // ili9341_write_data(0x00); 
    // ili9341_write_command(0xc0); // Power control 
    // ili9341_write_data(0x1b);    // VRH[5:0] 
    // ili9341_write_command(0xc1); // Power control 
    // ili9341_write_data(0x01);    // SAP[2:0];BT[3:0] 
    // ili9341_write_command(0xc5); // VCM control 
    // ili9341_write_data(0x30);    // 3F
    // ili9341_write_data(0x30);    // 3C
    // ili9341_write_command(0xc7); // VCM control2 
    // ili9341_write_data(0xb7); 
    // // direction seting
    // // ili9341_write_command(0x36); // Memory access control 
    // // ili9341_write_data(0x68);
    // if (HORIZONTAL)
    //     ili9341_direction(2);
    // else
    //     ili9341_direction(3);

    // ili9341_write_command(0x3a);   
    // ili9341_write_data(0x55); 
    // ili9341_write_command(0xb1);   
    // ili9341_write_data(0x00);   
    // ili9341_write_data(0x1a); 
    // ili9341_write_command(0xb6); // Display function control 
    // ili9341_write_data(0x0a); 
    // ili9341_write_data(0xa2); 
    // ili9341_write_command(0xf2); // 3Gamma function disable 
    // ili9341_write_data(0x00); 
    // ili9341_write_command(0x26); // Gamma curve selected 
    // ili9341_write_data(0x01); 
    // ili9341_write_command(0xe0); // Set gamma 
    // ili9341_write_data(0x0f); 
    // ili9341_write_data(0x2a); 
    // ili9341_write_data(0x28); 
    // ili9341_write_data(0x08); 
    // ili9341_write_data(0x0e); 
    // ili9341_write_data(0x08); 
    // ili9341_write_data(0x54); 
    // ili9341_write_data(0xa9); 
    // ili9341_write_data(0x43); 
    // ili9341_write_data(0x0a); 
    // ili9341_write_data(0x0f); 
    // ili9341_write_data(0x00); 
    // ili9341_write_data(0x00); 
    // ili9341_write_data(0x00); 
    // ili9341_write_data(0x00);       
    // ili9341_write_command(0xe1); // Set gamma 
    // ili9341_write_data(0x00);
    // ili9341_write_data(0x15);
    // ili9341_write_data(0x17);
    // ili9341_write_data(0x07);
    // ili9341_write_data(0x11);
    // ili9341_write_data(0x06);
    // ili9341_write_data(0x2b);
    // ili9341_write_data(0x56);
    // ili9341_write_data(0x3c);
    // ili9341_write_data(0x05);
    // ili9341_write_data(0x10);
    // ili9341_write_data(0x0f);
    // ili9341_write_data(0x3f);
    // ili9341_write_data(0x3f);
    // ili9341_write_data(0x0f);
    // ili9341_write_command(0x2b); 
    // ili9341_write_data(0x00);
    // ili9341_write_data(0x00);
    // ili9341_write_data(0x01);
    // ili9341_write_data(0x3f);
    // ili9341_write_command(0x2a); 
    // ili9341_write_data(0x00);
    // ili9341_write_data(0x00);
    // ili9341_write_data(0x00);
    // ili9341_write_data(0xef);   
    // ili9341_write_command(0x11); // Exit sleep
    // ili9341_write_command(0x29); // display on
// -----------------------------------
    ili9341_write_command(0xcf);
    ili9341_write_data(0x00);
    ili9341_write_data(0xc1); // If it is 0x81, jitter noise will appear.
    ili9341_write_data(0x30);
    
    ili9341_write_command(0xed);
    ili9341_write_data(0x64);
    ili9341_write_data(0x03);
    ili9341_write_data(0x12);
    ili9341_write_data(0x81);
    
    ili9341_write_command(0xe8);
    ili9341_write_data(0x85);
    ili9341_write_data(0x10);
    ili9341_write_data(0x78);

    ili9341_write_command(0xcb);
    ili9341_write_data(0x39);
    ili9341_write_data(0x2c);
    ili9341_write_data(0x00);
    ili9341_write_data(0x34);
    ili9341_write_data(0x02);
    
    ili9341_write_command(0xf7);
    ili9341_write_data(0x20);
    
    ili9341_write_command(0xea);
    ili9341_write_data(0x00);
    ili9341_write_data(0x00);
    
    ili9341_write_command(0xb1);
    ili9341_write_data(0x00);
    ili9341_write_data(0x1b);
    
    ili9341_write_command(0xb6); // Display function control 
    ili9341_write_data(0x0a);
    ili9341_write_data(0xa2);
    
    ili9341_write_command(0xc0); // Power control
    ili9341_write_data(0x1b);

    ili9341_write_command(0xc1); // Power control 
    ili9341_write_data(0x01);

    ili9341_write_command(0xc5); // VCM control
    ili9341_write_data(0x45);
    ili9341_write_data(0x45);
    
    ili9341_write_command(0xc7); // VCM control 2
    ili9341_write_data(0xa2);
    
    ili9341_write_command(0xf2);
    ili9341_write_data(0x00);
    
    ili9341_write_command(0x26);
    ili9341_write_data(0x01);

    ili9341_write_command(0xe0);
    ili9341_write_data(0x0f);
    ili9341_write_data(0x26);
    ili9341_write_data(0x24);
    ili9341_write_data(0x0b);
    ili9341_write_data(0x0e);
    ili9341_write_data(0x09);
    ili9341_write_data(0x54);
    ili9341_write_data(0xA8);
    ili9341_write_data(0x46);
    ili9341_write_data(0x0c);
    ili9341_write_data(0x17);
    ili9341_write_data(0x09);
    ili9341_write_data(0x0f);
    ili9341_write_data(0x07);
    ili9341_write_data(0x00);
    
    ili9341_write_command(0xe1);
    ili9341_write_data(0x00);
    ili9341_write_data(0x19);
    ili9341_write_data(0x1b);
    ili9341_write_data(0x04);
    ili9341_write_data(0x10);
    ili9341_write_data(0x07);
    ili9341_write_data(0x2a);
    ili9341_write_data(0x47);
    ili9341_write_data(0x39);
    ili9341_write_data(0x03);
    ili9341_write_data(0x06);
    ili9341_write_data(0x06);
    ili9341_write_data(0x30);
    ili9341_write_data(0x38);
    ili9341_write_data(0x0f);
    // direction seting
    // ili9341_write_command(0x36);
    // ili9341_write_data(0xc8);
    if (HORIZONTAL)
        ili9341_direction(2);
    else
        ili9341_direction(3);

    ili9341_write_command(0x2a);
    ili9341_write_data(0x00);
    ili9341_write_data(0x00);
    ili9341_write_data(0x00);
    ili9341_write_data(0xef);
 
    ili9341_write_command(0x2b);
    ili9341_write_data(0x00);
    ili9341_write_data(0x00);
    ili9341_write_data(0x01);
    ili9341_write_data(0x3f);
    
    ili9341_write_command(0x3a);
    ili9341_write_data(0x55);
    
    ili9341_write_command(0x11);
    sleep_ms(120);   
    ili9341_write_command(0x29);

    ili9341_backlight(1);
}

void display_position(unsigned int y, unsigned int x)
{
    unsigned char seting_x = 0x2a;
    unsigned char seting_y = 0x2b;

    y = y - 1;
    x = x - 1;

    ili9341_write_command(seting_x);
    ili9341_write_data(x >> 8);
    ili9341_write_data(0x00ff & x);
    ili9341_write_data((x + 1) >> 8);
    ili9341_write_data((x + 1));
    
    ili9341_write_command(seting_y);
    ili9341_write_data(y >> 8);
    ili9341_write_data(0x00ff & y);
    ili9341_write_data((y + 1) >> 8);
    ili9341_write_data((y + 1));
}

void ili9341_display_region(unsigned int y, unsigned int x, unsigned int width, unsigned int height)
{
    ili9341_write_command(0x2a);
    ili9341_write_data(x >> 8);
    ili9341_write_data(x & 0xff);
    ili9341_write_data((x + width - 1) >> 8);
    ili9341_write_data((x + width - 1) & 0xff);

    ili9341_write_command(0x2b);
    ili9341_write_data(y >> 8);
    ili9341_write_data(y & 0xff);
    ili9341_write_data((y + height - 1) >> 8);
    ili9341_write_data((y + height - 1) & 0xff);

    ili9341_write_command(0x2c);
}
