
#ifndef __POWER_MANAGER_H__
#define __POWER_MANAGER_H__

#include <math.h>
#include <stdbool.h>

#include "log.h"
#include "bsp.h"

#define ADC_MAX    4096 // 12bit
#define VREF       280  // 2.8V, 2800mV              (magnify 100)
#define PROPORTION 57   // R(all):R(1) = 5.7(M):1(M) (magnify 10)

#define BATTERY_VOLTAGE_MIN 2700
#define BATTERY_VOLTAGE_MAX 4500

#define DATA_BUF_MAX 100

struct power_manager_t {
    unsigned int  data_buf[DATA_BUF_MAX + 1];
    unsigned char data_index;
    unsigned char data_set_size;
    unsigned char collect_complete;
    unsigned int  out_put_data;
};

extern struct power_manager_t power_manager;

extern void power_data_serialize(int data_buf[], int len);
extern void power_data_handler();
extern unsigned char read_battery_power();

#endif
