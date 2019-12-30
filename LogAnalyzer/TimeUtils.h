#pragma once

#include <ctime>
#include <string>

using namespace std;

/**
 * Class for handling string/time conversions
 */
class TimeUtils
{
public:
    /**
     * Converts string from the form Www Mmm dd hh:mm:ss yyyy (output of asctime)
     * to a time_t
     *
     * @param[in] ascii_time - Time string retrieved from asctime()
     *
     * Returns pointer to struct tm returned by an internal call to localtime
     */
    static time_t AsctimeToTime(string ascii_time);
};