
#include "ov7670.h" 

unsigned char ov7670_init(void)
{

    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(OV7670_CS_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_RRST_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_RCK_CLOCK,  ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_WREN_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_WRST_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_VSYNC_CLOCK,ENABLE);

    RCC_AHB1PeriphClockCmd(OV7670_D0_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D1_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D2_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D3_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D4_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D5_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D6_CLOCK,   ENABLE);
    RCC_AHB1PeriphClockCmd(OV7670_D7_CLOCK,   ENABLE);

    // D0, D1, D2, D3, D4, D5, D6, D7
    gpio_init.GPIO_Pin   = OV7670_D0_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D0_GPIO, &gpio_init);
    
    gpio_init.GPIO_Pin   = OV7670_D1_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D1_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_D2_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D2_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_D3_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D3_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_D4_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D4_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_D5_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D5_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_D6_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D6_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_D7_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_D7_GPIO, &gpio_init);


    gpio_init.GPIO_Pin   = OV7670_VSYNC_PIN;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_Init(OV7670_VSYNC_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_RRST_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;    
    GPIO_Init(OV7670_RRST_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_RCK_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;    
    GPIO_Init(OV7670_RCK_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = OV7670_WRST_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;    
    GPIO_Init(OV7670_WRST_GPIO, &gpio_init);    

    gpio_init.GPIO_Pin   = OV7670_WREN_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;    
    GPIO_Init(OV7670_WREN_GPIO, &gpio_init); 

    gpio_init.GPIO_Pin   = OV7670_CS_PIN;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;    
    GPIO_Init(OV7670_CS_GPIO, &gpio_init);             


    sccb_gpio_init();

    unsigned char t;

    if (sccb_write_reg(0x12, 0x80))
        // reset sccb 
        return 1; 
    sleep_ms(50);  

    t = sccb_read_reg(0x0b);   
    if (t != 0x73)
        return 2;

    t = sccb_read_reg(0x0a);   
    if(t != 0x76)
        return 2;

    for (int i = 0; i < sizeof(ov7670_regdata) / sizeof(ov7670_regdata[0]); i++) {
        sccb_write_reg(ov7670_regdata[i][0], ov7670_regdata[i][1]);
    }

    return 0;
}

void exti8_init(void)
{                                              
    EXTI_InitTypeDef exti_init;
    NVIC_InitTypeDef nvic_init;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // because ov7670 vsync io connect to gpioa pin8
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);

    // because ov7670 vsync io connect to gpioa pin8
    exti_init.EXTI_Line = EXTI_Line8;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt; 
    exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
    exti_init.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_init);

    // nvic only need to be configured once
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // EXTI9_5_IRQn is interrupt 5 -> 9 interrupt number
    nvic_init.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init.NVIC_IRQChannelSubPriority =  0;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);  
}

void read_image(uint32_t n, unsigned int *vm)
{
    uint32_t piexl;
    unsigned int color;

    if (frame != 0) {
        // start resetting the read pointer
        OV7670_RRST = 0;

        OV7670_RCK_L();
        OV7670_RCK_H();
        OV7670_RCK_L();
        // end of reset read pointer
        OV7670_RRST = 1;
        OV7670_RCK_H();

        for (piexl = 0; piexl < n; piexl++) {
            OV7670_RCK_L();
            color = OV7670_DATA();
            OV7670_RCK_H();

            color <<= 8;

            OV7670_RCK_L();
            color |= OV7670_DATA();
            OV7670_RCK_H();

            vm[piexl] = color;
        }
        frame = 0;
    }
}

void ov7670_light_mode(unsigned char mode)
{
    unsigned char reg13 = 0xe7;
    unsigned char reg01 = 0;
    unsigned char reg02 = 0;

    // The default is set to automatic white balance
    // reg13 = 0xe7;
    switch (mode) {
        case 1:// sunny
            reg13 = 0xe5;
            reg01 = 0x5a;
            reg02 = 0x5c;
            break;

        case 2:// cloudy
            reg13 = 0xe5;
            reg01 = 0x58;
            reg02 = 0x60;
            break;

        case 3:// office
            reg13 = 0xe5;
            reg01 = 0x84;
            reg02 = 0x4c;
            break;

        case 4:// home
            reg13 = 0xe5;
            reg01 = 0x96;
            reg02 = 0x40;
            break;  
    }

    sccb_write_reg(0x13, reg13);// COM8 setting
    sccb_write_reg(0x01, reg01);// AWB Blue channel gain 
    sccb_write_reg(0x02, reg02);// AWB Red channel gain 
}

void ov7670_color_saturation(unsigned char sat)
{
    unsigned char reg4f5054 = 0x80;
    unsigned char reg52 = 0x22;
    unsigned char reg53 = 0x5e;

    switch (sat) {
        case 0:// -2
            reg4f5054 = 0x40;    
            reg52 = 0x11;
            reg53 = 0x2F;        
            break;

        case 1:// -1
            reg4f5054 = 0x66;       
            reg52 = 0x1B;
            reg53 = 0x4B;     
            break;

        case 3:// +1
            reg4f5054 = 0x99;      
            reg52 = 0x28;
            reg53 = 0x71;      
            break;

        case 4:// +2
            reg4f5054 = 0xC0;      
            reg52 = 0x33;
            reg53 = 0x8D;      
            break;  
    }
    sccb_write_reg(0x4F, reg4f5054); // Color matrix factor 1
    sccb_write_reg(0x50, reg4f5054); // Color matrix factor 2
    sccb_write_reg(0x51, 0x00);      // Color matrix factor 3
    sccb_write_reg(0x52, reg52);     // Color matrix factor 4
    sccb_write_reg(0x53, reg53);     // Color matrix factor 5
    sccb_write_reg(0x54, reg4f5054); // Color matrix factor 6 
    sccb_write_reg(0x58, 0x9e);      // MTXS 
}

// 0: -2
// 1: -1
// 2:  0
// 3: +1
// 4: +2
void ov7670_brightness(unsigned char bright)
{
    unsigned char reg55 = 0x00;

    switch (bright) {
        case 0:// -2
            reg55 = 0xB0;        
            break;

        case 1:// -1
            reg55 = 0x98;        
            break;

        case 3:// +1
            reg55 = 0x18;        
            break;

        case 4:// +2
            reg55 = 0x30;        
            break;  
    }
    sccb_write_reg(0x55, reg55);
}

// 0: -2
// 1: -1
// 2,  0
// 3, +1
// 4, +2
void ov7670_contrast(unsigned char contrast)
{
    unsigned char reg56 = 0x40;

    // reg56 = 0X40; default contrast = 2
    switch (contrast) {
        case 0:// -2
            reg56 = 0x30;        
            break;

        case 1:// -1
            reg56 = 0x38;        
            break;

        case 3:// +1
            reg56 = 0x50;        
            break;

        case 4:// +2
            reg56 = 0x60;        
            break;  
    }
    sccb_write_reg(0x56, reg56);
}

// 0: normal mode
// 1: negative
// 2: black and white
// 3: reddish
// 4: greenish
// 5: blue
// 6: retro
void ov7670_special_effects(unsigned char eft)
{
    unsigned char reg3a = 0x04;
    unsigned char reg67 = 0xc0;
    unsigned char reg68 = 0x80;

    // reg3a = 0X04; The default is normal mode
    switch (eft) {
        case 1:// negative
            reg3a = 0x24;
            reg67 = 0x80;
            reg68 = 0x80;
            break;

        case 2:// Black and white
            reg3a = 0x14;
            reg67 = 0x80;
            reg68 = 0x80;
            break;

        case 3:// Reddish
            reg3a = 0x14;
            reg67 = 0xc0;
            reg68 = 0x80;
            break;

        case 4:// Greenish
            reg3a = 0x14;
            reg67 = 0x40;
            reg68 = 0x40;
            break;

        case 5:// Bluish
            reg3a = 0x14;
            reg67 = 0x80;
            reg68 = 0xC0;
            break;

        case 6:// Retro
            reg3a = 0x14;
            reg67 = 0xA0;
            reg68 = 0x40;
            break;   
    }
    sccb_write_reg(0x3a, reg3a);// TSLB setting
    sccb_write_reg(0x68, reg67);// MANU
    sccb_write_reg(0x67, reg68);// MANV
}

void image_size(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    unsigned int _x;
    unsigned int _y;

    unsigned char t; 
    _x = x + width * 2;  // V * 2
    _y = y + height * 2;

    if (_y > 784)
        _y -= 784;
    t = sccb_read_reg(0x03);   // read before Vref value
    t &= 0xf0;
    t |= ((_x & 0x03) << 2) | (x & 0x03);

    sccb_write_reg(0x03, t);      //Set the lowest 2 bits of Vref's start and end
    sccb_write_reg(0x19, x >> 2); //Set the high 8 bits of Vref's start
    sccb_write_reg(0x1a, _x >> 2);//Set the high 8 bits of the end of Vref

    t = sccb_read_reg(0x32);      //Read the value before Href
    t &= 0xc0;
    t |= ((_y & 0x07) << 3) | (y & 0x07);

    sccb_write_reg(0x32, t);
    sccb_write_reg(0x17, y >> 3); //Set the high 8 bits of Href's start
    sccb_write_reg(0x18, _y >> 3);//Set the high 8 bits of the end of Href
}

unsigned char frame;

// EXTI9_5_IRQHandler is interrupt 
// 5 -> 9 shared interrupt function
void EXTI9_5_IRQHandler()
{               
    if (EXTI_GetITStatus(EXTI_Line8) == SET) {      
        OV7670_WRST = 0; // reset write point
        // GPIO_ResetBits(OV7670_WRST_GPIO, OV7670_WRST_PIN);       
        OV7670_WRST = 1;
        // GPIO_SetBits(OV7670_WRST_GPIO, OV7670_WRST_PIN);
       
        OV7670_WREN = 1; // allow write to FIFO
        // GPIO_SetBits(OV7670_WREN_GPIO, OV7670_WREN_PIN);   
        
        //frame interrupt +1
        frame++;
    }
    EXTI_ClearITPendingBit(EXTI_Line8);                       
}
