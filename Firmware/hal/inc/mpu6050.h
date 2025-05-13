
#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "stm32f4xx.h"

#include "time.h"

#define MPU6050_I2C         I2C1
#define MPU6050_I2C_CLOCK   RCC_APB1Periph_I2C1

#define MPU6050_I2C_SPEED   400000
#define MPU6050_I2C_ADDRESS 0x00

#define MPU6050_SCL_GPIO  GPIOB
#define MPU6050_SCL_PIN   GPIO_Pin_8
#define MPU6050_SCL_CLOCK RCC_AHB1Periph_GPIOB
#define MPU6050_SCL_AF    GPIO_AF_I2C1
#define MPU6050_SCL_SRC   GPIO_PinSource8

#define MPU6050_SDA_GPIO  GPIOB
#define MPU6050_SDA_PIN   GPIO_Pin_9
#define MPU6050_SDA_CLOCK RCC_AHB1Periph_GPIOB
#define MPU6050_SDA_AF    GPIO_AF_I2C1
#define MPU6050_SDA_SRC   GPIO_PinSource9

#define MPU6050_I2C_FLAG_TIMEOUT ((unsigned int)900)
#define MPU6050_I2C_LONG_TIMEOUT ((unsigned int)(300 * MPU6050_I2C_FLAG_TIMEOUT))

// mpu6050 register address
#define SMPLRT_DIV      0x19
#define CONFIG          0x1a

#define GYRO_CONFIG     0x1b
#define ACCEL_CONFIG    0x1c

#define ACCEL_XOUT_H    0x3b
#define ACCEL_XOUT_L    0x3c
#define ACCEL_YOUT_H    0x3d
#define ACCEL_YOUT_L    0x3e
#define ACCEL_ZOUT_H    0x3f
#define ACCEL_ZOUT_L    0x40

#define TEMP_OUT_H      0x41
#define TEMP_OUT_L      0x42

#define GYRO_XOUT_H     0x43
#define GYRO_XOUT_L     0x44
#define GYRO_YOUT_H     0x45
#define GYRO_YOUT_L     0x46
#define GYRO_ZOUT_H     0x47
#define GYRO_ZOUT_L     0x48

#define PWR_MGMT_1      0x6b
#define WHO_AM_I        0x75

#define MPU6050_ADDRESS 0x69

extern unsigned short i2c_retry_time;

extern void mpu6050_gpio_init();
extern void mpu6050_i2c_init();
extern unsigned int mpu6050_i2c_timout_handle(unsigned char err_num);
extern void mpu6050_i2c_check_timeout(unsigned int flag, FlagStatus value, unsigned int time, unsigned char err_num);
extern unsigned long mpu6050_i2c_write_reg(unsigned char address, unsigned char reg, unsigned short data_length, const unsigned char * reg_value);
extern unsigned long mpu6050_i2c_read_reg(unsigned char address, unsigned char reg, unsigned short data_length, unsigned char * reg_value);
extern void set_i2c_retry_time(unsigned short ms);
extern unsigned short get_i2c_retry_time();
extern int mpu6050_i2c_write_reg_retry(unsigned char slave_addr, unsigned char reg_addr, const unsigned char * byte, unsigned short length);
extern int mpu6050_i2c_read_reg_retry(unsigned char slave_addr, unsigned char reg_addr, unsigned char * byte,  unsigned short length);
extern void mpu6050_write_data(unsigned char reg_address, unsigned char reg_data);
extern void mpu6050_read_data(unsigned char reg_address, unsigned char * buf, unsigned char num);

extern void mpu6050_init();
extern unsigned char mpu6050_read_id();
extern void mpu6050_read_accel(short * accel_data);
extern void mpu6050_read_gyro(short * gyro_data);
extern void mpu6050_read_temper(short * temp_data);
extern void mpu6050_return_temper(float * temperature);

#endif
