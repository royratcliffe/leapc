#include "mkdays.h"

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
