#include "leap.h"
#include "mkdays.h"

#include <assert.h>

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
