#include "TimeUtils.h"
#include <iostream>
#include <map>

/**
 * List of months that could be printed by asctime.
 * Used to determine the index when building a struct tm
 * from the string.
 */
static const char MONTH_LIST[][4] = {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun",
      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char WEEKDAY_LIST[][4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static int GetWeekdayIndex(string day)
{
    for (int i = 0; i < 7; i++)
    {
        const char* wday = WEEKDAY_LIST[i];
        if (day.compare(wday) == 0)
        {
            return i;
        }
    }
#ifdef DEBUG
    cout << "Got invalid day of the week: " << day << endl;
#endif // DEBUG

    return -1;
}

/**
 * Expects a month from the array above. returns the index
 * which can be put into a struct tm instance
 */
static int GetMonthIndex(string month)
{
    for (int i = 0; i < 12; i++)
    {
        const char* mo = MONTH_LIST[i];
        if (month.compare(mo) == 0)
        {
            return i;
        }
    }
#ifdef DEBUG
    cout << "Got invalid month: " << month << endl;
#endif // DEBUG
    return -1;
}

// Expected string format is "Www Mmm dd hh:mm:ss yyyy"
time_t TimeUtils::AsctimeToTime(string ascii_time)
{
    time_t raw_time;
    struct tm* time_struct;
    time(&raw_time);
    time_struct = localtime(&raw_time);

    string day = ascii_time.substr(0, 3);
    string month = ascii_time.substr(4, 3);
    int day_of_the_month = atoi(ascii_time.substr(8, 2).c_str());
    int hour = atoi(ascii_time.substr(11, 2).c_str());
    int minute = atoi(ascii_time.substr(14, 2).c_str());
    int second = atoi(ascii_time.substr(17, 2).c_str());
    int year = atoi(ascii_time.substr(20, 4).c_str());
    
    time_struct->tm_mon = GetMonthIndex(month);
    time_struct->tm_wday = GetWeekdayIndex(day);
    time_struct->tm_mday = day_of_the_month;
    time_struct->tm_hour = hour;
    time_struct->tm_min = minute;
    time_struct->tm_sec = second;
    time_struct->tm_year = year - 1900;

#ifdef DEBUG
    cout << "Time struct dump:" << endl;
    cout << "  tm_mon  = " << time_struct->tm_mon << endl;
    cout << "  tm_wday = " << time_struct->tm_wday << endl;
    cout << "  tm_mday = " << time_struct->tm_mday << endl;
    cout << "  tm_hour = " << time_struct->tm_hour << endl;
    cout << "  tm_min  = " << time_struct->tm_min << endl;
    cout << "  tm_sec  = " << time_struct->tm_sec << endl;
    cout << "  tm_year = " << time_struct->tm_year<< endl;
    cout << "This as asctime is: " << asctime(time_struct);
#endif
    return mktime(time_struct);
}
