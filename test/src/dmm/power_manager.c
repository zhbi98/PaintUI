
#include "power_manager.h"

struct power_manager_t power_manager = {
    .data_index       = 0,
    .out_put_data     = 0,
    .data_set_size    = 5,
    .collect_complete = false,
};

void power_data_serialize(int data_buf[], int len)
{
    int t;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (data_buf[j] > data_buf[j + 1]) {
                t = data_buf[j];
                data_buf[j] = data_buf[j + 1];
                data_buf[j + 1] = t;
            }
        }
    }
}

void power_data_handler()
{
    if (power_manager.collect_complete == false) {
        // info("data_index:%d", power_manager.data_index);
        power_manager.data_buf[power_manager.data_index] = get_battery_adc();
        power_manager.data_index++;
    }

    if (power_manager.data_index > power_manager.data_set_size - 1) {
        power_manager.collect_complete = true;
        power_manager.data_index = 0;
        power_data_serialize(power_manager.data_buf, power_manager.data_set_size);

        #if 0
        info("data_set_size:%d", power_manager.data_set_size);
        power_manager.collect_complete = false;
        for (unsigned char t = 0; t < power_manager.data_set_size; t++) {
            info("data_buf2:%d", power_manager.data_buf[t]);
        }

        power_manager.data_set_size += 10; // Pay attention to the position 
        if (power_manager.data_set_size >= DATA_BUF_MAX - 1)
            power_manager.data_set_size = DATA_BUF_MAX - 1;
        #endif
    }

    int sum              = 0;
    int mean             = 0;
    int variance_sum     = 0;
    float variance       = 0;
    unsigned char num    = 0;
    unsigned char offset = 0;

    if (power_manager.collect_complete == true) {
        num = (int)(power_manager.data_set_size / 5);
        offset = (int)((power_manager.data_set_size - num) / 2);

        for (unsigned char i = 0; i < num; i++)
            sum += power_manager.data_buf[offset + i];

        if (num <= 0)
            num = 1;
        mean = (int)(sum / num);

        for (unsigned char j = 0; j < num; j++) {
            variance_sum += (int)(pow(power_manager.data_buf[offset + j] - mean, 2));
            // info("deta:%d", power_manager.data_buf[offset + j] - mean);
        }
        if (num <= 0.0)
            num = 1.0;
        variance = (float)variance_sum / (float)num;

        #if 0
        info("data_set_size:%d",power_manager.data_set_size);
        info("offset:%d",       offset                     );
        info("num:%d",          num                        );
        info("sum:%d",          sum                        );
        info("mean:%d",         mean                       );
        info("variance_sum:%d", variance_sum               );
        info("variance:%.3f",   variance                   );
        #endif

        if (variance <= 1.5)
            power_manager.out_put_data = mean;

        power_manager.data_set_size += 10; // Pay attention to the position 
        if (power_manager.data_set_size >= DATA_BUF_MAX)
            power_manager.data_set_size = DATA_BUF_MAX;

        power_manager.collect_complete = false;
    }
}

unsigned char read_battery_power()
{
    unsigned int voltage;
    unsigned int capacity;
    static unsigned char run_times = 0;

    // (Ref v) * (Adc Current / Adc Full) * PROPORTION
    voltage = (int)(VREF * power_manager.out_put_data * PROPORTION / ADC_MAX);
    capacity = (int)((voltage - BATTERY_VOLTAGE_MIN) * 100 / (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN));

    #if 0
    if (run_times >= 5) {
        info("voltage:%d", voltage);
        info("capacity:%d", capacity);
        run_times = 0;
    }
    run_times++;
    #endif

    if (capacity >= 100)
        capacity = 100;

    return capacity;
}
