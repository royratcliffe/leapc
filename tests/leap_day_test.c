#include "leap.h"
#include "mkdays.h"
#include "diff_days.h"

#include <assert.h>

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
