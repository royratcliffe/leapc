#include "diff_days.h"
#include "leap.h"
#include "mkdays.h"

double diff_days(int year1, int year0) {
  double x = mkdays(year1, 1, 1) - mkdays(year0, 1, 1);
  int y = leap_day(year1) - leap_day(year0);
  return x - y;
}
