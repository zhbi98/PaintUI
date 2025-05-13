
#include "mpu6050.h"

void mpu6050_gpio_init()
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(MPU6050_SCL_GPIO, ENABLE);
    RCC_AHB1PeriphClockCmd(MPU6050_SDA_GPIO, ENABLE);

    GPIO_PinAFConfig(MPU6050_SCL_GPIO, MPU6050_SCL_SRC, MPU6050_SCL_AF);
    GPIO_PinAFConfig(MPU6050_SDA_GPIO, MPU6050_SDA_SRC, MPU6050_SDA_AF);

    gpio_init.GPIO_Pin   = MPU6050_SCL_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_OD;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(MPU6050_SCL_GPIO, &gpio_init);

    gpio_init.GPIO_Pin   = MPU6050_SDA_PIN;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_OD;
    gpio_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(MPU6050_SDA_GPIO, &gpio_init);
}

void mpu6050_i2c_init()
{
    I2C_InitTypeDef i2c_init;

    RCC_AHB3PeriphClockCmd(MPU6050_I2C_CLOCK, ENABLE);

    I2C_DeInit(MPU6050_I2C);

    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_init.I2C_OwnAddress1 = MPU6050_I2C_ADDRESS;
    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    i2c_init.I2C_ClockSpeed = MPU6050_I2C_SPEED;

    I2C_Cmd(MPU6050_I2C, ENABLE);
    I2C_Init(MPU6050_I2C, &i2c_init);
}

unsigned int mpu6050_i2c_timout_handle(unsigned char err_num)
{
    I2C_InitTypeDef i2c_init;

    I2C_GenerateSTOP(MPU6050_I2C, ENABLE);
    I2C_SoftwareResetCmd(MPU6050_I2C, ENABLE);
    I2C_SoftwareResetCmd(MPU6050_I2C, DISABLE);

    I2C_DeInit(MPU6050_I2C);
    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_init.I2C_OwnAddress1 = MPU6050_I2C_ADDRESS;
    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    i2c_init.I2C_ClockSpeed = MPU6050_I2C_SPEED;

    // Enable the I2C peripheral 
    I2C_Cmd(MPU6050_I2C, ENABLE);  
    // Initialize the I2C peripheral 
    I2C_Init(MPU6050_I2C, &i2c_init);
    // I2C_ERROR("I2C error num = %d", err_num);
}

void mpu6050_i2c_check_timeout(unsigned int flag, FlagStatus value, unsigned int time, unsigned char err_num)
{
    unsigned int timeout = time;

    while (I2C_GetFlagStatus(MPU6050_I2C, flag) != value) {
        if (!(timeout--))
            return mpu6050_i2c_timout_handle(err_num);
    }
}

unsigned long mpu6050_i2c_write_reg(unsigned char address, unsigned char reg, unsigned short data_length, const unsigned char * reg_value)
{
    unsigned int result = 0;
    unsigned int i = 0; // i = data_length;
    __IO unsigned int timeout = MPU6050_I2C_LONG_TIMEOUT;

    // reg_value = reg_value + (data_length - 1);

    /* Wait for the busy flag to be cleared */
    mpu6050_i2c_check_timeout(I2C_FLAG_BUSY, RESET, MPU6050_I2C_LONG_TIMEOUT, 1);

    /* Start the config sequence */
    I2C_GenerateSTART(MPU6050_I2C, ENABLE);

    /* Wait for the start bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_SB, SET, MPU6050_I2C_FLAG_TIMEOUT, 2);

    /* Transmit the slave address and enable writing operation */
    I2C_Send7bitAddress(MPU6050_I2C, (address << 1), I2C_Direction_Transmitter);

    /* Wait for address bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_ADDR, SET, MPU6050_I2C_FLAG_TIMEOUT, 3);

    /* clear the ADDR interrupt bit  - this is done by reading SR1 and SR2*/
    I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR1);
    I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR2);

    /* Wait for address bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_TXE, SET, MPU6050_I2C_FLAG_TIMEOUT, 4);

    /* Transmit the first address for write operation */
    I2C_SendData(MPU6050_I2C, reg);


    for (i = 0; i < data_length; i++) {
        /* Wait for address bit to be set */
        mpu6050_i2c_check_timeout(I2C_FLAG_TXE, SET, MPU6050_I2C_FLAG_TIMEOUT, 5);

        /* Prepare the register value to be sent */
        I2C_SendData(MPU6050_I2C, reg_value[i]);
    }  

    /* Wait for address bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_BTF, SET, MPU6050_I2C_FLAG_TIMEOUT, 6);

    /* End the configuration sequence */
    I2C_GenerateSTOP(MPU6050_I2C, ENABLE);  

    /* Return the verifying value: 0 (Passed) or 1 (Failed) */
    return result;  
}

unsigned long mpu6050_i2c_read_reg(unsigned char address, unsigned char reg, unsigned short data_length, unsigned char * reg_value)
{
    unsigned int i = 0, result = 0;
    __IO unsigned int timeout = MPU6050_I2C_LONG_TIMEOUT;

    /* Wait for the busy flag to be cleared */
    mpu6050_i2c_check_timeout(I2C_FLAG_BUSY, RESET, MPU6050_I2C_LONG_TIMEOUT, 7);

    /* Start the config sequence */
    I2C_GenerateSTART(MPU6050_I2C, ENABLE);

    /* Wait for the start bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_SB, SET, MPU6050_I2C_FLAG_TIMEOUT, 8);

    /* Transmit the slave address and enable writing operation */
    I2C_Send7bitAddress(MPU6050_I2C, (address << 1), I2C_Direction_Transmitter);

    /* Wait for the start bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_ADDR, SET, MPU6050_I2C_FLAG_TIMEOUT, 9);

    /* clear the ADDR interrupt bit  - this is done by reading SR1 and SR2*/
    I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR1);
    I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR2);

    /* Wait for address bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_TXE, SET, MPU6050_I2C_FLAG_TIMEOUT, 10);

    /* Transmit the register address to be read */
    I2C_SendData(MPU6050_I2C, reg);

    /* Wait for address bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_TXE, SET, MPU6050_I2C_FLAG_TIMEOUT, 11);  

    /*!< Send START condition a second time */  
    I2C_GenerateSTART(MPU6050_I2C, ENABLE);

    /* Wait for the start bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_SB, SET, MPU6050_I2C_FLAG_TIMEOUT, 12);

    /*!< Send address for read */
    I2C_Send7bitAddress(MPU6050_I2C, (address << 1), I2C_Direction_Receiver);  

    /* Wait for the start bit to be set */
    mpu6050_i2c_check_timeout(I2C_FLAG_ADDR, SET, MPU6050_I2C_FLAG_TIMEOUT, 13);

    if (data_length == 1) {
        /*!< Disable Acknowledgment */
        I2C_AcknowledgeConfig(MPU6050_I2C, DISABLE);

        /* clear the ADDR interrupt bit  - this is done by reading SR1 and SR2*/
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR1);
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR2);

        /*!< Send STOP Condition */
        I2C_GenerateSTOP(MPU6050_I2C, ENABLE);

        /* Wait for the RXNE bit to be set */
        mpu6050_i2c_check_timeout(I2C_FLAG_RXNE, SET, MPU6050_I2C_FLAG_TIMEOUT, 14);

        reg_value[0] = I2C_ReceiveData(MPU6050_I2C);
    } else if (data_length == 2) {
        /*!< Disable Acknowledgment */
        I2C_AcknowledgeConfig(MPU6050_I2C, DISABLE);

        /* Set POS bit */ 
        MPU6050_I2C->CR1 |= I2C_CR1_POS;

        /* clear the ADDR interrupt bit  - this is done by reading SR1 and SR2*/
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR1);
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR2);

        /* Wait for the buffer full bit to be set */
        mpu6050_i2c_check_timeout(I2C_FLAG_BTF, SET, MPU6050_I2C_FLAG_TIMEOUT, 15);

        /*!< Send STOP Condition */
        I2C_GenerateSTOP(MPU6050_I2C, ENABLE);

        /* Read 2 bytes */
        reg_value[0] = I2C_ReceiveData(MPU6050_I2C);
        reg_value[1] = I2C_ReceiveData(MPU6050_I2C);
    } else if (data_length == 3) {
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR1);
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR2);

        /* Wait for the buffer full bit to be set */
        mpu6050_i2c_check_timeout(I2C_FLAG_BTF, SET, MPU6050_I2C_FLAG_TIMEOUT, 16);
        /*!< Disable Acknowledgment */
        I2C_AcknowledgeConfig(MPU6050_I2C, DISABLE);
        /* Read 1 bytes */
        reg_value[0] = I2C_ReceiveData(MPU6050_I2C);
        /*!< Send STOP Condition */
        I2C_GenerateSTOP(MPU6050_I2C, ENABLE);        
        /* Read 1 bytes */
        reg_value[1] = I2C_ReceiveData(MPU6050_I2C);
        /* Wait for the buffer full bit to be set */
        mpu6050_i2c_check_timeout(I2C_FLAG_RXNE, SET, MPU6050_I2C_FLAG_TIMEOUT, 17);
        /* Read 1 bytes */
        reg_value[2] = I2C_ReceiveData(MPU6050_I2C);
    } else { /* more than 2 bytes */
        /* clear the ADDR interrupt bit  - this is done by reading SR1 and SR2*/
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR1);
        I2C_ReadRegister(MPU6050_I2C, I2C_Register_SR2);

        for (i = 0; i < data_length; i++) {
            if (i == (data_length - 3)) {
                /* Wait for the buffer full bit to be set */
                mpu6050_i2c_check_timeout(I2C_FLAG_BTF, SET, MPU6050_I2C_FLAG_TIMEOUT, 16);

                /*!< Disable Acknowledgment */
                I2C_AcknowledgeConfig(MPU6050_I2C, DISABLE);

                /* Read 1 bytes */
                reg_value[i++] = I2C_ReceiveData(MPU6050_I2C);

                /*!< Send STOP Condition */
                I2C_GenerateSTOP(MPU6050_I2C, ENABLE);        

                /* Read 1 bytes */
                reg_value[i++] = I2C_ReceiveData(MPU6050_I2C);

                /* Wait for the buffer full bit to be set */
                mpu6050_i2c_check_timeout(I2C_FLAG_RXNE, SET, MPU6050_I2C_FLAG_TIMEOUT, 17);

                /* Read 1 bytes */
                reg_value[i++] = I2C_ReceiveData(MPU6050_I2C);  
                goto finish_read;
            }

            /* Wait for the RXNE bit to be set */
            mpu6050_i2c_check_timeout(I2C_FLAG_RXNE, SET, MPU6050_I2C_FLAG_TIMEOUT, 18);
            reg_value[i] = I2C_ReceiveData(MPU6050_I2C); 
        }
    }
  
finish_read:
    /* Clear BTF flag */
    I2C_ClearFlag(MPU6050_I2C, I2C_FLAG_BTF);
    /* Wait for the busy flag to be cleared */
    mpu6050_i2c_check_timeout(I2C_FLAG_BUSY, RESET, MPU6050_I2C_LONG_TIMEOUT, 19);  
    /*!< Re-Enable Acknowledgment to be ready for another reception */
    I2C_AcknowledgeConfig(MPU6050_I2C, ENABLE);
    //Disable POS -- TODO
    MPU6050_I2C->CR1 &= ~I2C_CR1_POS;  

    /* Return the byte read from sensor */
    return result;
}

unsigned short i2c_retry_time = 55;

void set_i2c_retry_time(unsigned short ms)
{
    i2c_retry_time = ms;
}

unsigned short get_i2c_retry_time()
{
    return i2c_retry_time;
}

int mpu6050_i2c_write_reg_retry(unsigned char slave_addr, unsigned char reg_addr, const unsigned char * byte, unsigned short length)
{
    char retries = 0;
    int ret = 0;
    unsigned short retry_in_mlsec = get_i2c_retry_time();

try_again:
    ret = 0;
    ret = mpu6050_i2c_write_reg(slave_addr, reg_addr, length, byte); 

    if (ret && retry_in_mlsec) {
        if (retries++ > 4)
            return ret;

        sleep_ms(retry_in_mlsec);
        goto try_again;
    }
    return ret;
}

int mpu6050_i2c_read_reg_retry(unsigned char slave_addr, unsigned char reg_addr, unsigned char * byte,  unsigned short length)
{
    char retries=0;
    int ret = 0;
    unsigned short retry_in_mlsec = get_i2c_retry_time();

try_again:
    ret = 0;
    ret = mpu6050_i2c_read_reg(slave_addr, reg_addr, length, byte);

    if (ret && retry_in_mlsec) {
        if (retries++ > 4)
            return ret;

        sleep_ms(retry_in_mlsec);
        goto try_again;
    } 
    return ret;
}

void mpu6050_write_data(unsigned char reg_address, unsigned char reg_data)
{
    mpu6050_i2c_write_reg_retry(MPU6050_ADDRESS, reg_address, &reg_data, 1);
}

void mpu6050_read_data(unsigned char reg_address, unsigned char * buf, unsigned char num)
{
    mpu6050_i2c_read_reg_retry(MPU6050_ADDRESS, reg_address, buf, num);
}

void mpu6050_init()
{
    mpu6050_gpio_init();
    mpu6050_i2c_init();
    sleep_ms(2000);

    mpu6050_write_data(PWR_MGMT_1, 0x80);
    mpu6050_write_data(PWR_MGMT_1, 0x00);
    mpu6050_write_data(SMPLRT_DIV, 0x07);
    mpu6050_write_data(CONFIG, 0x06);
    mpu6050_write_data(GYRO_CONFIG, 0x18);
    mpu6050_write_data(ACCEL_CONFIG, 0x01);
}

unsigned char mpu6050_read_id()
{
    unsigned char id = 0x00;

    mpu6050_read_data(WHO_AM_I, &id, 1);
    // if (id != 0x68)
    //     return 0;
    // else
    //     return 1;
    return id;
}

void mpu6050_read_accel(short * accel_data)
{
    unsigned char buf[6];

    mpu6050_read_data(ACCEL_XOUT_H, buf, 6);
    accel_data[0] = (buf[0] << 8) | buf[1];
    accel_data[1] = (buf[2] << 8) | buf[3];
    accel_data[2] = (buf[4] << 8) | buf[5];
}

void mpu6050_read_gyro(short * gyro_data)
{
    unsigned char buf[6];

    mpu6050_read_data(GYRO_XOUT_H, buf, 6);
    gyro_data[0] = (buf[0] << 8) | buf[1];
    gyro_data[1] = (buf[2] << 8) | buf[3];
    gyro_data[2] = (buf[4] << 8) | buf[5];
}

void mpu6050_read_temper(short * temp_data)
{
    unsigned char buf[2];

    mpu6050_read_data(TEMP_OUT_H, buf, 2);
    *temp_data = (buf[0] << 8) | buf[1];
}

void mpu6050_return_temper(float * temperature)
{
    short temp3;
    unsigned char buf[2];
    
    mpu6050_read_data(TEMP_OUT_H, buf, 2);
    temp3 = (buf[0] << 8) | buf[1];    
    *temperature = ((double)temp3 / 340.0) + 36.53;
}
