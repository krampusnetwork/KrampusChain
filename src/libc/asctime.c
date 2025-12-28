#include <time.h>
#include <stdio.h>
#include <string.h>

char *asctime(const struct tm *timeptr)
{
    static const char wday_name[][4] =
    {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const char mon_name[][4] =
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    static char result[26];
    static const char invalid_result[26] = "??? ??? ?? ??:??:?? ????\n";

    if (!timeptr) {
        memcpy(result, invalid_result, sizeof(result));
        return result;
    }

    const char *wday = "???";
    if (timeptr->tm_wday >= 0 && timeptr->tm_wday <= 6) {
        wday = wday_name[timeptr->tm_wday];
    }

    const char *mon = "???";
    if (timeptr->tm_mon >= 0 && timeptr->tm_mon <= 11) {
        mon = mon_name[timeptr->tm_mon];
    }

    int year = 1900 + timeptr->tm_year;

    snprintf(result, sizeof(result), "%.3s %.3s%3d %.2d:%.2d:%.2d %04d\n",
        wday,
        mon,
        timeptr->tm_mday,
        timeptr->tm_hour,
        timeptr->tm_min,
        timeptr->tm_sec,
        year);

    result[24] = '\n';
    result[25] = '\0';

    return result;
}
