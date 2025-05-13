
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
        power_manager.data_buf[power_manager.data_index] = 3500/*get_battery_adc()*/;
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
    
    if (voltage <= BATTERY_VOLTAGE_MIN)
        voltage = BATTERY_VOLTAGE_MIN;

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

#if 0 /** Auto power off tips demo */
#define CONTROLLER_WAIT 10 //  10(s)
#define TIPS_INTERVAL  300 // 300(s)

struct lp_controller_t {
    unsigned char wait;
    unsigned int interval;
    unsigned char times;
    unsigned char tips;
    unsigned char power;
};

struct lp_controller_t lp_controller = {
    .wait     = SECOND_TO_TICKS(CONTROLLER_WAIT),
    .interval = SECOND_TO_TICKS(TIPS_INTERVAL),
    .times    = 5,
    .tips     = false,
    .power    = 0,
};

void power_handler_wait_timing()
{
    if (lp_controller.wait > 0)
        lp_controller.wait--;
}

void tips_interval_timing()
{
    if (lp_controller.interval > 0)
        lp_controller.interval--;

    if ((lp_controller.interval <= 0) && (lp_controller.times > 0)) {
        lp_controller.times--;
        lp_controller.tips = false;
        lp_controller.interval = SECOND_TO_TICKS(TIPS_INTERVAL);
    }

#if 0
    info("interval:%d", lp_controller.interval);
    info("times   :%d", lp_controller.times);
    info("power   :%d", read_battery_power());
#endif
}

unsigned char power_low_handler_active()
{
    if ((lp_controller.wait <= 0) && (lp_controller.power <= 28))
        return true;
    return false;
}

void active_power_tips()
{
    if (lp_controller.power <= 18)
        active_tips(
            &message_tips[POWER_10_WRN], 
            lp_controller.interval
        );
    if (lp_controller.power <= 23)
        active_tips(
            &message_tips[POWER_15_WRN], 
            lp_controller.interval
        );
    if (lp_controller.power <= 28)
        active_tips(
            &message_tips[POWER_20_WRN], 
            lp_controller.interval
        );
}

void active_power_off_tips()
{
    active_tips(
        &message_tips[POWER_LOW_AUTO_OFF], 
        lp_controller.interval
    );
}

void inactive_power_tips()
{
    inactive_tips(&message_tips[POWER_20_WRN]);
    inactive_tips(&message_tips[POWER_15_WRN]);
    inactive_tips(&message_tips[POWER_10_WRN]);
}

void active_power_off()
{
    static unsigned char wait_off = 0;

    if ((lp_controller.times <= 0) && (lp_controller.power < 18))
        goto power_off;
    else if (lp_controller.power < 15)
        goto power_off;
    else
        return;

power_off:
    active_power_off_tips();

    if (wait_off == 0)
        wait_off = SECOND_TO_TICKS(CONTROLLER_WAIT);
    wait_off--;

    if (wait_off == 0) {
        power_off_duration_sound(true);
        power_down();
    }
}

void power_low_handler()
{
    lp_controller.power = read_battery_power();

    power_handler_wait_timing();

    if (!power_low_handler_active()) {
        lp_controller.times = 5;
        if (lp_controller.tips == true) {
            inactive_power_tips();
            lp_controller.tips = false;
        }
        return;
    }

    tips_interval_timing();
    if (lp_controller.tips == false) {
        active_power_tips();
        lp_controller.tips = true;
    }

#ifndef KEIL_DEBUG
    active_power_off();
#endif
}

#endif /** Auto power off tips demo */
