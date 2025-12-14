#include "leap.h"

#include <assert.h>
#include <time.h>
#include <memory.h>

int year_test(int argc, char **argv)
{
    struct tm tm;
    time_t time = 0;
    // gmtime(&tm, &time);
    // assert(mktime(&tm) == 0);
    assert(is_leap_year(0));
    assert(!is_leap_year(1970));
    return 0;
}
