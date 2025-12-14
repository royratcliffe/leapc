#include "leap.h"

#include <assert.h>
#include <memory.h>
#include <time.h>

/*!
 * \brief Days of year, month and day of month.
 * \details Uses the standard library's "make time" function to make the number
 * of days for a year, month and month day. Divides the seconds by 86,400 (the
 * number of seconds in a day) in order to answer days rather than seconds.
 * \param year Year from 1970.
 * \param mon One-based month. Converts to a zero-based month.
 * \param mday Day of the month starting at one.
 * \note The standard library's mktime() function has a prescribed minimum start
 * time of 1970. Times cannot precede the first day of that year.
 */
static double mkdays(int year, int mon, int mday) {
  struct tm tm;
  (void)memset(&tm, 0, sizeof(tm));
  tm.tm_year = year - 1900;
  tm.tm_mon = mon - 1;
  tm.tm_mday = mday;
  return mktime(&tm) / (24.0 * 60 * 60);
}

/*!
 * \brief Compute difference in days.
 * \param year1 Year to compute for.
 * \param year0 Base year for comparison.
 * \returns The difference between the "make time" days in-between the two years
 * and the leap_day() difference.
 */
static double diff_days(int year1, int year0) {
  double x = mkdays(year1, 1, 1) - mkdays(year0, 1, 1);
  int y = leap_day(year1) - leap_day(year0);
  return x - y;
}

int leap_day_test(int argc, char **argv) {
  assert(366 == leap_day(1));
  assert(693961 == leap_day(1900));
  assert(25567 == leap_day(1970) - leap_day(1900));

  for (int year0 = 1970; year0 < 2025; year0++)
    for (int year_span = 1; year_span < 50; year_span++) {
      assert(0 == diff_days(year0 + year_span, year0));
    }
  return 0;
}
