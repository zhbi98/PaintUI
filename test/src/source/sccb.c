
#include "sccb.h"

void sccb_gpio_init()
{               
    GPIO_InitTypeDef  gpio_init;

    RCC_AHB1PeriphClockCmd(SCCB_SDA_CLOCK, ENABLE);
    RCC_AHB1PeriphClockCmd(SCCB_SCL_CLOCK, ENABLE);

    gpio_init.GPIO_Pin   = SCCB_SDA_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(SCCB_SDA_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = SCCB_SCL_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(SCCB_SCL_GPIO, &gpio_init);

    GPIO_SetBits(SCCB_SDA_GPIO, SCCB_SDA_PIN);
    GPIO_SetBits(SCCB_SCL_GPIO, SCCB_SCL_PIN);

    sccb_sda_out();  
}            

void sccb_on()
{
    SCCB_SDA_H();
    SCCB_SCL_H();
    sleep_us(50);  
    SCCB_SDA_L();
    sleep_us(50);    
    SCCB_SCL_L();
}

void sccb_off()
{
    SCCB_SDA_L();
    sleep_us(50);    
    SCCB_SCL_H(); 
    sleep_us(50); 
    SCCB_SDA_H(); 
    sleep_us(50);
}  

void sccb_no_ack()
{
    sleep_us(50);
    SCCB_SDA_H(); 
    SCCB_SCL_H(); 
    sleep_us(50);
    SCCB_SCL_L(); 
    sleep_us(50);
    SCCB_SDA_L(); 
    sleep_us(50);
}

unsigned char sccb_write(unsigned char dat_a)
{
    unsigned char write, t;
   
    for (write = 0;write < 8; write++) {
        if (dat_a & 0x80)
            SCCB_SDA_H(); 
        else
            SCCB_SDA_L();

        dat_a <<= 1;
        sleep_us(50);
        SCCB_SCL_H();
        sleep_us(50);
        SCCB_SCL_L();
    }

    sccb_sda_in();
    sleep_us(50);
    // Receive the ninth bit 
    // to determine whether 
    // the transmission is 
    // successful
    SCCB_SCL_H();         
    sleep_us(50);

    if (SCCB_READ_SDA())
        t = 1;
    else
        t = 0;

    SCCB_SCL_L();      
    sccb_sda_out();
    // t = 0 success, t = 1 error
    return t;  
}    

unsigned char sccb_read()
{
    unsigned char dat_a = 0, read;

    sccb_sda_in();
    for (read = 0; read < 8; read++) {                 
        sleep_us(50);
        SCCB_SCL_H();
        dat_a = dat_a << 1;
        if (SCCB_READ_SDA())
            dat_a++;

        sleep_us(50);
        SCCB_SCL_L();
    }

    sccb_sda_out();  
    
    return dat_a;
}                               

unsigned char sccb_write_reg(unsigned char reg, unsigned char dat_a)
{
    unsigned char t = 0;

    sccb_on();

    if (sccb_write(OV7670_ADDRESS))
        t = 1;
    sleep_us(100);

    if (sccb_write(reg))
        t = 1;    
    sleep_us(100);

    if (sccb_write(dat_a))
        t = 1;
    sccb_off();

    // t = 0 success, t = 1 error
    return  t;
}                               

unsigned char sccb_read_reg(unsigned char reg)
{
    unsigned char dat_a = 0;

    sccb_on();
    sccb_write(OV7670_ADDRESS + WRITE);
    sleep_us(100);   
    sccb_write(reg);
    sleep_us(100);    
    sccb_off();   
    sleep_us(100);     

    sccb_on();
    sccb_write(OV7670_ADDRESS + READ);
    sleep_us(100);
    dat_a = sccb_read();
    sccb_no_ack();
    sccb_off();

    return dat_a;
}
