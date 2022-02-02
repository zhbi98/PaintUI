
#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f4xx.h"

// #define RTC_CLOCK_SOURCE_LSE
#define RTC_CLOCK_SOURCE_LSI

#define SYNCH_PREDIV    0xff
#define ASYNCH_PREDIV   0x7f

#define HOUR_12   RTC_H12_PM
#define HOUR_24   RTC_H12_AM

#define TIME_FORMAT RTC_Format_BIN
#define BACKUP_REG  RTC_BKP_DR0
#define BACKUP_DATA 0x32f2


typedef struct {
    int year;
    char month;
    char day;
    char weekday;
} RtcDate;

typedef struct {
    char hour;
    char minute;
    char second;
} RtcTime;

static void rtc_clock_config();

extern void real_timer_init();
extern void date_seting(int year, char month, char date, char weekday);
extern void time_seting(char hour, char minute, char second, char time_type);

extern RtcDate read_date();
extern RtcTime read_time();

#endif
