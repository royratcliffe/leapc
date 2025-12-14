#include "days.h"
#include "leap.h"

#include <time.h>
#include <memory.h>

double mkdays(int year, int mon, int mday) {
  struct tm tm;
  (void)memset(&tm, 0, sizeof(tm));
  tm.tm_year = year - 1900;
  tm.tm_mon = mon - 1;
  tm.tm_mday = mday;
  return mktime(&tm) / (24.0 * 60 * 60);
}

double diff_days(int year1, int year0) {
  double x = mkdays(year1, 1, 1) - mkdays(year0, 1, 1);
  int y = leap_day(year1) - leap_day(year0);
  return x - y;
}
