
#include "rtc.h"

static void rtc_clock_config()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    PWR_BackupAccessCmd(ENABLE);

#if defined (RTC_CLOCK_SOURCE_LSI) 
    RCC_LSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

#elif defined (RTC_CLOCK_SOURCE_LSE)
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

#endif

    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();
}

void real_timer_init()
{
    RTC_InitTypeDef rtc_init;

    rtc_clock_config();

    rtc_init.RTC_AsynchPrediv = ASYNCH_PREDIV;
    rtc_init.RTC_SynchPrediv = SYNCH_PREDIV;
    rtc_init.RTC_HourFormat = RTC_HourFormat_24;
    if (RTC_Init(&rtc_init) == ERROR)
        return;
}

void date_seting(int year, char month, char date, char weekday)
{
    RTC_DateTypeDef rtc_date;

    year -= 2000;
    rtc_date.RTC_Year = year;
    rtc_date.RTC_Month = month;
    rtc_date.RTC_Date = date;
    rtc_date.RTC_WeekDay = weekday;
    RTC_SetDate(TIME_FORMAT, &rtc_date);
    RTC_WriteBackupRegister(BACKUP_REG, BACKUP_DATA);    
}

void time_seting(char hour, char minute, char second, char time_type)
{
    RTC_TimeTypeDef rtc_time;

    rtc_time.RTC_H12 = time_type;
    rtc_time.RTC_Hours = hour;
    rtc_time.RTC_Minutes = minute;
    rtc_time.RTC_Seconds = second;
    RTC_SetTime(TIME_FORMAT, &rtc_time);
    RTC_WriteBackupRegister(BACKUP_REG, BACKUP_DATA);
}
/*
RTC_DateTypeDef read_date()
{
    RTC_DateTypeDef rtc_date;

    RTC_GetDate(TIME_FORMAT, &rtc_date);
    return rtc_date;
}

RTC_TimeTypeDef read_time()
{
    RTC_TimeTypeDef rtc_time;

    RTC_GetTime(TIME_FORMAT, &rtc_time);
    return rtc_time;
}
*/
RtcDate read_date()
{
    RtcDate date;
    RTC_DateTypeDef rtc_date;

    RTC_GetDate(TIME_FORMAT, &rtc_date);

    date.year = rtc_date.RTC_Year + 2000;
    date.month = rtc_date.RTC_Month;
    date.day = rtc_date.RTC_Date;
    date.weekday = rtc_date.RTC_WeekDay;
    return date;
}

RtcTime read_time()
{
    RtcTime time;
    RTC_TimeTypeDef rtc_time;

    RTC_GetTime(TIME_FORMAT, &rtc_time);

    time.hour = rtc_time.RTC_Hours; 
    time.minute = rtc_time.RTC_Minutes;
    time.second = rtc_time.RTC_Seconds;

    return time;
}
