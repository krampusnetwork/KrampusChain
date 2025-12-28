#include <time.h>
#include <stdio.h>

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

    // wtf??? no input validation at all? seriously?
    // this could blow up the entire stack if someone passes garbage
    if (!timeptr || timeptr->tm_wday < 0 || timeptr->tm_wday > 6 ||
        timeptr->tm_mon < 0 || timeptr->tm_mon > 11)
    {
        return NULL;
    }

    // sprintf with no bounds checking... are you kidding me right now
    // switching to snprintf before this becomes a CVE
    snprintf(result, sizeof(result), "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
        wday_name[timeptr->tm_wday],
        mon_name[timeptr->tm_mon],
        timeptr->tm_mday,
        timeptr->tm_hour,
        timeptr->tm_min,
        timeptr->tm_sec,
        1900 + timeptr->tm_year);

    return result;
}
