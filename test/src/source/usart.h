
#include "usart.h"

unsigned char usart_data[64] = {0};

static void usart_nvic_init()
{
    NVIC_InitTypeDef nvic_init;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    nvic_init.NVIC_IRQChannel = USART_IRQN;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);
}

static void usart_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(USART_TX_CLOCK | USART_RX_CLOCK, ENABLE);

    GPIO_PinAFConfig(USART_TX_GPIO, USART_TX_SRC, USART_TX_AF);
    GPIO_PinAFConfig(USART_RX_GPIO, USART_RX_SRC, USART_RX_AF);

    gpio_init.GPIO_Pin   = USART_TX_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_TX_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = USART_RX_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_RX_GPIO, &gpio_init);
}

void usart_init()
{
    USART_InitTypeDef usart_init;

    usart_gpio_init();
    
    RCC_APB2PeriphClockCmd(USART_CLOCK, ENABLE);

    usart_init.USART_BaudRate = BAUD_RATE;
    usart_init.USART_WordLength = USART_WordLength_8b;
    usart_init.USART_StopBits = USART_StopBits_1;
    usart_init.USART_Parity = USART_Parity_No;
    usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(CURRENT_USART, &usart_init);

    usart_nvic_init();

    USART_ITConfig(CURRENT_USART, USART_IT_RXNE, ENABLE);
    USART_Cmd(CURRENT_USART, ENABLE);
}

void usart_send_byte(USART_TypeDef * current_usart, unsigned char a_byte)
{
    USART_SendData(current_usart, a_byte);
    while (USART_GetFlagStatus(current_usart, USART_FLAG_TXE) == RESET);
}

void usart_send_string(USART_TypeDef * current_usart, unsigned char * string)
{
    unsigned char i = 0;

    while (string[i] != '\0') {
        usart_send_byte(current_usart, string[i]);
        i++;
    }
    while (USART_GetFlagStatus(current_usart, USART_FLAG_TC) == RESET);
}

void usart_send_value(USART_TypeDef * current_usart, unsigned char * format, ...)
{
    unsigned char value[10];

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);
    
    va_end(parameter_pointer);

    usart_send_string(current_usart, value);
}

void USART_IRQHANDLER()
{
    static unsigned char i = 0;
    if (USART_GetITStatus(CURRENT_USART, USART_IT_RXNE) != RESET) {
        usart_data[i] = USART_ReceiveData(CURRENT_USART);
        i++;
    }
}
