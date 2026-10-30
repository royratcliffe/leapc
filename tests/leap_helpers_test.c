#include "leap.h"

/* Keep assert-based tests enabled in Release builds. */
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>
#include <stdlib.h>

int leap_helpers_test(int argc, char **argv) {
  (void)argc;
  (void)argv;

  static const struct leap_off offsets[] = {
      {2000, 59},
      {2001, 59},
      {2000, 60},
  };
  static const struct leap_date dates[] = {
      {2000, 2, 29},
      {2001, 2, 29},
      {2000, 3, 29},
      {2000, 2, 28},
  };

  for (size_t i = 0; i < sizeof offsets / sizeof offsets[0]; i++)
    for (size_t j = 0; j < sizeof offsets / sizeof offsets[0]; j++)
      assert(equal_leap_off(offsets[i], offsets[j]) == (i == j));

  for (size_t i = 0; i < sizeof dates / sizeof dates[0]; i++)
    for (size_t j = 0; j < sizeof dates / sizeof dates[0]; j++)
      assert(equal_leap_date(dates[i], dates[j]) == (i == j));

  /* Test conversion between leap_date and leap_off structures. */
  static const struct {
    struct leap_date date;
    struct leap_off off;
    int absolute;
  } cases[] = {
      {{0, 1, 1}, {0, 0}, 0},   {{0, 2, 29}, {0, 59}, 59},     {{0, 12, 31}, {0, 365}, 365},
      {{1, 1, 1}, {1, 0}, 366}, {{-1, 12, 31}, {-1, 364}, -1},
  };

  for (size_t i = 0; i < sizeof cases / sizeof cases[0]; i++) {
    const struct leap_off off = leap_from_date(cases[i].date);
    assert(off.year == cases[i].off.year);
    assert(off.day == cases[i].off.day);
    assert(leap_abs_from_date(cases[i].date) == cases[i].absolute);

    const struct leap_date date = leap_date_from_off(cases[i].off);
    assert(date.year == cases[i].date.year);
    assert(date.month == cases[i].date.month);
    assert(date.day == cases[i].date.day);
  }

  return EXIT_SUCCESS;
}
